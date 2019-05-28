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

const Identifier Globals::TREEID_SETTINGS = "globalSettings";

Globals::Globals() : changed(false) {
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
    // TODO - add actual settings
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
    return tree;
}

void Globals::parseValueTree(const ValueTree &tree) {
    std::scoped_lock lock(mutex);
    reset();
    // TODO - add actual settings
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
