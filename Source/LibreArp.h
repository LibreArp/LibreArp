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

#include <atomic>
#include <sstream>
#include <mutex>
#include <bitset>
#include <juce_core/juce_core.h>
#include <juce_audio_processors/juce_audio_processors.h>

#include "ArpPattern.h"
#include "editor/EditorState.h"
#include "AudioUpdatable.h"
#include "Globals.h"
#include "Updater.h"

/**
 * The LibreArp audio processor.
 */
class LibreArp : public juce::AudioProcessor {
public:

    struct InputNote {
        explicit InputNote(int note = -1, double velocity = 0.8);

        int note;
        double velocity;
    };

    static const juce::Identifier TREEID_LIBREARP;
    static const juce::Identifier TREEID_LOOP_RESET;
    static const juce::Identifier TREEID_PATTERN_XML;
    static const juce::Identifier TREEID_OCTAVES;
    static const juce::Identifier TREEID_SMART_OCTAVES;
    static const juce::Identifier TREEID_INPUT_VELOCITY;
    static const juce::Identifier TREEID_SWING;
    static const juce::Identifier TREEID_MAX_CHORD_SIZE;
    static const juce::Identifier TREEID_EXTRA_NOTES_SELECTION_MODE;
    static const juce::Identifier TREEID_NUM_INPUT_NOTES;
    static const juce::Identifier TREEID_OUTPUT_MIDI_CHANNEL;
    static const juce::Identifier TREEID_INPUT_MIDI_CHANNEL;
    static const juce::Identifier TREEID_NON_PLAYING_MODE_OVERRIDE;
    static const juce::Identifier TREEID_BYPASS;
    static const juce::Identifier TREEID_PATTERN_OFFSET;
    static const juce::Identifier TREEID_USER_TIME_SIG;
    static const juce::Identifier TREEID_USER_TIME_SIG_NUMERATOR;
    static const juce::Identifier TREEID_USER_TIME_SIG_DENOMINATOR;

    enum ExtraNotesSelectionMode : int {
        FROM_BOTTOM = 0,
        FROM_TOP = 1,
    };

    LibreArp();
    ~LibreArp() override;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    bool isBusesLayoutSupported(const BusesLayout &layouts) const override;
    void processBlock(juce::AudioBuffer<float> &, juce::MidiBuffer &) override;
    void processBlock(juce::AudioBuffer<double> &, juce::MidiBuffer &) override;
    juce::AudioProcessorEditor *createEditor() override;
    bool hasEditor() const override;
    const juce::String getName() const override;
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String &newName) override;
    void getStateInformation(juce::MemoryBlock &destData) override;
    void setStateInformation(const void *data, int sizeInBytes) override;

    /**
     * Serializes this processor into a ValueTree.
     *
     * @return the value tree representing this pattern
     */
    juce::ValueTree toValueTree();

    /**
     * Schedules a stop of all currently playing notes. The stop will occur on the next block process.
     */
    void stopAll();

    /**
     * Sets the pattern to play.
     *
     * @param newPattern the pattern to play
     */
    void setPattern(const ArpPattern &newPattern);

    /**
     * Loads a pattern from the specified file.
     *
     * @param file the file to load
     */
    void loadPatternFromFile(const juce::File &file);

    /**
     * Schedules a pattern build for the processing of the next block.
     */
    void buildPattern();

    /**
     * Gets the current pattern.
     *
     * @return the current pattern
     */
    ArpPattern &getPattern();

    /**
     * Gets the last position the processor has played, in pulses.
     *
     * @return the last position the processor has played
     */
    int64_t getLastPosition();

    /**
     * Sets the amount of beats after which the loop should reset.
     *
     * @param beats the amount of beats after which the loop should reset
     */
    void setLoopReset(double beats);

    /**
     * Gets the amount of beats after which the loop should reset.
     *
     * @return the amount of beats after which the loop should reset
     */
    double getLoopReset() const;

    bool isTransposingOctaves();

    void setTransposingOctaves(bool value);

    bool isUsingSmartOctaves();

    void setUsingSmartOctaves(bool value);

    bool isUsingInputVelocity();

    void setUsingInputVelocity(bool value);

    /**
     * Gets the last active number of input notes.
     *
     * @return the last active number of input notes
     */
    int getNumInputNotes() const;

    /** Set whether we should be using user-defined time signature. */
    void setUserTimeSig(bool v);

    /** Check whether we are using user-defined time signature. */
    bool isUserTimeSig() const;

    void setUserTimeSigNumerator(int v);
    int getUserTimeSigNumerator() const;

    void setUserTimeSigDenominator(int v);
    int getUserTimeSigDenominator() const;

    /**
     * Gets the time signature numerator.
     *
     * @return the time signature numerator
     */
    int getTimeSigNumerator() const;

    /**
     * Gets the time signature denominator.
     *
     * @return the time signature denominator
     */
    int getTimeSigDenominator() const;

    /**
     * Fills in current debug playback position information.
     *
     * @param cpi the position information to fill
     */
    void fillCurrentNonPlayingPositionInfo(juce::AudioPlayHead::CurrentPositionInfo &cpi);


    bool getBypass() const;

    void setBypass(bool value);

    bool getRecordingPatternOffset() const;

    void setRecordingPatternOffset(bool value);

    void resetPatternOffset();

    /**
     * Gets the MIDI channel output notes are sent into.
     *
     * @return the MIDI channel output notes are sent into
     */
    int getOutputMidiChannel() const;

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
    int getInputMidiChannel() const;

    /**
     * Sets the MIDI channel input notes are read from.
     *
     * @param channel the MIDI channel input notes are read from. An integer from range 0-16. Notes from all channels
     * are read if zero.
     */
    void setInputMidiChannel(int channel);

    /**
     * Gets the current swing amount value.
     */
    float getSwing() const;

    /**
     * Sets the current swing amount value. Should be `0.0` to `1.0`.
     */
    void setSwing(float value);

    NonPlayingMode::Value getNonPlayingModeOverride() const;

    void setNonPlayingModeOverride(NonPlayingMode::Value nonPlayingModeOverride);

    int getMaxChordSize() const;

    void setMaxChordSize(int size);

    ExtraNotesSelectionMode getExtraNotesSelectionMode() const;

    void setExtraNotesSelectionMode(ExtraNotesSelectionMode mode);

    /**
     * Gets the current non-playing mode, taking the global and overridden one into account.
     */
    NonPlayingMode::Value getNonPlayingMode() const;

    Globals &getGlobals();

    void setLastUpdateInfo(Updater::UpdateInfo &info);

    Updater::UpdateInfo &getLastUpdateInfo();

    /**
     * Whether the playhead was playing in the last block.
     */
    bool wasPlaying = false;


private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LibreArp)

    /**
     * Global data of the plugin.
     */
    Globals globals;

    /**
     * The mutex for last update info.
     */
    std::recursive_mutex lastUpdateInfoMutex;

    /**
     * Last retrieved update info.
     */
    Updater::UpdateInfo lastUpdateInfo;

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
    juce::String patternXml;

    /**
     * The current pattern, built for playback.
     */
    ArpBuiltEvents events;

    /**
     * Whether the plugin is being bypassed.
     */
    juce::AudioParameterBool* bypass;

    /**
     * Whether the plugin should transpose octaves upon "note overflow".
     */
    juce::AudioParameterBool* octaves;

    /**
     * Whether the plugin should transpose by multiple octaves when the input spans multiple octaves.
     */
    juce::AudioParameterBool* smartOctaves;

    /**
     * Whether the plugin is using the velocity of input notes.
     */
    juce::AudioParameterBool* usingInputVelocity;

    /**
     * The amount of realtime swing applied to the arp pattern.
     */
    juce::AudioParameterFloat* swing;

    /**
     * The maximum amount of notes the plugin will take into account.
     */
    juce::AudioParameterInt* maxChordSize;

    /**
     * Determines how the plugin will choose input notes when there are more than `maxChordSize`.
     */
    juce::AudioParameterChoice* extraNotesSelectionMode;

    /**
     * The value of `swing` in the last processed block.
     */
    float lastSwing = 0.0f;

    /**
     * The last position the processor has played, in pulses.
     */
    std::atomic<int64_t> lastPosition = 0;

    /**
     * The amount of beats after which the loop should reset.
     */
    std::atomic<double> loopReset = 0.0;

    /**
     * Whether stopAll was called.
     */
    bool stopScheduled = false;

    /**
     * Whether buildPattern was called.
     */
    bool buildScheduled = false;

    /**
     * The number of input notes in the last block.
     */
    int lastNumInputNotes = 0;

    /**
     * The set of currently fed input notes.
     */
    juce::SortedSet<InputNote> inputNotes;

    /**
     * The set of currently playing output notes.
     */
    std::bitset<128 * 16> playingNotesBitset;

    /**
     * The last active number of input notes.
     */
    int octaveSize = 0;

    /** Whether time signature is manually set by the user or automatically
     * determined from the host. */
    bool userTimeSig = false;

    /** Time signature numerator from user. */
    int userTimeSigNumerator = 4;

    /** Time signature denominator from user. */
    int userTimeSigDenominator = 4;

    /** Time signature numerator from host. */
    int hostTimeSigNumerator = 4;

    /** Time signature denominator from host. */
    int hostTimeSigDenominator = 4;

    /**
     * The timestamp of the last debug playback reset.
     */
    int64_t silenceEndedTime;

    /** Playback offset - subtracted from the current playback time. Used to
     * offset the pattern globally in a song. */
    int64_t patternOffset = 0;

    /** Whether the plugin is going to be recording the playback offset the
     * next time playback starts. */
    juce::AudioParameterBool* recordingPatternOffset;

    /**
     * Number of octaves spanned by the current input - rounded up.
     */
    int smartOctaveNumber = 1;

    /**
     * The MIDI channel output notes are sent to.
     */
    int outputMidiChannel = 1;

    /**
     * The MIDI channel input notes are read from. Notes from all channels are read if zero.
     */
    int inputMidiChannel = 0;

    /**
     * Overridden non-playing mode.
     *
     * @see NonPlayingMode
     */
    NonPlayingMode::Value nonPlayingModeOverride = NonPlayingMode::Value::NONE;

    /**
     * Main LibreArp processing method.
     */
    void processMidi(int numSamples, juce::MidiBuffer &midi);

    /**
     * Processes input MIDI messages.
     *
     * @param inMidi the input MIDI messages
     */
    void processInputMidi(juce::MidiBuffer &inMidi, bool isPlaying);

    /**
     * Sends a noteOff for all currently playing output notes.
     *
     * @param midi the midi messages
     */
    void stopAll(juce::MidiBuffer &midi);

    /**
     * Calculates the index of the bit representing the specified note.
     */
    static int noteBitsetPosition(int channel, int noteNumber);

    bool isNotePlaying(int channel, int noteNumber);

    void setNotePlaying(int channel, int noteNumber);

    void setNoteNotPlaying(int channel, int noteNumber);

    /**
     * Sends an asynchronous update to the editor.
     */
    void updateEditor();

    /**
     * Calculates the next time of the specified event.
     *
     * @param event the event of which the next time should be calculated
     * @param blockEndPosition the current processed position
     * @param blockStartPosition the last processed position
     * @return the next time of the event
     */
    int64_t nextTime(ArpBuiltEvents::Event& event, int64_t blockStartPosition, int64_t blockEndPosition) const;

    /**
     * Calculates a new position value with swing applied.
     */
    double applySwing(double position, float swingAmount) const;
};

bool operator> (const LibreArp::InputNote &a, const LibreArp::InputNote &b);
bool operator< (const LibreArp::InputNote &a, const LibreArp::InputNote &b);
bool operator>=(const LibreArp::InputNote &a, const LibreArp::InputNote &b);
bool operator<=(const LibreArp::InputNote &a, const LibreArp::InputNote &b);
bool operator==(const LibreArp::InputNote &a, const LibreArp::InputNote &b);
