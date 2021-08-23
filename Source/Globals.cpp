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

#include "Globals.h"
#include "BuildConfig.h"

juce::String NonPlayingMode::toJuceString(NonPlayingMode::Value mode) {
    switch (mode) {
        case NonPlayingMode::Value::NONE:         return "NONE";
        case NonPlayingMode::Value::SILENCE:      return "SILENCE";
        case NonPlayingMode::Value::PASSTHROUGH:  return "PASSTHROUGH";
        case NonPlayingMode::Value::PATTERN:      return "PATTERN";
    }
    return "UNKNOWN";
}

juce::String NonPlayingMode::getDisplayName(NonPlayingMode::Value mode) {
    switch (mode) {
        case NonPlayingMode::Value::NONE:         return "None";
        case NonPlayingMode::Value::SILENCE:      return "Silence";
        case NonPlayingMode::Value::PASSTHROUGH:  return "Passthrough";
        case NonPlayingMode::Value::PATTERN:      return "Pattern";
    }
    return "Unknown";
}

NonPlayingMode::Value NonPlayingMode::of(juce::var&& var) {
    return NonPlayingMode::of(juce::String(var));
}

NonPlayingMode::Value NonPlayingMode::of(juce::String&& string) {
    if (string == "NONE")         return NonPlayingMode::Value::NONE;
    if (string == "SILENCE")      return NonPlayingMode::Value::SILENCE;
    if (string == "PASSTHROUGH")  return NonPlayingMode::Value::PASSTHROUGH;
    if (string == "PATTERN")      return NonPlayingMode::Value::PATTERN;

    return NonPlayingMode::Value::NONE;
}

const juce::Identifier Globals::TREEID_SETTINGS = "globalSettings"; // NOLINT
const juce::Identifier Globals::TREEID_ASKED_FOR_UPDATE_CHECK_CONSENT = "askedForUpdateCheckConsent"; // NOLINT
const juce::Identifier Globals::TREEID_UPDATE_CHECK = "checkForUpdates"; // NOLINT
const juce::Identifier Globals::TREEID_FOUND_UPDATE_ON_LAST_CHECK = "foundUpdateOnLastCheck"; // NOLINT
const juce::Identifier Globals::TREEID_MIN_SECS_BEFORE_UPDATE_CHECK = "minSecsBeforeUpdateCheck"; // NOLINT
const juce::Identifier Globals::TREEID_LAST_UPDATE_CHECK_TIME = "lastUpdateCheckTime"; // NOLINT
const juce::Identifier Globals::TREEID_GUI_SCALE_FACTOR = "guiScaleFactor"; // NOLINT
const juce::Identifier Globals::TREEID_NON_PLAYING_MODE = "nonPlayingMode"; // NOLINT

Globals::Globals() :
        changed(false),
        askedForUpdateCheckConsent(false),
        checkForUpdatesEnabled(BuildConfig::DEFAULT_CHECK_FOR_UPDATES_ENABLED),
        foundUpdateOnLastCheck(false),
        minSecsBeforeUpdateCheck(BuildConfig::DEFAULT_MIN_SECS_BEFORE_UPDATE_CHECK),
        lastUpdateCheckTime(0L),
        guiScaleFactor(1.0f)
{
#if JUCE_OSX
    globalsDir = File::getSpecialLocation(File::SpecialLocationType::userApplicationDataDirectory)
            .getChildFile("Application Support")
            .getChildFile(JucePlugin_Name);
#else
    globalsDir = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userApplicationDataDirectory)
            .getChildFile(JucePlugin_Name);
#endif

    settingsFile = globalsDir.getChildFile("settings.xml");
    patternPresetsDir = globalsDir.getChildFile("presets");

    // TODO - add better checks (e.g. what if the globalsDir is a file and not a directory for whatever reason?)
    if (!globalsDir.isDirectory()) {
        globalsDir.createDirectory();
    }
    if (!patternPresetsDir.isDirectory()) {
        patternPresetsDir.createDirectory();
    }

    load();
}

Globals::~Globals() {
    save();
}

void Globals::reset() {
    std::scoped_lock lock(mutex);
    askedForUpdateCheckConsent = false;
    checkForUpdatesEnabled = BuildConfig::DEFAULT_CHECK_FOR_UPDATES_ENABLED;
    minSecsBeforeUpdateCheck = BuildConfig::DEFAULT_MIN_SECS_BEFORE_UPDATE_CHECK;
    foundUpdateOnLastCheck = false;
    lastUpdateCheckTime = 0L;
    guiScaleFactor = 1.0;
    nonPlayingMode = NonPlayingMode::Value::PASSTHROUGH;
}

bool Globals::save() {
    std::scoped_lock lock(mutex);
    if (changed) {
        this->forceSave();
        return true;
    } else {
        return false;
    }
}

void Globals::forceSave() {
    std::scoped_lock lock(mutex);

    char const *lineEnding;
#if JUCE_WINDOWS
    lineEnding = "\r\n";
#else
    lineEnding = "\n";
#endif

    auto tree = toValueTree();

    settingsFile.replaceWithText(tree.toXmlString(), false, false, lineEnding);
}

void Globals::load() {
    std::scoped_lock lock(mutex);

    if (settingsFile.existsAsFile()) {
        auto xmlDoc = juce::XmlDocument::parse(settingsFile);
        parseValueTree(juce::ValueTree::fromXml(*xmlDoc));
    } else {
        reset();
    }
}

void Globals::markChanged() {
    std::scoped_lock lock(mutex);
    this->changed = true;
}

juce::ValueTree Globals::toValueTree() {
    std::scoped_lock lock(mutex);
    auto tree = juce::ValueTree(TREEID_SETTINGS);

    tree.setProperty(TREEID_ASKED_FOR_UPDATE_CHECK_CONSENT, this->askedForUpdateCheckConsent, nullptr);
    tree.setProperty(TREEID_UPDATE_CHECK, this->checkForUpdatesEnabled, nullptr);
    tree.setProperty(TREEID_FOUND_UPDATE_ON_LAST_CHECK, this->foundUpdateOnLastCheck, nullptr);
    tree.setProperty(TREEID_MIN_SECS_BEFORE_UPDATE_CHECK, juce::int64(this->minSecsBeforeUpdateCheck), nullptr);
    tree.setProperty(TREEID_LAST_UPDATE_CHECK_TIME, juce::int64(this->lastUpdateCheckTime), nullptr);
    tree.setProperty(TREEID_GUI_SCALE_FACTOR, this->guiScaleFactor, nullptr);
    tree.setProperty(TREEID_NON_PLAYING_MODE, NonPlayingMode::toJuceString(this->nonPlayingMode), nullptr);

    return tree;
}

void Globals::parseValueTree(const juce::ValueTree &tree) {
    std::scoped_lock lock(mutex);
    reset();
    if (!tree.hasType(TREEID_SETTINGS)) {
        juce::Logger::writeToLog("Invalid settings tag! Skipping load.");
        return;
    }

    if (tree.hasProperty(TREEID_ASKED_FOR_UPDATE_CHECK_CONSENT)) {
        this->askedForUpdateCheckConsent = tree.getProperty(TREEID_ASKED_FOR_UPDATE_CHECK_CONSENT);
    }
    if (tree.hasProperty(TREEID_UPDATE_CHECK)) {
        this->checkForUpdatesEnabled = tree.getProperty(TREEID_UPDATE_CHECK);
    }
    if (tree.hasProperty(TREEID_FOUND_UPDATE_ON_LAST_CHECK)) {
        this->foundUpdateOnLastCheck = tree.getProperty(TREEID_FOUND_UPDATE_ON_LAST_CHECK);
    }
    if (tree.hasProperty(TREEID_MIN_SECS_BEFORE_UPDATE_CHECK)) {
        this->minSecsBeforeUpdateCheck = juce::int64(tree.getProperty(TREEID_MIN_SECS_BEFORE_UPDATE_CHECK));
    }
    if (tree.hasProperty(TREEID_LAST_UPDATE_CHECK_TIME)) {
        this->lastUpdateCheckTime = juce::int64(tree.getProperty(TREEID_LAST_UPDATE_CHECK_TIME));
    }
    if (tree.hasProperty(TREEID_GUI_SCALE_FACTOR)) {
        this->guiScaleFactor = tree.getProperty(TREEID_GUI_SCALE_FACTOR);
    }
    if (tree.hasProperty(TREEID_NON_PLAYING_MODE)) {
        this->nonPlayingMode = NonPlayingMode::of(tree.getProperty(TREEID_NON_PLAYING_MODE));
    }
}


juce::File Globals::getGlobalsDir() {
    return this->globalsDir;
}

juce::File Globals::getSettingsFile() {
    return this->settingsFile;
}

juce::File Globals::getPatternPresetsDir() {
    return this->patternPresetsDir;
}

bool Globals::isCheckForUpdatesEnabled() const {
    std::scoped_lock lock(mutex);
    return checkForUpdatesEnabled;
}

void Globals::setCheckForUpdatesEnabled(bool checkForUpdates) {
    std::scoped_lock lock(mutex);
    this->checkForUpdatesEnabled = checkForUpdates;
    this->changed = true;
}

bool Globals::isAskedForUpdateCheckConsent() const {
    std::scoped_lock lock(mutex);
    return askedForUpdateCheckConsent;
}

void Globals::setAskedForUpdateCheckConsent(bool asked) {
    std::scoped_lock lock(mutex);
    this->askedForUpdateCheckConsent = asked;
    this->changed = true;
}

int64_t Globals::getMinSecsBeforeUpdateCheck() const {
    std::scoped_lock lock(mutex);
    return minSecsBeforeUpdateCheck;
}

void Globals::setMinSecsBeforeUpdateCheck(int64_t minSecsBeforeUpdateCheck) {
    std::scoped_lock lock(mutex);
    Globals::minSecsBeforeUpdateCheck = minSecsBeforeUpdateCheck;
    this->changed = true;
}

int64_t Globals::getLastUpdateCheckTime() const {
    std::scoped_lock lock(mutex);
    return lastUpdateCheckTime;
}

void Globals::setLastUpdateCheckTime(int64_t lastUpdateCheckTime) {
    std::scoped_lock lock(mutex);
    Globals::lastUpdateCheckTime = lastUpdateCheckTime;
    this->changed = true;
}

bool Globals::isFoundUpdateOnLastCheck() const {
    std::scoped_lock lock(mutex);
    return foundUpdateOnLastCheck;
}

void Globals::setFoundUpdateOnLastCheck(bool foundUpdateOnLastCheck) {
    std::scoped_lock lock(mutex);
    Globals::foundUpdateOnLastCheck = foundUpdateOnLastCheck;
    this->changed = true;
}

float Globals::getGuiScaleFactor() const {
    std::scoped_lock lock(mutex);
    return guiScaleFactor;
}

void Globals::setGuiScaleFactor(float guiScaleFactor) {
    std::scoped_lock lock(mutex);
    Globals::guiScaleFactor = guiScaleFactor;
    this->changed = true;
}

NonPlayingMode::Value Globals::getNonPlayingMode() const {
    std::scoped_lock lock(mutex);
    return nonPlayingMode;
}

void Globals::setNonPlayingMode(NonPlayingMode::Value nonPlayingMode) {
    std::scoped_lock lock(mutex);
    Globals::nonPlayingMode = nonPlayingMode;
    this->changed = true;
}
