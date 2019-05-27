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

#pragma once

#include <sstream>
#include "../JuceLibraryCode/JuceHeader.h"
#include "ArpPattern.h"
#include "editor/EditorState.h"
#include "AudioUpdatable.h"
#include "Globals.h"

/**
 * The LibreArp audio processor.
 */
class LibreArp : public AudioProcessor {
public:
    static const Identifier TREEID_LIBREARP;
    static const Identifier TREEID_LOOP_RESET;
    static const Identifier TREEID_PATTERN_XML;
    static const Identifier TREEID_OCTAVES;
    static const Identifier TREEID_NUM_INPUT_NOTES;
    static const Identifier TREEID_OUTPUT_MIDI_CHANNEL;
    static const Identifier TREEID_INPUT_MIDI_CHANNEL;


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


    /**
     * Serializes this processor into a ValueTree.
     *
     * @return the value tree representing this pattern
     */
    ValueTree toValueTree();

    void getStateInformation(MemoryBlock &destData) override;

    void setStateInformation(const void *data, int sizeInBytes) override;



    /**
     * Schedules a stop of all currently playing notes. The stop will occur on the next block process.
     */
    void stopAll();



    /**
     * Sets the pattern to play.
     *
     * @param pattern the pattern to play
     * @param updateXml whether the XML representation should be updated
     */
    void setPattern(ArpPattern &pattern, bool updateXml = true);

    /**
     * Parses the pattern to play from the given XML data.
     *
     * @param xmlPattern the XML data
     */
    void parsePattern(const String &xmlPattern);

    /**
     * Builds the current pattern.
     */
    void buildPattern();

    /**
     * Gets the current pattern.
     *
     * @return the current pattern
     */
    ArpPattern &getPattern();

    /**
     * Gets the current pattern's XML.
     *
     * @return the current pattern's XML
     */
    String getStateXml();



    /**
     * Gets the last position the processor has played, in pulses.
     *
     * @return the last position the processor has played
     */
    int64 getLastPosition();

    /**
     * Sets the amount of beats after which the loop should reset.
     *
     * @param loopReset the amount of beats after which the loop should reset
     */
    void setLoopReset(double loopReset);

    /**
     * Gets the amount of beats after which the loop should reset.
     *
     * @return the amount of beats after which the loop should reset
     */
    double getLoopReset();

    /**
     * Gets the currently playing pattern indices.
     *
     * @return the currently playing pattern indices
     */
    SortedSet<unsigned long> &getPlayingPatternIndices();


    bool isTransposingOctaves();

    void setTransposingOctaves(bool value);


    /**
     * Gets the last active number of input notes.
     *
     * @return the last active number of input notes
     */
    int getNumInputNotes();

    /**
     * Gets the time signature numerator.
     *
     * @return the time signature numerator
     */
    int getTimeSigNumerator();

    /**
     * Gets the time signature denominator.
     *
     * @return the time signature denominator
     */
    int getTimeSigDenominator();


    /**
     * @return <code>true</code> if debug playback is enabled, otherwise <code>false</code>
     */
    bool isDebugPlaybackEnabled();

    /**
     * Enables or disables debug playback and resets the debug playhead.
     *
     * @param enabled whether debug playback is enabled
     */
    void setDebugPlaybackEnabled(bool enabled);

    /**
     * Resets the debug playback.
     */
    void resetDebugPlayback();

    /**
     * Fills in current debug playback position information.
     *
     * @param cpi the position information to fill
     */
    void fillCurrentDebugPositionInfo(AudioPlayHead::CurrentPositionInfo &cpi);


    /**
     * Gets the MIDI channel output notes are sent into.
     *
     * @return the MIDI channel output notes are sent into
     */
    int getOutputMidiChannel();

    /**
     * Sets the MIDI channel output notes are sent into.
     *
     * @param channel the MIDI channel output notes are sent into. An integer from range 1-16.
     */
    void setOutputMidiChannel(int channel);



    /**
     * Gets the MIDI channel input notes are read from.
     *
     * @return the MIDI channel input notes are read from
     */
    int getInputMidiChannel();

    /**
     * Sets the MIDI channel input notes are read from.
     *
     * @param channel the MIDI channel input notes are read from. An integer from range 0-16. Notes from all channels
     * are read if zero.
     */
    void setInputMidiChannel(int channel);



private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LibreArp);

    /**
     * Global data of the plugin.
     */
    Globals globals;

    /**
     * The persistent state of the editor.
     */
    EditorState editorState;



    /**
     * The current pattern.
     */
    ArpPattern pattern;

    /**
     * The current pattern's XML representation.
     */
    String patternXml;

    /**
     * The current pattern, built for playback.
     */
    ArpBuiltEvents events;



    /**
     * Whether the plugin should transpose octaves upon "note overflow".
     */
    AudioParameterBool *octaves;



    /**
     * The last position the processor has played, in pulses.
     */
    int64 lastPosition;

    /**
     * The amount of beats after which the loop should reset.
     */
    double loopReset;

    /**
     * Whether the playhead was playing in the last block.
     */
    bool wasPlaying;



    /**
     * Whether stopAll was called.
     */
    bool stopScheduled;

    /**
     * Whether buildPattern was called.
     */
    bool buildScheduled;



    /**
     * The set of currently fed input notes.
     */
    SortedSet<int> inputNotes;

    /**
     * The set of currently playing output notes.
     */
    SortedSet<ArpBuiltEvents::PlayingNote> playingNotes;

    /**
     * The set of currently playing pattern indices.
     */
    SortedSet<unsigned long> playingPatternIndices;

    /**
     * The last active number of input notes.
     */
    int numInputNotes;

    /**
     * Time signature numerator.
     */
    int timeSigNumerator;

    /**
     * Time signature denominator.
     */
    int timeSigDenominator;


    /**
     * Whether debug playback is enabled.
     */
    bool debugPlaybackEnabled;

    /**
     * The timestamp of the last debug playback reset.
     */
    unsigned long debugPlaybackResetTime;


    /**
     * The MIDI channel output notes are sent to.
     */
    int outputMidiChannel;

    /**
     * The MIDI channel input notes are read from. Notes from all channels are read if zero.
     */
    int inputMidiChannel;



    /**
     * Processes input MIDI messages.
     *
     * @param inMidi the input MIDI messages
     */
    void processInputMidi(MidiBuffer &inMidi);

    /**
     * Sends a noteOff for all currently playing output notes.
     *
     * @param midi the midi messages
     */
    void stopAll(MidiBuffer &midi);

    /**
     * Sends an update to the editor.
     */
    void updateEditor(uint32 type = AudioUpdatable::GENERAL_UPDATE);



    /**
     * Calculates the next time of the specified event.
     *
     * @param event the event of which the next time should be calculated
     * @param position the current processed position
     * @param lastPosition the last processed position
     * @return the next time of the event
     */
    int64 nextTime(ArpBuiltEvents::Event &event, int64 position, int64 lastPosition);
};
