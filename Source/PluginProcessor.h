#pragma once

#include <sstream>
#include "../JuceLibraryCode/JuceHeader.h"
#include "ArpPattern.h"

/**
 * The LibreArp audio processor.
 */
class LibreArpAudioProcessor : public AudioProcessor {
public:
    static const Identifier TREEID_LIBREARP;
    static const Identifier TREEID_PATTERN_XML;


    LibreArpAudioProcessor();

    ~LibreArpAudioProcessor() override;


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
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LibreArpAudioProcessor)

    ArpPattern pattern;
    String patternXml;
    std::vector<ArpEvent> events;
    unsigned long eventsPosition;

    double sampleRate;
    int64 lastPosition;
    int64 startingPosition;
    bool wasPlaying;

    SortedSet<int> activeNotes;
    int note;

    void processInputMidi(MidiBuffer &midiMessages);

    int64 nextTime(ArpEvent &event, int64 position);
};
