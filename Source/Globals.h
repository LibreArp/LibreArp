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

#include <mutex>
#include <juce_core/juce_core.h>
#include <juce_data_structures/juce_data_structures.h>

namespace NonPlayingMode {
    /**
     * An enumeration defining the behaviour of the plugin when the DAW is not playing but there are input notes
     * present.
     */
    enum class Value {
        NONE = 1,
        SILENCE,
        PASSTHROUGH,
        PATTERN,
    };

    juce::String toJuceString(Value mode);

    juce::String getDisplayName(Value mode);

    Value of(juce::var&& var);

    Value of(juce::String&& string);
};

/**
 * A class managing global data (like global settings) of the plugin.
 */
class Globals {
public:

    static const juce::Identifier TREEID_SETTINGS;
    static const juce::Identifier TREEID_ASKED_FOR_UPDATE_CHECK_CONSENT;
    static const juce::Identifier TREEID_UPDATE_CHECK;
    static const juce::Identifier TREEID_FOUND_UPDATE_ON_LAST_CHECK;
    static const juce::Identifier TREEID_MIN_SECS_BEFORE_UPDATE_CHECK;
    static const juce::Identifier TREEID_LAST_UPDATE_CHECK_TIME;
    static const juce::Identifier TREEID_GUI_SCALE_FACTOR;
    static const juce::Identifier TREEID_NON_PLAYING_MODE;


    explicit Globals();
    ~Globals();


    /**
     * Resets global settings to default values.
     */
    void reset();

    /**
     * Saves global settings if changed.
     *
     * @return <code>true</code> if needed, otherwise <code>false</code>
     */
    bool save();

    /**
     * Saves global settings (regardless of whether the settings have been changed).
     */
    void forceSave();

    /**
     * Loads/reloads global settings. Unsaved settings will be lost.
     */
    void load();

    /**
     * Marks the globals as changed. The next save() call will actually do the save.
     */
    void markChanged();

    /**
     * Converts this Globals object into a value tree.
     *
     * @return a value tree representing this object
     */
    juce::ValueTree toValueTree();

    /**
     * Resets this Globals object and repopulates it according to the specified value tree.
     *
     * @param tree the tree to use for repopulation
     */
    void parseValueTree(const juce::ValueTree &tree);


    /**
     * @return the directory where global data is stored
     */
    juce::File getGlobalsDir();

    /**
     * @return the global settings file
     */
    juce::File getSettingsFile();

    /**
     * @return the directory where pattern presets are stored
     */
    juce::File getPatternPresetsDir();

    bool isCheckForUpdatesEnabled() const;

    void setCheckForUpdatesEnabled(bool checkForUpdates);

    bool isAskedForUpdateCheckConsent() const;

    void setAskedForUpdateCheckConsent(bool asked);

    bool isFoundUpdateOnLastCheck() const;

    void setFoundUpdateOnLastCheck(bool foundUpdateOnLastCheck);

    int64_t getMinSecsBeforeUpdateCheck() const;

    void setMinSecsBeforeUpdateCheck(int64_t minSecsBeforeUpdateCheck);

    int64_t getLastUpdateCheckTime() const;

    void setLastUpdateCheckTime(int64_t lastUpdateCheckTime);

    float getGuiScaleFactor() const;

    void setGuiScaleFactor(float guiScaleFactor);

    NonPlayingMode::Value getNonPlayingMode() const;

    void setNonPlayingMode(NonPlayingMode::Value nonPlayingMode);

private:

    /**
     * Directory of the global data.
     */
    juce::File globalsDir;

    /**
     * Global settings file.
     */
    juce::File settingsFile;

    /**
     * Default presets directory.
     */
    juce::File patternPresetsDir;

    /**
     * This flag is <code>true</code> if the global settings have changed since the last save/load.
     */
    bool changed;

    /**
     * Whether the GUI of the plugin has already asked the user for consent about automatic update checks.
     */
    bool askedForUpdateCheckConsent;

    /**
     * Whether the plugin should check for updates automatically.
     */
    bool checkForUpdatesEnabled;

    /**
     * Whether the last update check yielded a positive result.
     */
    bool foundUpdateOnLastCheck;

    /**
     * The minimum amount of seconds that need to elapse before another check for updates is performed.
     */
    int64_t minSecsBeforeUpdateCheck;

    /**
     * The timestamp (in milliseconds) of the last update check.
     */
    int64_t lastUpdateCheckTime;

    /**
     * The scale factor of the GUI.
     */
    float guiScaleFactor;

    /**
     * Behaviour of the plugin when the host is not playing.
     */
    NonPlayingMode::Value nonPlayingMode;

    /**
     * Mutex for the globals.
     */
    mutable std::recursive_mutex mutex;

};


