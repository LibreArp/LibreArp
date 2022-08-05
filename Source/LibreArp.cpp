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
#include "util/MathConsts.h"

const juce::Identifier LibreArp::TREEID_LIBREARP = "libreArpPlugin"; // NOLINT
const juce::Identifier LibreArp::TREEID_LOOP_RESET = "loopReset"; // NOLINT
const juce::Identifier LibreArp::TREEID_PATTERN_XML = "patternXml"; // NOLINT
const juce::Identifier LibreArp::TREEID_OCTAVES = "octaves"; // NOLINT
const juce::Identifier LibreArp::TREEID_SMART_OCTAVES = "smartOctaves"; // NOLINT
const juce::Identifier LibreArp::TREEID_INPUT_VELOCITY = "usingInputVelocity"; // NOLINT
const juce::Identifier LibreArp::TREEID_SWING = "swing"; // NOLINT
const juce::Identifier LibreArp::TREEID_MAX_CHORD_SIZE = "maxChordSize"; // NOLINT
const juce::Identifier LibreArp::TREEID_EXTRA_NOTES_SELECTION_MODE = "extraNotesSelectionMode"; // NOLINT
const juce::Identifier LibreArp::TREEID_NUM_INPUT_NOTES = "numInputNotes"; // NOLINT
const juce::Identifier LibreArp::TREEID_OUTPUT_MIDI_CHANNEL = "outputMidiChannel"; // NOLINT
const juce::Identifier LibreArp::TREEID_INPUT_MIDI_CHANNEL = "inputMidiChannel"; // NOLINT
const juce::Identifier LibreArp::TREEID_NON_PLAYING_MODE_OVERRIDE = "nonPlayingModeOverride"; // NOLINT
const juce::Identifier LibreArp::TREEID_BYPASS = "bypass"; // NOLINT
const juce::Identifier LibreArp::TREEID_PATTERN_OFFSET = "patternOffset"; // NOLINT

static const int NOTES_IN_OCTAVE = 12;


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

// NOTE: The plugin technically should not need any audio channels, but there are two things:
//        - ever since migration to JUCE 6, without any channels, it reported numSamples of 0
//        - Renoise does not accept our MIDI output when there is no output channel
LibreArp::LibreArp()
        : AudioProcessor(BusesProperties()
                                 .withInput("Input", juce::AudioChannelSet::mono(), true)
                                 .withOutput("Output", juce::AudioChannelSet::mono(), true)),
          silenceEndedTime(juce::Time::currentTimeMillis())
{
    // NOTE: The parameters have to be pointers and allocated randomly on the heap because JUCE is trying to be smart
    //       about this and puts them in a std::unique_ptr to be 'managed', instead of us being able to put them
    //       inside of the processor directly and passing JUCE just a pointer to that... doing that will cause a nasty
    //       SIGSEGV when the plugin is unloaded from the host.
    addParameter(bypass = new juce::AudioParameterBool(
            "bypass",
            "Bypass",
            false,
            "Whether the plugin is being bypassed"));
    addParameter(octaves = new juce::AudioParameterBool(
            "octaves",
            "Octaves",
            true,
            "Overflow octave transposition"));
    addParameter(smartOctaves = new juce::AudioParameterBool(
            "smartOctaves",
            "Smart octaves",
            true,
            "Transpose by the number of octaves spanned by the input notes"));
    addParameter(usingInputVelocity = new juce::AudioParameterBool(
            "usingInputVelocity",
            "Input velocity",
            true,
            "Use input note velocity"));
    addParameter(swing = new juce::AudioParameterFloat(
            "swing",
            "Swing",
            0.0f, 1.0f, 0.0f));
    addParameter(maxChordSize = new juce::AudioParameterInt(
            "maxChordSize",
            "Chord size",
            0, 16, 0,
            "The maximum amount of input notes taken into account",
            [] (int value, int) {
                if (value == 0)
                    return std::string("Auto");

                std::stringstream ss;
                ss << value;
                return ss.str();
            }));
    addParameter(extraNotesSelectionMode = new juce::AudioParameterChoice(
            "extraNotesSelectionMode",
            "Note selection mode",
            { "From bottom", "From top" },
            ExtraNotesSelectionMode::FROM_BOTTOM,
            "Determines how notes should be selected when there are more than Chord size"));
    addParameter(recordingPatternOffset = new juce::AudioParameterBool(
            "recordingPatternOffset",
            "Record offset",
            false,
            "Whether the offset should be changed the next time playback starts."));

    globals.markChanged();
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
        updateEditor();
        buildScheduled = false;
    }

    // Input data processing
    juce::AudioPlayHead::CurrentPositionInfo cpi; // NOLINT
    if (getPlayHead() != nullptr) {
        getPlayHead()->getCurrentPosition(cpi);
    }

    processInputMidi(midi, cpi.isPlaying);

    if (lastNumInputNotes == 0 && inputNotes.size() > 0) {
        silenceEndedTime = juce::Time::currentTimeMillis();
    }

    if (!cpi.isPlaying && getNonPlayingMode() == NonPlayingMode::Value::PATTERN) {
        fillCurrentNonPlayingPositionInfo(cpi);
    }

    this->timeSigNumerator = cpi.timeSigNumerator;
    this->timeSigDenominator = cpi.timeSigDenominator;

    // Output generation
    if (!*bypass && cpi.isPlaying && !this->events.events.empty() && this->events.loopLength > 0) {
        auto timebase = this->events.timebase;
        auto pulseLength = 60.0 / (cpi.bpm * timebase);
        auto pulseSamples = getSampleRate() * pulseLength;

        // Current position in pattern-space
        auto baseBlockStartPosition = cpi.ppqPosition * timebase;
        if (*this->recordingPatternOffset) {
            this->patternOffset = baseBlockStartPosition;
            *this->recordingPatternOffset = false;
            this->updateHostDisplay();
            this->stopAll();
        }

        baseBlockStartPosition -= this->patternOffset;
        auto offsadd = (this->loopReset > 0)
            ? static_cast<int64_t>(this->loopReset * timebase)
            : this->events.loopLength;
        if (baseBlockStartPosition < 0)
            baseBlockStartPosition = std::fmod(baseBlockStartPosition, offsadd) + offsadd;

        auto baseBlockEndPosition = baseBlockStartPosition + numSamples / pulseSamples;
        auto blockStartPosition = static_cast<int64_t>(std::floor(applySwing(baseBlockStartPosition, lastSwing)));
        auto blockEndPosition = static_cast<int64_t>(std::ceil(applySwing(baseBlockEndPosition, *swing)));

        if (stopScheduled) {
            this->stopAll(midi);
            stopScheduled = false;
        }

        if (maxChordSize->get() != 0)
            octaveSize = maxChordSize->get();
        else if (inputNotes.size() != 0)
            octaveSize = inputNotes.size();

        for(auto event : events.events) {
            auto time = nextTime(event, blockStartPosition, blockEndPosition);

            if (time < blockEndPosition) {
                auto offsetBase = static_cast<int>(std::floor((double) (time - this->lastPosition) * pulseSamples));
                int offset = juce::jmin(offsetBase, numSamples - 1);

                if (this->lastPosition > blockEndPosition && offset < 0) {
                    offset = 0;
                }

                if (offset < 0) continue; // The event is outside of the current block

                // Generate note-off MIDI events
                for (auto i : event.offs) {
                    auto &data = events.data[i];
                    if (data.lastNote.noteNumber >= 0) {
                        midi.addEvent(juce::MidiMessage::noteOff(data.lastNote.outChannel, data.lastNote.noteNumber), offset);
                        setNoteNotPlaying(data.lastNote.outChannel, data.lastNote.noteNumber);
                        data.lastNote = ArpBuiltEvents::PlayingNote(-1, -1);
                    }
                }

                if (inputNotes.isEmpty()) continue;

                // Max chord size processing
                int chordSize;
                int indexOffset;
                if (maxChordSize->get() == 0) {
                    chordSize = inputNotes.size();
                    indexOffset = 0;
                } else {
                    chordSize = *maxChordSize;
                    indexOffset = (chordSize < inputNotes.size() && extraNotesSelectionMode->getIndex() == FROM_TOP)
                        ? inputNotes.size() - chordSize
                        : 0;
                }

                // Generate note-on MIDI events
                for (auto i : event.ons) {
                    auto &data = events.data[i];
                    auto index = data.noteNumber % chordSize;
                    if (index < 0)
                        index += inputNotes.size();
                    index += indexOffset;

                    if (index > inputNotes.size()) {
                        // There is no sound for us right now, skip it
                        data.lastNote = ArpBuiltEvents::PlayingNote(-1, -1);
                        continue;
                    }

                    auto note = inputNotes[index].note;
                    auto velocity = (*usingInputVelocity)
                            ? inputNotes[index].velocity * data.velocity * 1.25
                            : data.velocity;

                    // Transposition
                    if (*octaves) {
                        auto octave = data.noteNumber / chordSize;
                        if (data.noteNumber < 0) {
                            octave--;
                        }
                        note += (*smartOctaves)
                                ? octave * smartOctaveNumber * NOTES_IN_OCTAVE
                                : octave * NOTES_IN_OCTAVE;
                    }

                    if (juce::isPositiveAndBelow(note, 128) && data.lastNote.noteNumber != note) {
                        data.lastNote = ArpBuiltEvents::PlayingNote(note, outputMidiChannel);
                        midi.addEvent(juce::MidiMessage::noteOn(
                                    data.lastNote.outChannel,
                                    data.lastNote.noteNumber,
                                    static_cast<float>(velocity)), offset);
                        setNotePlaying(data.lastNote.outChannel, data.lastNote.noteNumber);
                    }
                }
            }
        }

        this->lastPosition = blockEndPosition;
        this->wasPlaying = true;
        updateEditor();
    } else {
        updateEditor();

        if (this->wasPlaying) {
            this->stopAll(midi);
        }

        this->lastPosition = 0;
        this->wasPlaying = false;
    }

    this->lastNumInputNotes = this->inputNotes.size();
    this->lastSwing = *this->swing;
}

//==============================================================================
bool LibreArp::hasEditor() const {
    return true;
}

juce::AudioProcessorEditor *LibreArp::createEditor() {
    return new MainEditor(*this, editorState);
}

void LibreArp::getStateInformation(juce::MemoryBlock &destData) {
    destData.reset();
    juce::MemoryOutputStream(destData, true).writeString(toValueTree().toXmlString());
}

void LibreArp::setStateInformation(const void *data, int sizeInBytes) {
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
            if (tree.hasProperty(TREEID_SMART_OCTAVES)) {
                *this->smartOctaves = tree.getProperty(TREEID_SMART_OCTAVES);
            } else {
                // Backwards compatibility: do not change behaviour of old instances
                *this->smartOctaves = false;
            }
            if (tree.hasProperty(TREEID_INPUT_VELOCITY)) {
                *this->usingInputVelocity = tree.getProperty(TREEID_INPUT_VELOCITY);
            }
            if (tree.hasProperty(TREEID_SWING)) {
                *this->swing = tree.getProperty(TREEID_SWING);
                this->lastSwing = *this->swing;
            }
            if (tree.hasProperty(TREEID_MAX_CHORD_SIZE)) {
                *this->maxChordSize = tree.getProperty(TREEID_MAX_CHORD_SIZE);
            }
            if (tree.hasProperty(TREEID_EXTRA_NOTES_SELECTION_MODE)) {
                *this->extraNotesSelectionMode = tree.getProperty(TREEID_EXTRA_NOTES_SELECTION_MODE);
            }
            if (tree.hasProperty(TREEID_NUM_INPUT_NOTES)) {
                this->octaveSize = tree.getProperty(TREEID_NUM_INPUT_NOTES);
            }
            if (tree.hasProperty(TREEID_OUTPUT_MIDI_CHANNEL)) {
                this->outputMidiChannel = tree.getProperty(TREEID_OUTPUT_MIDI_CHANNEL);
            }
            if (tree.hasProperty(TREEID_INPUT_MIDI_CHANNEL)) {
                this->inputMidiChannel = tree.getProperty(TREEID_INPUT_MIDI_CHANNEL);
            }
            if (tree.hasProperty(TREEID_NON_PLAYING_MODE_OVERRIDE)) {
                this->nonPlayingModeOverride = NonPlayingMode::of(tree.getProperty(TREEID_NON_PLAYING_MODE_OVERRIDE));
            }
            if (tree.hasProperty(TREEID_BYPASS)) {
                *this->bypass = tree.getProperty(TREEID_BYPASS);
            }
            if (tree.hasProperty(TREEID_PATTERN_OFFSET)) {
                this->patternOffset = static_cast<juce::int64>(tree.getProperty(TREEID_PATTERN_OFFSET));
            }

            setPattern(loadedPattern);
        }
    }
}

juce::ValueTree LibreArp::toValueTree() {
    juce::ValueTree tree = juce::ValueTree(TREEID_LIBREARP);
    tree.appendChild(this->pattern.toValueTree(), nullptr);
    tree.appendChild(this->editorState.toValueTree(), nullptr);
    tree.setProperty(TREEID_LOOP_RESET, this->loopReset.load(), nullptr);
    tree.setProperty(TREEID_PATTERN_XML, this->patternXml, nullptr);
    tree.setProperty(TREEID_OCTAVES, this->octaves->get(), nullptr);
    tree.setProperty(TREEID_SMART_OCTAVES, this->smartOctaves->get(), nullptr);
    tree.setProperty(TREEID_INPUT_VELOCITY, this->usingInputVelocity->get(), nullptr);
    tree.setProperty(TREEID_SWING, this->swing->get(), nullptr);
    tree.setProperty(TREEID_MAX_CHORD_SIZE, this->maxChordSize->get(), nullptr);
    tree.setProperty(TREEID_EXTRA_NOTES_SELECTION_MODE, this->extraNotesSelectionMode->getIndex(), nullptr);
    tree.setProperty(TREEID_NUM_INPUT_NOTES, this->octaveSize, nullptr);
    tree.setProperty(TREEID_OUTPUT_MIDI_CHANNEL, this->outputMidiChannel, nullptr);
    tree.setProperty(TREEID_INPUT_MIDI_CHANNEL, this->inputMidiChannel, nullptr);
    tree.setProperty(TREEID_NON_PLAYING_MODE_OVERRIDE, NonPlayingMode::toJuceString(this->nonPlayingModeOverride), nullptr);
    tree.setProperty(TREEID_BYPASS, this->bypass->get(), nullptr);
    tree.setProperty(TREEID_PATTERN_OFFSET, static_cast<juce::int64>(this->patternOffset), nullptr);
    return tree;
}

void LibreArp::setPattern(const ArpPattern &newPattern) {
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


int64_t LibreArp::getLastPosition() {
    return this->lastPosition;
}



void LibreArp::setLoopReset(double beats) {
    this->loopReset = juce::jmax(0.0, beats);
}

double LibreArp::getLoopReset() const {
    return this->loopReset;
}


bool LibreArp::isTransposingOctaves() {
    return *this->octaves;
}

void LibreArp::setTransposingOctaves(bool value) {
    *this->octaves = value;
}

bool LibreArp::isUsingSmartOctaves() {
    return *this->smartOctaves;
}

void LibreArp::setUsingSmartOctaves(bool value) {
    *this->smartOctaves = value;
}

bool LibreArp::isUsingInputVelocity() {
    return *this->usingInputVelocity;
}

void LibreArp::setUsingInputVelocity(bool value) {
    *this->usingInputVelocity = value;
}


int LibreArp::getNumInputNotes() const {
    return this->octaveSize;
}

int LibreArp::getTimeSigNumerator() const {
    return this->timeSigNumerator;
}

int LibreArp::getTimeSigDenominator() const {
    return this->timeSigDenominator;
}

void LibreArp::fillCurrentNonPlayingPositionInfo(juce::AudioPlayHead::CurrentPositionInfo &cpi) {
    // Dummy data
    cpi.isLooping = false;
    cpi.isRecording = false;
    cpi.editOriginTime = 0.0;
    cpi.frameRate = juce::AudioPlayHead::FrameRateType::fps24;
    cpi.ppqLoopStart = 0.0;
    cpi.ppqLoopEnd = 0.0;
    cpi.ppqPositionOfLastBarStart = 0.0;

    // Metadata
    if (cpi.bpm <= 0.0) {
        cpi.bpm = 128.0;
    }
    if (cpi.timeSigNumerator <= 0) {
        cpi.timeSigNumerator = 3;
    }
    if (cpi.timeSigDenominator) {
        cpi.timeSigDenominator = 4;
    }
    cpi.isPlaying = !inputNotes.isEmpty();

    // Time data
    auto positionMillis = juce::Time::currentTimeMillis() - silenceEndedTime;
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



bool LibreArp::getBypass() const {
    return *this->bypass;
}

void LibreArp::setBypass(bool value) {
    *this->bypass = value;
}

bool LibreArp::getRecordingPatternOffset() const {
    return *this->recordingPatternOffset;
}

void LibreArp::setRecordingPatternOffset(bool value) {
    *this->recordingPatternOffset = value;
    this->updateEditor();
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

float LibreArp::getSwing() const {
    return *this->swing;
}

void LibreArp::setSwing(float value) {
    *this->swing = value;
}

NonPlayingMode::Value LibreArp::getNonPlayingModeOverride() const {
    return nonPlayingModeOverride;
}

void LibreArp::setNonPlayingModeOverride(NonPlayingMode::Value mode) {
    this->nonPlayingModeOverride = mode;
}

NonPlayingMode::Value LibreArp::getNonPlayingMode() const {
    return (nonPlayingModeOverride == NonPlayingMode::Value::NONE)
           ? globals.getNonPlayingMode()
           : nonPlayingModeOverride;
}

int LibreArp::getMaxChordSize() const {
    return *this->maxChordSize;
}

void LibreArp::setMaxChordSize(int size) {
    *this->maxChordSize = size;
}

LibreArp::ExtraNotesSelectionMode LibreArp::getExtraNotesSelectionMode() const {
    return static_cast<LibreArp::ExtraNotesSelectionMode>(this->extraNotesSelectionMode->getIndex());
}

void LibreArp::setExtraNotesSelectionMode(ExtraNotesSelectionMode mode) {
    *this->extraNotesSelectionMode = static_cast<int>(mode);
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


void LibreArp::processInputMidi(juce::MidiBuffer &inMidi, bool isPlaying) {
    bool inputNotesChanged = false;
    int sample = 0;
    juce::MidiBuffer outMidi;

    for (const juce::MidiMessageMetadata metadata : inMidi) {
        juce::MidiMessage message = metadata.getMessage();

        if (inputMidiChannel == 0 || message.getChannel() == inputMidiChannel) {
            bool processed = false;
            if (message.isNoteOn()) {
                inputNotes.add(InputNote(message.getNoteNumber(), message.getVelocity() / 127.0));
                processed = true;
                inputNotesChanged = true;
            } else if (message.isNoteOff()) {
                inputNotes.removeValue(InputNote(message.getNoteNumber()));
                processed = true;
                inputNotesChanged = true;
            }

            if (!processed || *bypass || (!isPlaying && getNonPlayingMode() == NonPlayingMode::Value::PASSTHROUGH)) {
                outMidi.addEvent(message, sample);
            }
        } else {
            if (message.isNoteOn()) {
                setNotePlaying(message.getChannel(), message.getNoteNumber());
            } else if (message.isNoteOff()) {
                setNoteNotPlaying(message.getChannel(), message.getNoteNumber());
            }

            outMidi.addEvent(message, sample);
        }
    }

    if (inputNotesChanged && !inputNotes.isEmpty()) {
        smartOctaveNumber = 1 + (inputNotes.getLast().note - inputNotes.getFirst().note) / NOTES_IN_OCTAVE;
    }

    inMidi.swapWith(outMidi);
}



void LibreArp::stopAll() {
    this->stopScheduled = true;
}

void LibreArp::stopAll(juce::MidiBuffer &midi) {
    for (int channel = 1; channel <= 16; channel++) {
        for (int noteNumber = 0; noteNumber <= 127; noteNumber++) {
            if (isNotePlaying(channel, noteNumber)) {
                midi.addEvent(juce::MidiMessage::noteOff(channel, noteNumber), 0);
            }
        }
    }
    playingNotesBitset.reset();

    for (auto &data : events.data) {
        data.lastNote = ArpBuiltEvents::PlayingNote(-1, -1);
    }
}

int LibreArp::noteBitsetPosition(int channel, int noteNumber) {
    return (channel - 1) * 128 + noteNumber;
}

bool LibreArp::isNotePlaying(int channel, int noteNumber) {
    if (noteNumber < 0 || noteNumber > 127 || channel < 1 || channel > 16) {
        return false;
    }

    return playingNotesBitset.test((size_t) noteBitsetPosition(channel, noteNumber));
}

void LibreArp::setNotePlaying(int channel, int noteNumber) {
    if (noteNumber < 0 || noteNumber > 127 || channel < 1 || channel > 16) {
        return;
    }

    playingNotesBitset.set((size_t) noteBitsetPosition(channel, noteNumber));
}

void LibreArp::setNoteNotPlaying(int channel, int noteNumber) {
    if (noteNumber < 0 || noteNumber > 127 || channel < 1 || channel > 16) {
        return;
    }

    playingNotesBitset.reset((size_t) noteBitsetPosition(channel, noteNumber));
}

void LibreArp::updateEditor() {
    auto editor = (MainEditor *) getActiveEditor();
    if (editor) {
        editor->triggerAsyncUpdate();
    }
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

double LibreArp::applySwing(double position, float swingAmount) const {
    if (swingAmount == 0.0) {
        // The resulting modifier would be zero, anyway, so no need to calculate.
        return position;
    }

    double swingFreq = (4 * X_PI) / events.timebase;
    return position - sin(position * swingFreq) * (swingAmount / swingFreq);
}

[[maybe_unused]] // Used by JUCE plugin wrappers
juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter() {
    return new LibreArp();
}
