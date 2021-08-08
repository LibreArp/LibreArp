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

#include "LibreArp.h"
#include "editor/MainEditor.h"

const juce::Identifier LibreArp::TREEID_LIBREARP = "libreArpPlugin"; // NOLINT
const juce::Identifier LibreArp::TREEID_LOOP_RESET = "loopReset"; // NOLINT
const juce::Identifier LibreArp::TREEID_PATTERN_XML = "patternXml"; // NOLINT
const juce::Identifier LibreArp::TREEID_OCTAVES = "octaves"; // NOLINT
const juce::Identifier LibreArp::TREEID_INPUT_VELOCITY = "usingInputVelocity"; // NOLINT
const juce::Identifier LibreArp::TREEID_NUM_INPUT_NOTES = "numInputNotes"; // NOLINT
const juce::Identifier LibreArp::TREEID_OUTPUT_MIDI_CHANNEL = "outputMidiChannel"; // NOLINT
const juce::Identifier LibreArp::TREEID_INPUT_MIDI_CHANNEL = "inputMidiChannel"; // NOLINT


LibreArp::InputNote::InputNote(int note, double velocity) : note(note), velocity(velocity) {}

bool operator>(const LibreArp::InputNote &a, const LibreArp::InputNote &b) {
    return a.note > b.note;
}

bool operator<(const LibreArp::InputNote &a, const LibreArp::InputNote &b) {
    return a.note < b.note;
}

bool operator>=(const LibreArp::InputNote &a, const LibreArp::InputNote &b) {
    return a.note >= b.note;
}

bool operator<=(const LibreArp::InputNote &a, const LibreArp::InputNote &b) {
    return a.note <= b.note;
}

bool operator==(const LibreArp::InputNote &a, const LibreArp::InputNote &b) {
    return a.note == b.note;
}


LibreArp::LibreArp()
    // The following input channel is needed, otherwise JUCE reports numSamples of 0
    : AudioProcessor(BusesProperties().withInput("Input", juce::AudioChannelSet::mono(), true))
{
    this->lastPosition = 0;
    this->wasPlaying = false;
    this->buildScheduled = false;
    this->stopScheduled = false;
    this->loopReset = 0.0;
    this->numInputNotes = 0;
    this->outputMidiChannel = 1;
    this->inputMidiChannel = 0;
    this->timeSigNumerator = 4;
    this->timeSigDenominator = 4;
    this->debugPlaybackEnabled = false;
    this->debugPlaybackResetTime = juce::Time::currentTimeMillis();
    resetDebugPlayback();

    globals.markChanged();

    addParameter(octaves = new juce::AudioParameterBool(
            "octaves",
            "Octaves",
            true,
            "Overflow octave transposition"));

    addParameter(usingInputVelocity = new juce::AudioParameterBool(
            "usingInputVelocity",
            "Input velocity",
            true,
            "Use input note velocity"));
}

LibreArp::~LibreArp() = default;

//==============================================================================
const juce::String LibreArp::getName() const {
    return JucePlugin_Name;
}

bool LibreArp::acceptsMidi() const {
    return true;
}

bool LibreArp::producesMidi() const {
    return true;
}

bool LibreArp::isMidiEffect() const {
    return true;
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
    juce::ignoreUnused(index);
}

const juce::String LibreArp::getProgramName(int index) {
    juce::ignoreUnused(index);
    return {};
}

void LibreArp::changeProgramName(int index, const juce::String &newName) {
    juce::ignoreUnused(index, newName);
}

//==============================================================================
void LibreArp::prepareToPlay(double sampleRate, int samplesPerBlock) {
    juce::ignoreUnused(samplesPerBlock, sampleRate);
}

void LibreArp::releaseResources() {

}

bool LibreArp::isBusesLayoutSupported(const BusesLayout &layouts) const {
    ignoreUnused(layouts);
    return true;
}

void LibreArp::processBlock(juce::AudioBuffer<float> &audio, juce::MidiBuffer &midi) {
    std::scoped_lock lock(mutex);
    juce::ScopedNoDenormals noDenormals;

    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    auto numSamples = audio.getNumSamples();

    // Clear output channels
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        audio.clear(i, 0, numSamples);

    processMidi(numSamples, midi);
}

void LibreArp::processBlock(juce::AudioBuffer<double> &audio, juce::MidiBuffer &midi) {
    std::scoped_lock lock(mutex);
    juce::ScopedNoDenormals noDenormals;

    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    auto numSamples = audio.getNumSamples();

    // Clear output channels
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        audio.clear(i, 0, numSamples);

    processMidi(numSamples, midi);
}

void LibreArp::processMidi(int numSamples, juce::MidiBuffer& midi) {
    // Build events if scheduled
    if (buildScheduled) {
        this->stopAll();
        events = pattern.buildEvents();
        updateEditor(AudioUpdatable::PATTERN_UPDATE);
        buildScheduled = false;
    }

    processInputMidi(midi);

    juce::AudioPlayHead::CurrentPositionInfo cpi; // NOLINT
    if (isDebugPlaybackEnabled() || juce::JUCEApplicationBase::isStandaloneApp()) {
        fillCurrentDebugPositionInfo(cpi);
    } else {
        if (getPlayHead() != nullptr) {
            getPlayHead()->getCurrentPosition(cpi);
        }
    }

    this->timeSigNumerator = cpi.timeSigNumerator;
    this->timeSigDenominator = cpi.timeSigDenominator;

    if (cpi.isPlaying && !this->events.events.empty()) {
        auto timebase = this->events.timebase;
        auto pulseLength = 60.0 / (cpi.bpm * timebase);
        auto pulseSamples = getSampleRate() * pulseLength;

        auto blockStartPosition = static_cast<int64_t>(std::floor(cpi.ppqPosition * timebase));
        auto blockEndPosition = blockStartPosition + static_cast<int64_t>(std::ceil(numSamples / pulseSamples));

        if (stopScheduled) {
            this->stopAll(midi);
            stopScheduled = false;
        }

        if (inputNotes.size() != 0) {
            numInputNotes = inputNotes.size();
        }

        for(auto event : events.events) {
            auto time = nextTime(event, blockStartPosition, blockEndPosition);

            if (time < blockEndPosition) {
                auto offsetBase = static_cast<int>(std::floor((double) (time - this->lastPosition) * pulseSamples));
                int offset = juce::jmin(offsetBase, numSamples - 1);

                if (this->lastPosition > blockEndPosition && offset < 0) {
                    offset = 0;
                }

                if (offset >= 0) {
                    for (auto i : event.offs) {
                        auto &data = events.data[i];
                        if (data.lastNote.noteNumber >= 0) {
                            midi.addEvent(juce::MidiMessage::noteOff(data.lastNote.outChannel, data.lastNote.noteNumber), offset);
                            playingNotes.removeValue(data.lastNote);
                            data.lastNote = ArpBuiltEvents::PlayingNote(-1, -1);
                        }
                    }

                    if (!inputNotes.isEmpty()) {
                        for (auto i : event.ons) {
                            auto &data = events.data[i];
                            auto index = data.noteNumber % inputNotes.size();
                            while (index < 0) {
                                index += inputNotes.size();
                            }

                            auto note = inputNotes[index].note;
                            auto velocity = (usingInputVelocity->get()) ?
                                    inputNotes[index].velocity * data.velocity * 1.25 :
                                    data.velocity;
                            if (octaves->get()) {
                                auto octave = data.noteNumber / inputNotes.size();
                                if (data.noteNumber < 0) {
                                    octave--;
                                }
                                note += octave * 12;
                            }

                            if (juce::isPositiveAndBelow(note, 128) && data.lastNote.noteNumber != note) {
                                data.lastNote = ArpBuiltEvents::PlayingNote(note, outputMidiChannel);
                                midi.addEvent(
                                        juce::MidiMessage::noteOn(
                                                data.lastNote.outChannel, data.lastNote.noteNumber, static_cast<float>(velocity)), offset);
                                playingNotes.add(data.lastNote);
                            }
                        }
                    }
                }
            }
        }

        updateEditor();

        this->lastPosition = blockEndPosition;
        this->wasPlaying = true;
    } else {
        if (this->wasPlaying) {
            updateEditor();

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

juce::AudioProcessorEditor *LibreArp::createEditor() {
    return new MainEditor(*this, editorState);
}

juce::ValueTree LibreArp::toValueTree() {
    std::scoped_lock lock(mutex);
    juce::ValueTree tree = juce::ValueTree(TREEID_LIBREARP);
    tree.appendChild(this->pattern.toValueTree(), nullptr);
    tree.appendChild(this->editorState.toValueTree(), nullptr);
    tree.setProperty(TREEID_LOOP_RESET, this->loopReset, nullptr);
    tree.setProperty(TREEID_PATTERN_XML, this->patternXml, nullptr);
    tree.setProperty(TREEID_OCTAVES, this->octaves->get(), nullptr);
    tree.setProperty(TREEID_INPUT_VELOCITY, this->usingInputVelocity->get(), nullptr);
    tree.setProperty(TREEID_NUM_INPUT_NOTES, this->numInputNotes, nullptr);
    tree.setProperty(TREEID_OUTPUT_MIDI_CHANNEL, this->outputMidiChannel, nullptr);
    tree.setProperty(TREEID_INPUT_MIDI_CHANNEL, this->inputMidiChannel, nullptr);
    return tree;
}

void LibreArp::getStateInformation(juce::MemoryBlock &destData) {
    destData.reset();
    juce::MemoryOutputStream(destData, true).writeString(toValueTree().toXmlString());
}

void LibreArp::setStateInformation(const void *data, int sizeInBytes) {
    std::scoped_lock lock(mutex);

    if (sizeInBytes > 0) {
        juce::String xml = juce::MemoryInputStream(data, static_cast<size_t>(sizeInBytes), false).readString();
        std::unique_ptr<juce::XmlElement> doc = juce::XmlDocument::parse(xml);
        juce::ValueTree tree = juce::ValueTree::fromXml(*doc);

        if (tree.isValid() && tree.hasType(TREEID_LIBREARP)) {
            juce::ValueTree patternTree = tree.getChildWithName(ArpPattern::TREEID_PATTERN);
            ArpPattern loadedPattern = ArpPattern::fromValueTree(patternTree);

            juce::ValueTree editorTree = tree.getChildWithName(EditorState::TREEID_EDITOR_STATE);
            if (editorTree.isValid()) {
                this->editorState = EditorState::fromValueTree(editorTree);
            }

            if (tree.hasProperty(TREEID_LOOP_RESET)) {
                this->loopReset = tree.getProperty(TREEID_LOOP_RESET);
            }

            if (tree.hasProperty(TREEID_OCTAVES)) {
                *this->octaves = tree.getProperty(TREEID_OCTAVES);
            }

            if (tree.hasProperty(TREEID_INPUT_VELOCITY)) {
                *this->usingInputVelocity = tree.getProperty(TREEID_INPUT_VELOCITY);
            }

            if (tree.hasProperty(TREEID_NUM_INPUT_NOTES)) {
                this->numInputNotes = tree.getProperty(TREEID_NUM_INPUT_NOTES);
            }

            if (tree.hasProperty(TREEID_OUTPUT_MIDI_CHANNEL)) {
                this->outputMidiChannel = tree.getProperty(TREEID_OUTPUT_MIDI_CHANNEL);
            }

            if (tree.hasProperty(TREEID_INPUT_MIDI_CHANNEL)) {
                this->inputMidiChannel = tree.getProperty(TREEID_INPUT_MIDI_CHANNEL);
            }

            setPattern(loadedPattern);
        }
    }
}

void LibreArp::setPattern(const ArpPattern &newPattern) {
    std::scoped_lock lock(mutex);

    this->pattern = newPattern;
    buildPattern();
}

void LibreArp::loadPatternFromFile(const juce::File &file) {
    setPattern(ArpPattern::fromFile(file));
}

void LibreArp::buildPattern() {
    this->buildScheduled = true;
}

ArpPattern &LibreArp::getPattern() {
    return this->pattern;
}

juce::String LibreArp::getStateXml() {
    std::scoped_lock lock(mutex);
    return this->toValueTree().toXmlString();
}


int64_t LibreArp::getLastPosition() {
    std::scoped_lock lock(mutex);
    return this->lastPosition;
}



void LibreArp::setLoopReset(double beats) {
    std::scoped_lock lock(mutex);
    this->loopReset = juce::jmax(0.0, beats);
}

double LibreArp::getLoopReset() const {
    return this->loopReset;
}


bool LibreArp::isTransposingOctaves() {
    return this->octaves->get();
}

void LibreArp::setTransposingOctaves(bool value) {
    std::scoped_lock lock(mutex);
    *this->octaves = value;
}

bool LibreArp::isUsingInputVelocity() {
    return this->usingInputVelocity->get();
}

void LibreArp::setUsingInputVelocity(bool value) {
    std::scoped_lock lock(mutex);
    *this->usingInputVelocity = value;
}


int LibreArp::getNumInputNotes() const {
    return this->numInputNotes;
}

int LibreArp::getTimeSigNumerator() const {
    return this->timeSigNumerator;
}

int LibreArp::getTimeSigDenominator() const {
    return this->timeSigDenominator;
}


bool LibreArp::isDebugPlaybackEnabled() const {
    return this->debugPlaybackEnabled || juce::JUCEApplicationBase::isStandaloneApp();
}

void LibreArp::setDebugPlaybackEnabled(bool enabled) {
    this->debugPlaybackEnabled = enabled;
    resetDebugPlayback();
}

void LibreArp::resetDebugPlayback() {
    this->debugPlaybackResetTime = juce::Time::currentTimeMillis();

    this->inputNotes.clear();
    if (this->isDebugPlaybackEnabled()) {
        inputNotes.add(InputNote(1));
        inputNotes.add(InputNote(2));
        inputNotes.add(InputNote(254));
    }
}

void LibreArp::fillCurrentDebugPositionInfo(juce::AudioPlayHead::CurrentPositionInfo &cpi) {
    // Dummy data
    cpi.isLooping = false;
    cpi.isRecording = false;
    cpi.editOriginTime = 0.0;
    cpi.frameRate = juce::AudioPlayHead::FrameRateType::fps24;
    cpi.ppqLoopStart = 0.0;
    cpi.ppqLoopEnd = 0.0;
    cpi.ppqPositionOfLastBarStart = 0.0; // TODO (update: yea, who knows what past me wanted to do here *facepalm*)

    // Metadata
    cpi.bpm = 128.0;
    cpi.timeSigNumerator = 3;
    cpi.timeSigDenominator = 4;
    cpi.isPlaying = true;

    // Time data
    auto positionMillis = juce::Time::currentTimeMillis() - debugPlaybackResetTime;
    cpi.timeInSeconds = static_cast<double>(positionMillis) * 0.001;
    cpi.timeInSamples = static_cast<int64_t>(cpi.timeInSeconds * getSampleRate());
    cpi.ppqPosition = cpi.timeInSeconds * (cpi.bpm / 60);
}


int LibreArp::getOutputMidiChannel() const {
    return this->outputMidiChannel;
}

void LibreArp::setOutputMidiChannel(int channel) {
    jassert(channel >= 1 && channel <= 16);
    this->outputMidiChannel = channel;
    this->stopAll();
}



int LibreArp::getInputMidiChannel() const {
    return this->inputMidiChannel;
}

void LibreArp::setInputMidiChannel(int channel) {
    jassert(channel >= 0 && channel <= 16);
    this->inputMidiChannel = channel;
    this->stopAll();
    this->inputNotes.clear();
}


Globals &LibreArp::getGlobals() {
    return this->globals;
}

void LibreArp::setLastUpdateInfo(Updater::UpdateInfo& info) {
    std::scoped_lock lock(lastUpdateInfoMutex);
    lastUpdateInfo = info;
}

Updater::UpdateInfo& LibreArp::getLastUpdateInfo() {
    std::scoped_lock lock(lastUpdateInfoMutex);
    return lastUpdateInfo;
}


void LibreArp::processInputMidi(juce::MidiBuffer &inMidi) {
    int sample;
    juce::MidiBuffer outMidi;

    for (const juce::MidiMessageMetadata metadata : inMidi) {
        juce::MidiMessage message = metadata.getMessage();

        if (inputMidiChannel == 0 || message.getChannel() == inputMidiChannel) {
            if (message.isNoteOn()) {
                inputNotes.add(InputNote(message.getNoteNumber(), message.getVelocity() / 127.0));
            } else if (message.isNoteOff()) {
                inputNotes.removeValue(InputNote(message.getNoteNumber()));
            } else {
                outMidi.addEvent(message, sample);
            }
        } else {
            outMidi.addEvent(message, sample);
        }
    }

    inMidi.swapWith(outMidi);
}



void LibreArp::stopAll() {
    this->stopScheduled = true;
}

void LibreArp::stopAll(juce::MidiBuffer &midi) {
    for (auto note : playingNotes) {
        midi.addEvent(juce::MidiMessage::noteOff(note.outChannel, note.noteNumber), 0);
    }
    playingNotes.clear();

    for (auto &data : events.data) {
        data.lastNote = ArpBuiltEvents::PlayingNote(-1, -1);
    }
}

void LibreArp::updateEditor(uint32_t type) {
    juce::MessageManager::callAsync([this, type] {
        auto editor = (MainEditor *) getActiveEditor();
        if (editor != nullptr && editor->isVisible()) {
            editor->audioUpdate(type);
        }
    });
}



int64_t LibreArp::nextTime(ArpBuiltEvents::Event& event, int64_t blockStartPosition, int64_t blockEndPosition) const {
    int64_t result;

    if (loopReset > 0.0) {
        auto loopResetLength = static_cast<int64_t>(std::ceil(events.timebase * loopReset));
        auto resetPosition = blockEndPosition % loopResetLength;
        auto intermediateResult = resetPosition - (resetPosition % events.loopLength) + event.time;

        result = blockEndPosition - (blockEndPosition % loopResetLength) + intermediateResult;
    } else {
        result = blockEndPosition - (blockEndPosition % events.loopLength) + event.time;
    }

    while (result < blockStartPosition) {
        result += events.loopLength;
    }

    return result;
}

juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter() {
    return new LibreArp();
}
