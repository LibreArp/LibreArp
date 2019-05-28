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

#include "JuceHeader.h"


/**
 * A class managing global data (like global settings) of the plugin.
 */
class Globals {
public:

    static const Identifier TREEID_SETTINGS;


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
    ValueTree toValueTree();

    /**
     * Resets this Globals object and repopulates it according to the specified value tree.
     *
     * @param tree the tree to use for repopulation
     */
    void parseValueTree(const ValueTree &tree);

private:

    /**
     * This flag is <code>true</code> if the global settings have changed since the last save/load.
     */
    bool changed;

    /**
     * Directory of the global data.
     */
    File globalsDir;

    /**
     * Global settings file.
     */
    File settingsFile;

    /**
     * Mutex for the globals.
     */
    std::recursive_mutex mutex;

};


