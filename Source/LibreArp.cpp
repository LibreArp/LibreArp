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
#include "exception/ArpIntegrityException.h"

const Identifier LibreArp::TREEID_LIBREARP = Identifier("libreArpPlugin"); // NOLINT
const Identifier LibreArp::TREEID_LOOP_RESET = Identifier("loopReset"); // NOLINT
const Identifier LibreArp::TREEID_PATTERN_XML = Identifier("patternXml"); // NOLINT
const Identifier LibreArp::TREEID_OCTAVES = Identifier("octaves"); // NOLINT
const Identifier LibreArp::TREEID_NUM_INPUT_NOTES = Identifier("numInputNotes"); // NOLINT
const Identifier LibreArp::TREEID_OUTPUT_MIDI_CHANNEL = Identifier("outputMidiChannel"); // NOLINT
const Identifier LibreArp::TREEID_INPUT_MIDI_CHANNEL = Identifier("inputMidiChannel"); // NOLINT


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
    resetDebugPlayback();

    globals.markChanged();

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
    ignoreUnused(sampleRate);
}

void LibreArp::releaseResources() {

}

#ifndef JucePlugin_PreferredChannelConfigurations

bool LibreArp::isBusesLayoutSupported(const BusesLayout &layouts) const {
    ignoreUnused(layouts);
    return true;
}

#endif

void LibreArp::processBlock(AudioBuffer<float> &audio, MidiBuffer &midi) {
    std::scoped_lock lock(mutex);

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
        updateEditor(AudioUpdatable::PATTERN_UPDATE);
        buildScheduled = false;
    }

    processInputMidi(midi);

    AudioPlayHead::CurrentPositionInfo cpi; // NOLINT
    if (isDebugPlaybackEnabled() || JUCEApplicationBase::isStandaloneApp()) {
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

        auto lastPosition = static_cast<int64>(std::floor(cpi.ppqPosition * timebase));
        auto position = lastPosition + static_cast<int64>(std::ceil(numSamples / pulseSamples));

        if (stopScheduled) {
            this->stopAll(midi);
            stopScheduled = false;
        }

        if (inputNotes.size() != 0) {
            numInputNotes = inputNotes.size();
        }

        for(auto event : events.events) {
            auto time = nextTime(event, position, lastPosition);

            if (time < position) {
                auto offsetBase = static_cast<int>(std::floor((time - this->lastPosition) * pulseSamples));
                int offset = jmin(offsetBase, numSamples - 1);

                if (this->lastPosition > position && offset < 0) {
                    offset = 0;
                }

                if (offset >= 0) {
                    for (auto i : event.offs) {
                        auto &data = events.data[i];
                        if (data.lastNote.noteNumber >= 0) {
                            midi.addEvent(MidiMessage::noteOff(data.lastNote.outChannel, data.lastNote.noteNumber), offset);
                            playingNotes.removeValue(data.lastNote);
                            playingPatternIndices.removeValue(data.noteIndex);
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

                            auto note = inputNotes[index];
                            if (octaves->get()) {
                                auto octave = data.noteNumber / inputNotes.size();
                                if (data.noteNumber < 0) {
                                    octave--;
                                }
                                note += octave * 12;
                            }

                            if (isPositiveAndBelow(note, 128) && data.lastNote.noteNumber != note) {
                                data.lastNote = ArpBuiltEvents::PlayingNote(note, outputMidiChannel);
                                midi.addEvent(
                                        MidiMessage::noteOn(
                                                data.lastNote.outChannel, data.lastNote.noteNumber, static_cast<float>(data.velocity)), offset);
                                playingNotes.add(data.lastNote);
                                playingPatternIndices.add(data.noteIndex);
                            }
                        }
                    }
                }
            }
        }

        updateEditor();

        this->lastPosition = position;
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

AudioProcessorEditor *LibreArp::createEditor() {
    return new MainEditor(*this, editorState);
}

ValueTree LibreArp::toValueTree() {
    std::scoped_lock lock(mutex);
    ValueTree tree = ValueTree(TREEID_LIBREARP);
    tree.appendChild(this->pattern.toValueTree(), nullptr);
    tree.appendChild(this->editorState.toValueTree(), nullptr);
    tree.setProperty(TREEID_LOOP_RESET, this->loopReset, nullptr);
    tree.setProperty(TREEID_PATTERN_XML, this->patternXml, nullptr);
    tree.setProperty(TREEID_OCTAVES, this->octaves->get(), nullptr);
    tree.setProperty(TREEID_NUM_INPUT_NOTES, this->numInputNotes, nullptr);
    tree.setProperty(TREEID_OUTPUT_MIDI_CHANNEL, this->outputMidiChannel, nullptr);
    tree.setProperty(TREEID_INPUT_MIDI_CHANNEL, this->inputMidiChannel, nullptr);
    return tree;
}

void LibreArp::getStateInformation(MemoryBlock &destData) {
    destData.reset();
    MemoryOutputStream(destData, true).writeString(toValueTree().toXmlString());
}

void LibreArp::setStateInformation(const void *data, int sizeInBytes) {
    std::scoped_lock lock(mutex);

    if (sizeInBytes > 0) {
        String xml = MemoryInputStream(data, static_cast<size_t>(sizeInBytes), false).readString();
        std::unique_ptr<XmlElement> doc = XmlDocument::parse(xml);
        ValueTree tree = ValueTree::fromXml(*doc);

        if (tree.isValid() && tree.hasType(TREEID_LIBREARP)) {
            ValueTree patternTree = tree.getChildWithName(ArpPattern::TREEID_PATTERN);
            ArpPattern pattern = ArpPattern::fromValueTree(patternTree);

            ValueTree editorTree = tree.getChildWithName(EditorState::TREEID_EDITOR_STATE);
            if (editorTree.isValid()) {
                this->editorState = EditorState::fromValueTree(editorTree);
            }

            if (tree.hasProperty(TREEID_LOOP_RESET)) {
                this->loopReset = tree.getProperty(TREEID_LOOP_RESET);
            }

            if (tree.hasProperty(TREEID_OCTAVES)) {
                *this->octaves = tree.getProperty(TREEID_OCTAVES);
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

            setPattern(pattern);
        }
    }
}

void LibreArp::setPattern(const ArpPattern &newPattern) {
    std::scoped_lock lock(mutex);

    this->pattern = newPattern;
    buildPattern();
}

void LibreArp::loadPatternFromFile(const File &file) {
    setPattern(ArpPattern::fromFile(file));
}

void LibreArp::buildPattern() {
    this->buildScheduled = true;
}

ArpPattern &LibreArp::getPattern() {
    return this->pattern;
}

String LibreArp::getStateXml() {
    std::scoped_lock lock(mutex);
    return this->toValueTree().toXmlString();
}


int64 LibreArp::getLastPosition() {
    std::scoped_lock lock(mutex);
    return this->lastPosition;
}



void LibreArp::setLoopReset(double loopReset) {
    std::scoped_lock lock(mutex);
    this->loopReset = jmax(0.0, loopReset);
}

double LibreArp::getLoopReset() {
    return this->loopReset;
}



SortedSet<unsigned long>& LibreArp::getPlayingPatternIndices() {
    std::scoped_lock lock(mutex);
    return this->playingPatternIndices;
}


bool LibreArp::isTransposingOctaves() {
    return this->octaves->get();
}

void LibreArp::setTransposingOctaves(bool value) {
    this->octaves->setValueNotifyingHost(value ? 1.0f : 0.0f);
}


int LibreArp::getNumInputNotes() {
    return this->numInputNotes;
}

int LibreArp::getTimeSigNumerator() {
    return this->timeSigNumerator;
}

int LibreArp::getTimeSigDenominator() {
    return this->timeSigDenominator;
}


bool LibreArp::isDebugPlaybackEnabled() {
    return this->debugPlaybackEnabled || JUCEApplicationBase::isStandaloneApp();
}

void LibreArp::setDebugPlaybackEnabled(bool enabled) {
    this->debugPlaybackEnabled = enabled;
    resetDebugPlayback();
}

void LibreArp::resetDebugPlayback() {
    this->debugPlaybackResetTime = Time::currentTimeMillis();

    this->inputNotes.clear();
    if (this->isDebugPlaybackEnabled()) {
        inputNotes.add(1);
        inputNotes.add(2);
        inputNotes.add(3);
    }
}

void LibreArp::fillCurrentDebugPositionInfo(AudioPlayHead::CurrentPositionInfo &cpi) {
    // Dummy data
    cpi.isLooping = false;
    cpi.isRecording = false;
    cpi.editOriginTime = 0.0;
    cpi.frameRate = AudioPlayHead::FrameRateType::fps24;
    cpi.ppqLoopStart = 0.0;
    cpi.ppqLoopEnd = 0.0;
    cpi.ppqPositionOfLastBarStart = 0.0; // TODO

    // Metadata
    cpi.bpm = 128.0;
    cpi.timeSigNumerator = 3;
    cpi.timeSigDenominator = 4;
    cpi.isPlaying = true;

    // Time data
    auto positionMillis = Time::currentTimeMillis() - debugPlaybackResetTime;
    cpi.timeInSeconds = positionMillis * 0.001;
    cpi.timeInSamples = static_cast<int64>(cpi.timeInSeconds * getSampleRate());
    cpi.ppqPosition = cpi.timeInSeconds * (cpi.bpm / 60);
}


int LibreArp::getOutputMidiChannel() {
    return this->outputMidiChannel;
}

void LibreArp::setOutputMidiChannel(int channel) {
    jassert(channel >= 1 && channel <= 16);
    this->outputMidiChannel = channel;
    this->stopAll();
}



int LibreArp::getInputMidiChannel() {
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


void LibreArp::processInputMidi(MidiBuffer &inMidi) {
    int sample;
    MidiBuffer outMidi;
    MidiMessage message;

    for (MidiBuffer::Iterator i(inMidi); i.getNextEvent(message, sample);) {
        if (inputMidiChannel == 0 || message.getChannel() == inputMidiChannel) {
            if (message.isNoteOn()) {
                inputNotes.add(message.getNoteNumber());
            } else if (message.isNoteOff()) {
                inputNotes.removeValue(message.getNoteNumber());
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

void LibreArp::stopAll(MidiBuffer &midi) {
    for (auto note : playingNotes) {
        midi.addEvent(MidiMessage::noteOff(note.outChannel, note.noteNumber), 0);
    }
    playingNotes.clear();
    playingPatternIndices.clear();

    for (auto &data : events.data) {
        data.lastNote = ArpBuiltEvents::PlayingNote(-1, -1);
    }
}

void LibreArp::updateEditor(uint32 type) {
    auto editor = (MainEditor *) getActiveEditor();
    MessageManager::callAsync([editor, type] {
        if (editor != nullptr && editor->isVisible()) {
            editor->audioUpdate(type);
        }
    });
}



int64 LibreArp::nextTime(ArpBuiltEvents::Event &event, int64 position, int64 lastPosition) {
    int64 result;

    if (loopReset > 0.0) {
        auto loopResetLength = static_cast<int64>(std::ceil(events.timebase * loopReset));
        auto resetPosition = position % loopResetLength;
        auto intermediateResult = resetPosition - (resetPosition % events.loopLength) + event.time;

        result = position - (position % loopResetLength) + intermediateResult;
    } else {
        result = position - (position % events.loopLength) + event.time;
    }

    if (result < lastPosition) {
        result += events.loopLength;
    }

    return result;
}

AudioProcessor *JUCE_CALLTYPE createPluginFilter() {
    return new LibreArp();
}
