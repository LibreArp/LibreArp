//
// This file is part of LibreArp
//
// LibreArp is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// LibreArp is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see https://librearp.gitlab.io/license/.
//

#include <map>
#include "ArpPattern.h"

const juce::Identifier ArpPattern::TREEID_PATTERN = juce::Identifier("pattern"); // NOLINT
const juce::Identifier ArpPattern::TREEID_TIMEBASE = juce::Identifier("timebase"); // NOLINT
const juce::Identifier ArpPattern::TREEID_LOOP_LENGTH = juce::Identifier("loopLength"); // NOLINT
const juce::Identifier ArpPattern::TREEID_LOOP_START = juce::Identifier("loopStart"); // NOLINT
const juce::Identifier ArpPattern::TREEID_LOOP_END = juce::Identifier("loopEnd"); // NOLINT
const juce::Identifier ArpPattern::TREEID_NOTES = juce::Identifier("notes"); // NOLINT

ArpPattern::ArpPattern(int timebase) : loopEnd(timebase), timebase(timebase) {}

ArpPattern::ArpPattern(ArpPattern &pattern) {
    std::scoped_lock lock(pattern.mutex);
    this->timebase = pattern.timebase;
    this->loopStart = pattern.loopStart;
    this->loopEnd = pattern.loopEnd;
    this->notes = pattern.notes;
}

ArpPattern::~ArpPattern() = default;


int ArpPattern::getTimebase() {
    std::scoped_lock lock(mutex);
    return this->timebase;
}

std::vector<ArpNote> &ArpPattern::getNotes() {
    std::scoped_lock lock(mutex);
    return this->notes;
}


ArpBuiltEvents ArpPattern::buildEvents() {
    std::scoped_lock lock(mutex);
    std::map<int64_t, ArpBuiltEvents::Event> eventMap;
    ArpBuiltEvents result;

    result.timebase = this->timebase;
    result.loopLength = this->loopEnd - this->loopStart;

    for (auto &note : this->notes) {
        if (note.startPoint < this->loopStart || note.endPoint > this->loopEnd) {
            continue; // Skip notes whose starts or ends are outside the loop
        }

        auto dataIndex = result.data.size();
        result.data.push_back(ArpBuiltEvents::EventNoteData::of(note.data));

        int64_t onTime = (note.startPoint - this->loopStart) % result.loopLength;
        ArpBuiltEvents::Event &onEvent = eventMap[onTime];
        onEvent.time = onTime;
        onEvent.ons.insert(dataIndex);

        int64_t offTime = (note.endPoint - this->loopStart) % result.loopLength;
        ArpBuiltEvents::Event &offEvent = eventMap[offTime];
        offEvent.time = offTime;
        offEvent.offs.insert(dataIndex);

        ArpBuiltEvents::Event &totalOffEvent = eventMap[0];
        totalOffEvent.time = 0;
        totalOffEvent.offs.insert(dataIndex);
    }

    for (const auto &pair : eventMap) {
        result.events.push_back(pair.second);
    }

    return result;
}

juce::ValueTree ArpPattern::toValueTree() {
    std::scoped_lock lock(mutex);
    juce::ValueTree result = juce::ValueTree(TREEID_PATTERN);

    result.setProperty(TREEID_TIMEBASE, this->timebase, nullptr);
    result.setProperty(TREEID_LOOP_START, juce::int64(this->loopStart), nullptr);
    result.setProperty(TREEID_LOOP_END, juce::int64(this->loopEnd), nullptr);

    juce::ValueTree noteTree = result.getOrCreateChildWithName(TREEID_NOTES, nullptr);
    for (ArpNote note : this->notes) {
        noteTree.appendChild(note.toValueTree(), nullptr);
    }

    return result;
}

void ArpPattern::toFile(const juce::File &file) {
    auto tree = toValueTree();
    file.replaceWithText(tree.toXmlString());
}

int64_t ArpPattern::loopLength() const {
    return loopEnd - loopStart;
}


ArpPattern ArpPattern::fromValueTree(juce::ValueTree &tree) {
    int timebase = DEFAULT_TIMEBASE;
    if (tree.hasProperty(TREEID_TIMEBASE)) {
        timebase = tree.getProperty(TREEID_TIMEBASE);
    }

    ArpPattern result = ArpPattern(timebase);

    if (!tree.isValid() || !tree.hasType(TREEID_PATTERN)) {
        return result;
    }

    if (tree.hasProperty(TREEID_LOOP_LENGTH)) {
        // Compatibility with old versions that do not have the loop start/end range
        result.loopStart = 0;
        result.loopEnd = juce::int64(tree.getProperty(TREEID_LOOP_LENGTH));
    }
    if (tree.hasProperty(TREEID_LOOP_START)) {
        result.loopStart = juce::int64(tree.getProperty(TREEID_LOOP_START));
    }
    if (tree.hasProperty(TREEID_LOOP_END)) {
        result.loopEnd = juce::int64(tree.getProperty(TREEID_LOOP_END));
    }

    juce::ValueTree notesTree = tree.getChildWithName(TREEID_NOTES);
    if (notesTree.isValid()) {
        for (int i = 0; i < notesTree.getNumChildren(); i++) {
            juce::ValueTree noteTree = notesTree.getChild(i);
            result.notes.push_back(ArpNote::fromValueTree(noteTree));
        }
    }

    return result;
}

ArpPattern ArpPattern::fromFile(const juce::File &file) {
    auto xmlDoc = juce::XmlDocument::parse(file);
    auto tree = juce::ValueTree::fromXml(*xmlDoc);
    return fromValueTree(tree);
}


std::recursive_mutex &ArpPattern::getMutex() {
    return mutex;
}

ArpPattern& ArpPattern::operator=(const ArpPattern &pattern) noexcept {
    std::scoped_lock lock(this->mutex);
    this->timebase = pattern.timebase;
    this->loopStart = pattern.loopStart;
    this->loopEnd = pattern.loopEnd;
    this->notes = pattern.notes;
    return *this;
}
