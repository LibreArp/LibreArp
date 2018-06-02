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

#pragma once

#include <sstream>
#include "../JuceLibraryCode/JuceHeader.h"
#include "ArpPattern.h"

/**
 * The LibreArp audio processor.
 */
class LibreArp : public AudioProcessor {
public:
    static const Identifier TREEID_LIBREARP;
    static const Identifier TREEID_PATTERN_XML;
    static const Identifier TREEID_OCTAVES;


    LibreArp();

    ~LibreArp() override;


    void prepareToPlay(double sampleRate, int samplesPerBlock) override;

    void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations

    bool isBusesLayoutSupported(const BusesLayout &layouts) const override;

#endif

    void processBlock(AudioBuffer<float> &, MidiBuffer &) override;


    AudioProcessorEditor *createEditor() override;

    bool hasEditor() const override;


    const String getName() const override;

    bool acceptsMidi() const override;

    bool producesMidi() const override;

    bool isMidiEffect() const override;

    double getTailLengthSeconds() const override;


    int getNumPrograms() override;

    int getCurrentProgram() override;

    void setCurrentProgram(int index) override;

    const String getProgramName(int index) override;

    void changeProgramName(int index, const String &newName) override;


    void getStateInformation(MemoryBlock &destData) override;

    void setStateInformation(const void *data, int sizeInBytes) override;


    void setPattern(ArpPattern &pattern, bool updateXml = true);

    void parsePattern(const String &xmlPattern);

    void buildPattern();

    ArpPattern &getPattern();

    String &getPatternXml();


    int64 getLastPosition();

    int getNote();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LibreArp);

    ArpPattern pattern;
    String patternXml;
    ArpBuiltEvents events;

    AudioParameterBool *octaves;

    double sampleRate;
    int64 lastPosition;
    bool wasPlaying;

    bool stopScheduled;
    bool buildScheduled;

    SortedSet<int> inputNotes;
    SortedSet<int> playingNotes;
    int note;

    void processInputMidi(MidiBuffer &midiMessages);
    void stopAll();
    void stopAll(MidiBuffer &midi);

    int64 nextTime(ArpBuiltEvents::Event &event, int64 position);
};
