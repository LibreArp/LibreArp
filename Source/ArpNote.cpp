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

#include "ArpNote.h"

const juce::Identifier ArpNote::TREEID_NOTE = juce::Identifier("note"); // NOLINT
const juce::Identifier ArpNote::TREEID_START_POINT = juce::Identifier("start"); // NOLINT
const juce::Identifier ArpNote::TREEID_END_POINT = juce::Identifier("end"); // NOLINT


ArpNote::ArpNote(NoteData data) {
    this->data = data;
    this->startPoint = 0;
    this->endPoint = 1;
}


juce::ValueTree ArpNote::toValueTree() {
    juce::ValueTree result = juce::ValueTree(TREEID_NOTE);
    result.appendChild(this->data.toValueTree(), nullptr);
    result.setProperty(TREEID_START_POINT, juce::int64(this->startPoint), nullptr);
    result.setProperty(TREEID_END_POINT, juce::int64(this->endPoint), nullptr);
    return result;
}


ArpNote ArpNote::fromValueTree(juce::ValueTree &tree) {
    if (!tree.isValid() || !tree.hasType(TREEID_NOTE)) {
        throw std::invalid_argument("Input tree must be valid and of the correct type!");
    }

    ArpNote result = ArpNote();

    juce::ValueTree dataTree = tree.getChildWithName(NoteData::TREEID_NOTE_DATA);
    if (dataTree.isValid()) {
        result.data = NoteData::fromValueTree(dataTree);
    }

    if (tree.hasProperty(TREEID_START_POINT)) {
        result.startPoint = juce::int64(tree.getProperty(TREEID_START_POINT));
    }

    if (tree.hasProperty(TREEID_END_POINT)) {
        result.endPoint = juce::int64(tree.getProperty(TREEID_END_POINT));
    }

    return result;
}
