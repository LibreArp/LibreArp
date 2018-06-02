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
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//

#include "LibreArp.h"
#include "editor/MainEditor.h"
#include "util/PatternUtil.h"
#include "exception/ArpIntegrityException.h"

const Identifier LibreArp::TREEID_LIBREARP = Identifier("libreArpPlugin"); // NOLINT
const Identifier LibreArp::TREEID_PATTERN_XML = Identifier("patternXml"); // NOLINT
const Identifier LibreArp::TREEID_OCTAVES = Identifier("octaves"); // NOLINT

//==============================================================================
LibreArp::LibreArp()
#ifndef JucePlugin_PreferredChannelConfigurations
        : AudioProcessor(BusesProperties()
#if !JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
.withInput  ("Input",  AudioChannelSet::stereo(), true)
#endif
.withOutput ("Output", AudioChannelSet::stereo(), true)
#endif
)
#endif
{
    ArpPattern pattern = PatternUtil::createBasicPattern();
    setPattern(pattern);

    addParameter(octaves = new AudioParameterBool(
            "octaves",
            "Octaves",
            true,
            "Overflow octave transport"));
}

LibreArp::~LibreArp() = default;

//==============================================================================
const String LibreArp::getName() const {
    return JucePlugin_Name;
}

bool LibreArp::acceptsMidi() const {
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool LibreArp::producesMidi() const {
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool LibreArp::isMidiEffect() const {
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double LibreArp::getTailLengthSeconds() const {
    return 0.0;
}

int LibreArp::getNumPrograms() {
    return 1;
}

int LibreArp::getCurrentProgram() {
    return 0;
}

void LibreArp::setCurrentProgram(int index) {
    ignoreUnused(index);
}

const String LibreArp::getProgramName(int index) {
    ignoreUnused(index);
    return {};
}

void LibreArp::changeProgramName(int index, const String &newName) {
    ignoreUnused(index);
}

//==============================================================================
void LibreArp::prepareToPlay(double sampleRate, int samplesPerBlock) {
    ignoreUnused(samplesPerBlock);
    this->sampleRate = sampleRate;
    this->lastPosition = 0;
    this->wasPlaying = false;
    this->buildScheduled = false;
    this->stopScheduled = false;
}

void LibreArp::releaseResources() {

}

#ifndef JucePlugin_PreferredChannelConfigurations

bool LibreArp::isBusesLayoutSupported(const BusesLayout &layouts) const {
#if JucePlugin_IsMidiEffect
    ignoreUnused(layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}

#endif

void LibreArp::processBlock(AudioBuffer<float> &audio, MidiBuffer &midi) {
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    auto numSamples = audio.getNumSamples();

    // Clear output channels
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        audio.clear(i, 0, numSamples);

    // Build events if scheduled
    if (buildScheduled) {
        this->stopAll();
        events = pattern.buildEvents();
        buildScheduled = false;
    }

    processInputMidi(midi);

    AudioPlayHead::CurrentPositionInfo cpi; // NOLINT
    getPlayHead()->getCurrentPosition(cpi);

    if (cpi.isPlaying && !this->pattern.getNotes().empty()) {
        midi.clear();

        if (stopScheduled) {
            this->stopAll(midi);
            stopScheduled = false;
        }

        auto timebase = this->pattern.getTimebase();
        auto pulseLength = 60.0 / (cpi.bpm * timebase);
        auto pulseSamples = this->sampleRate * pulseLength;

        auto position = static_cast<int64>(std::ceil(cpi.ppqPosition * timebase));
        auto lastPosition = position - static_cast<int64>(std::ceil(numSamples / pulseSamples));

        if (!wasPlaying || lastPosition > position) {
            this->stopAll();
        }

        if (inputNotes.isEmpty()) {
            for (auto &note : pattern.getNotes()) {
                auto &data = note.data;
                if (data.lastNote > 0) {
                    midi.addEvent(MidiMessage::noteOff(1, data.lastNote), 0);
                    data.lastNote = -1;
                }
            }
        } else {
            for(auto event : events.events) {
                auto time = nextTime(event, lastPosition);
                if (time < position) {
                    auto offsetBase = static_cast<int>(std::ceil((time - this->lastPosition) * pulseSamples));
                    int offset = jmax(0, jmin(offsetBase, numSamples - 1));

                    for (auto i : event.offs) {
                        auto &data = events.data[i];
                        if (data.lastNote >= 0) {
                            midi.addEvent(MidiMessage::noteOff(1, data.lastNote), offset);
                            playingNotes.removeValue(data.lastNote);
                            data.lastNote = -1;
                        }
                    }

                    for (auto i : event.ons) {
                        auto &data = events.data[i];
                        auto index = data.noteNumber % inputNotes.size();
                        if (index < 0) {
                            index += inputNotes.size();
                        }

                        auto note = inputNotes[index];
                        if (octaves->get()) {
                            auto octave = data.noteNumber / inputNotes.size();
                            if (data.noteNumber < 0) {
                                octave--;
                            }
                            note += octave * 12;
                        }

                        if (data.lastNote != note) {
                            data.lastNote = note;
                            midi.addEvent(
                                    MidiMessage::noteOn(1, note, static_cast<float>(data.velocity)), offset);
                            playingNotes.add(note);
                        }
                    }
                }
            }
        }

        if (getActiveEditor() != nullptr && getActiveEditor()->isVisible()) {
            getActiveEditor()->repaint();
        }

        this->lastPosition = position;
        this->wasPlaying = true;
    } else {
        if (this->wasPlaying) {
            if (getActiveEditor() != nullptr && getActiveEditor()->isVisible()) {
                getActiveEditor()->repaint();
            }

            this->stopAll(midi);
        }

        this->lastPosition = 0;
        this->wasPlaying = false;
    }
}

//==============================================================================
bool LibreArp::hasEditor() const {
    return true;
}

AudioProcessorEditor *LibreArp::createEditor() {
    return new MainEditor(*this);
}

//==============================================================================
void LibreArp::getStateInformation(MemoryBlock &destData) {
    ValueTree tree = ValueTree(TREEID_LIBREARP);
    tree.appendChild(this->pattern.toValueTree(), nullptr);
    tree.setProperty(TREEID_PATTERN_XML, this->patternXml, nullptr);
    tree.setProperty(TREEID_OCTAVES, this->octaves->get(), nullptr);

    destData.reset();
    MemoryOutputStream(destData, true).writeString(tree.toXmlString());
}

void LibreArp::setStateInformation(const void *data, int sizeInBytes) {
    if (sizeInBytes > 0) {
        String xml = MemoryInputStream(data, static_cast<size_t>(sizeInBytes), false).readString();
        XmlElement *doc = XmlDocument::parse(xml);
        ValueTree tree = ValueTree::fromXml(*doc);
        delete doc;

        if (tree.isValid() && tree.hasType(TREEID_LIBREARP)) {
            ValueTree patternTree = tree.getChildWithName(ArpPattern::TREEID_PATTERN);
            ArpPattern pattern = ArpPattern::fromValueTree(patternTree);

            if (tree.hasProperty(TREEID_OCTAVES)) {
                *this->octaves = tree.getProperty(TREEID_OCTAVES);
            }

            if (tree.hasProperty(TREEID_PATTERN_XML)) {
                this->patternXml = tree.getProperty(TREEID_PATTERN_XML);
                setPattern(pattern, false);
            } else {
                setPattern(pattern, true);
            }
        }
    } else {
        ArpPattern pattern = PatternUtil::createBasicPattern();
        setPattern(pattern);
    }
}

void LibreArp::setPattern(ArpPattern &pattern, bool updateXml) {
    this->pattern = pattern;
    if (updateXml) {
        this->patternXml = pattern.toValueTree().toXmlString();
    }
    buildPattern();
}

void LibreArp::parsePattern(const String &xmlPattern) {
    XmlElement *doc = XmlDocument::parse(xmlPattern);
    if (doc == nullptr) {
        throw ArpIntegrityException("Malformed XML!");
    }
    ValueTree tree = ValueTree::fromXml(*doc);
    delete doc;
    ArpPattern pattern = ArpPattern::fromValueTree(tree);
    setPattern(pattern, false);
    this->patternXml = xmlPattern;
}

void LibreArp::buildPattern() {
    this->buildScheduled = true;
}

ArpPattern &LibreArp::getPattern() {
    return this->pattern;
}

String &LibreArp::getPatternXml() {
    return this->patternXml;
}


int64 LibreArp::getLastPosition() {
    return this->lastPosition;
}

int LibreArp::getNote() {
    return this->note;
}


void LibreArp::processInputMidi(MidiBuffer &midiMessages) {
    int time;
    MidiMessage m;
    for (MidiBuffer::Iterator i(midiMessages); i.getNextEvent(m, time);) {
        if (m.isNoteOn()) {
            inputNotes.add(m.getNoteNumber());
        } else if (m.isNoteOff()) {
            inputNotes.removeValue(m.getNoteNumber());
        }
    }
}

void LibreArp::stopAll() {
    this->stopScheduled = true;
}

void LibreArp::stopAll(MidiBuffer &midi) {
    midi.clear();

    for (auto noteNumber : playingNotes) {
        midi.addEvent(MidiMessage::noteOff(1, noteNumber), 0);
    }
    playingNotes.clear();

    for (auto &data : events.data) {
        data.lastNote = -1;
    }
}


int64 LibreArp::nextTime(ArpEvent &event, int64 position) {
    auto result = (((position / pattern.loopLength)) * pattern.loopLength) + event.time;
    if (result < position) {
        result += pattern.loopLength;
    }
    return result;
}

int64 LibreArp::nextTime(ArpBuiltEvents::Event &event, int64 position) {
    auto result = (((position / pattern.loopLength)) * pattern.loopLength) + event.time;
    if (result < position) {
        result += pattern.loopLength;
    }
    return result;
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor *JUCE_CALLTYPE createPluginFilter() {
    return new LibreArp();
}
