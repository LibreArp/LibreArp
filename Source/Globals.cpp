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

const Identifier Globals::TREEID_SETTINGS = "globalSettings";
const Identifier Globals::TREEID_ASKED_FOR_UPDATE_CHECK_CONSENT = "askedForUpdateCheckConsent";
const Identifier Globals::TREEID_UPDATE_CHECK = "checkForUpdates";
const Identifier Globals::TREEID_FOUND_UPDATE_ON_LAST_CHECK = "foundUpdateOnLastCheck";
const Identifier Globals::TREEID_MIN_SECS_BEFORE_UPDATE_CHECK = "minSecsBeforeUpdateCheck";
const Identifier Globals::TREEID_LAST_UPDATE_CHECK_TIME = "lastUpdateCheckTime";

Globals::Globals() :
        changed(false),
        askedForUpdateCheckConsent(false),
        checkForUpdatesEnabled(BuildConfig::DEFAULT_CHECK_FOR_UPDATES_ENABLED),
        minSecsBeforeUpdateCheck(BuildConfig::DEFAULT_MIN_SECS_BEFORE_UPDATE_CHECK),
        foundUpdateOnLastCheck(false),
        lastUpdateCheckTime(0L)
{
#if JUCE_OSX
    globalsDir = File::getSpecialLocation(File::SpecialLocationType::userApplicationDataDirectory)
            .getChildFile("Application Support")
            .getChildFile(JucePlugin_Name);
#else
    globalsDir = File::getSpecialLocation(File::SpecialLocationType::userApplicationDataDirectory)
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
        auto xmlDoc = XmlDocument::parse(settingsFile);
        parseValueTree(ValueTree::fromXml(*xmlDoc));
    } else {
        reset();
    }
}

void Globals::markChanged() {
    std::scoped_lock lock(mutex);
    this->changed = true;
}

ValueTree Globals::toValueTree() {
    std::scoped_lock lock(mutex);
    auto tree = ValueTree(TREEID_SETTINGS);

    tree.setProperty(TREEID_ASKED_FOR_UPDATE_CHECK_CONSENT, this->askedForUpdateCheckConsent, nullptr);
    tree.setProperty(TREEID_UPDATE_CHECK, this->checkForUpdatesEnabled, nullptr);
    tree.setProperty(TREEID_FOUND_UPDATE_ON_LAST_CHECK, this->foundUpdateOnLastCheck, nullptr);
    tree.setProperty(TREEID_MIN_SECS_BEFORE_UPDATE_CHECK, this->minSecsBeforeUpdateCheck, nullptr);
    tree.setProperty(TREEID_LAST_UPDATE_CHECK_TIME, this->lastUpdateCheckTime, nullptr);

    return tree;
}

void Globals::parseValueTree(const ValueTree &tree) {
    std::scoped_lock lock(mutex);
    reset();
    if (!tree.hasType(TREEID_SETTINGS)) {
        Logger::writeToLog("Invalid settings tag! Skipping load.");
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
        this->minSecsBeforeUpdateCheck = tree.getProperty(TREEID_MIN_SECS_BEFORE_UPDATE_CHECK);
    }
    if (tree.hasProperty(TREEID_LAST_UPDATE_CHECK_TIME)) {
        this->lastUpdateCheckTime = tree.getProperty(TREEID_LAST_UPDATE_CHECK_TIME);
    }
}


File Globals::getGlobalsDir() {
    return this->globalsDir;
}

File Globals::getSettingsFile() {
    return this->settingsFile;
}

File Globals::getPatternPresetsDir() {
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

void Globals::setAskedForUpdateCheckConsent(bool askedForUpdateCheckConsent) {
    std::scoped_lock lock(mutex);
    this->askedForUpdateCheckConsent = askedForUpdateCheckConsent;
    this->changed = true;
}

int64 Globals::getMinSecsBeforeUpdateCheck() const {
    std::scoped_lock lock(mutex);
    return minSecsBeforeUpdateCheck;
}

void Globals::setMinSecsBeforeUpdateCheck(int64 minSecsBeforeUpdateCheck) {
    std::scoped_lock lock(mutex);
    Globals::minSecsBeforeUpdateCheck = minSecsBeforeUpdateCheck;
    this->changed = true;
}

int64 Globals::getLastUpdateCheckTime() const {
    std::scoped_lock lock(mutex);
    return lastUpdateCheckTime;
}

void Globals::setLastUpdateCheckTime(int64 lastUpdateCheckTime) {
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
