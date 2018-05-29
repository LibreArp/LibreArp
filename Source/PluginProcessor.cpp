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

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "util/PatternUtil.h"
#include "ArpIntegrityException.h"

const Identifier LibreArpAudioProcessor::TREEID_LIBREARP = Identifier("libreArpPlugin"); // NOLINT
const Identifier LibreArpAudioProcessor::TREEID_PATTERN_XML = Identifier("patternXml"); // NOLINT

//==============================================================================
LibreArpAudioProcessor::LibreArpAudioProcessor()
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
}

LibreArpAudioProcessor::~LibreArpAudioProcessor() = default;

//==============================================================================
const String LibreArpAudioProcessor::getName() const {
    return JucePlugin_Name;
}

bool LibreArpAudioProcessor::acceptsMidi() const {
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool LibreArpAudioProcessor::producesMidi() const {
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool LibreArpAudioProcessor::isMidiEffect() const {
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double LibreArpAudioProcessor::getTailLengthSeconds() const {
    return 0.0;
}

int LibreArpAudioProcessor::getNumPrograms() {
    return 1;
}

int LibreArpAudioProcessor::getCurrentProgram() {
    return 0;
}

void LibreArpAudioProcessor::setCurrentProgram(int index) {
    ignoreUnused(index);
}

const String LibreArpAudioProcessor::getProgramName(int index) {
    ignoreUnused(index);
    return {};
}

void LibreArpAudioProcessor::changeProgramName(int index, const String &newName) {
    ignoreUnused(index);
}

//==============================================================================
void LibreArpAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {
    ignoreUnused(samplesPerBlock);
    this->sampleRate = sampleRate;
    this->lastPosition = 0;
    this->wasPlaying = false;
}

void LibreArpAudioProcessor::releaseResources() {

}

#ifndef JucePlugin_PreferredChannelConfigurations

bool LibreArpAudioProcessor::isBusesLayoutSupported(const BusesLayout &layouts) const {
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

void LibreArpAudioProcessor::processBlock(AudioBuffer<float> &audio, MidiBuffer &midi) {
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    auto numSamples = audio.getNumSamples();

    // Clear output channels
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        audio.clear(i, 0, numSamples);

    processInputMidi(midi);

    midi.clear();
    AudioPlayHead::CurrentPositionInfo cpi; // NOLINT
    getPlayHead()->getCurrentPosition(cpi);

    if (cpi.isPlaying) {
        auto timebase = this->pattern.getTimebase();
        auto pulseLength = 60.0 / (cpi.bpm * timebase);
        auto pulseSamples = this->sampleRate * pulseLength;

        auto position = static_cast<int64>(std::ceil(cpi.ppqPosition * timebase));
        auto lastPosition = this->lastPosition;

        ArpEvent event;
        int64 time;
        if (activeNotes.isEmpty()) {
            for (auto &note : pattern.getNotes()) {
                auto &data = note.data;
                if (data.lastNote > 0) {
                    midi.addEvent(MidiMessage::noteOff(1, data.lastNote), 0);
                    data.lastNote = -1;
                }
            }
        } else {
            while ((time = nextTime(event = events[eventsPosition], lastPosition)) < position) {
                auto offsetBase = static_cast<int>(std::ceil((time - this->lastPosition) * pulseSamples));
                int offset = jmax(0, offsetBase % numSamples);

                for (auto data : event.offs) {
                    if (data->lastNote >= 0) {
                        midi.addEvent(MidiMessage::noteOff(1, data->lastNote), offset);
                        data->lastNote = -1;
                    }
                }

                for (auto data : event.ons) {
                    auto note = activeNotes[data->noteNumber % activeNotes.size()];
                    data->lastNote = note;
                    midi.addEvent(
                            MidiMessage::noteOn(1, note, static_cast<float>(data->velocity)), offset);
                }

                lastPosition = time;
                eventsPosition = (eventsPosition + 1) % events.size();
            }
        }

        this->lastPosition = position;
        this->wasPlaying = true;
    } else {
        for (auto &note : pattern.getNotes()) {
            auto &data = note.data;
            if (data.lastNote > 0) {
                midi.addEvent(MidiMessage::noteOff(1, data.lastNote), 0);
                data.lastNote = -1;
            }
        }
        this->eventsPosition = 0;
        this->lastPosition = 0;
        this->wasPlaying = false;
    }
}

//==============================================================================
bool LibreArpAudioProcessor::hasEditor() const {
    return true;
}

AudioProcessorEditor *LibreArpAudioProcessor::createEditor() {
    return new LibreArpAudioProcessorEditor(*this);
}

//==============================================================================
void LibreArpAudioProcessor::getStateInformation(MemoryBlock &destData) {
    ValueTree tree = ValueTree(TREEID_LIBREARP);
    tree.appendChild(this->pattern.toValueTree(), nullptr);
    tree.setProperty(TREEID_PATTERN_XML, this->patternXml, nullptr);

    destData.reset();
    MemoryOutputStream(destData, true).writeString(tree.toXmlString());
}

void LibreArpAudioProcessor::setStateInformation(const void *data, int sizeInBytes) {
    if (sizeInBytes > 0) {
        String xml = MemoryInputStream(data, static_cast<size_t>(sizeInBytes), false).readString();
        XmlElement *doc = XmlDocument::parse(xml);
        ValueTree tree = ValueTree::fromXml(*doc);
        delete doc;

        if (tree.isValid()) {
            if (tree.hasType(TREEID_LIBREARP)) {
                ValueTree patternTree = tree.getChildWithName(ArpPattern::TREEID_PATTERN);
                ArpPattern pattern = ArpPattern::fromValueTree(patternTree);

                if (tree.hasProperty(TREEID_PATTERN_XML)) {
                    this->patternXml = tree.getProperty(TREEID_PATTERN_XML);
                    setPattern(pattern, false);
                } else {
                    setPattern(pattern, true);
                }
            }
        }
    } else {
        ArpPattern pattern = PatternUtil::createBasicPattern();
        setPattern(pattern);
    }
}

void LibreArpAudioProcessor::setPattern(ArpPattern &pattern, bool updateXml) {
    this->pattern = pattern;
    if (updateXml) {
        this->patternXml = pattern.toValueTree().toXmlString();
    }
    buildPattern();
}

void LibreArpAudioProcessor::parsePattern(const String &xmlPattern) {
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

void LibreArpAudioProcessor::buildPattern() {
    this->events = this->pattern.build();
}

ArpPattern &LibreArpAudioProcessor::getPattern() {
    return this->pattern;
}

String &LibreArpAudioProcessor::getPatternXml() {
    return this->patternXml;
}


int64 LibreArpAudioProcessor::getLastPosition() {
    return this->lastPosition;
}

int LibreArpAudioProcessor::getNote() {
    return this->note;
}


void LibreArpAudioProcessor::processInputMidi(MidiBuffer &midiMessages) {
    int time;
    MidiMessage m;
    for (MidiBuffer::Iterator i(midiMessages); i.getNextEvent(m, time);) {
        if (m.isNoteOn()) {
            activeNotes.add(m.getNoteNumber());
        } else if (m.isNoteOff()) {
            activeNotes.removeValue(m.getNoteNumber());
        }
    }
}


int64 LibreArpAudioProcessor::nextTime(ArpEvent &event, int64 position) {
    auto result = (((position / pattern.loopLength)) * pattern.loopLength) + event.time;
    if (result < position) {
        result += pattern.loopLength;
    }
    return result;
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor *JUCE_CALLTYPE createPluginFilter() {
    return new LibreArpAudioProcessor();
}
