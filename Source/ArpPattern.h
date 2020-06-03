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

#include "../JuceLibraryCode/JuceHeader.h"
#include "ArpNote.h"
#include "ArpBuiltEvents.h"

/**
 * A data class of a pattern, editable by the user.
 */
class ArpPattern {
public:

    static const Identifier TREEID_PATTERN;
    static const Identifier TREEID_TIMEBASE;
    static const Identifier TREEID_LOOP_LENGTH;
    static const Identifier TREEID_NOTES;

    static constexpr int DEFAULT_TIMEBASE = 96;


    /**
     * The length of the loop.
     */
    int64 loopLength;


    /**
     * Constructs a new pattern with the specified timebase.
     *
     * @param timebase the timebase in PPQ
     */
    explicit ArpPattern(int timebase = DEFAULT_TIMEBASE);

    /**
     * Copy constructor.
     */
    ArpPattern(ArpPattern &pattern);

    ~ArpPattern();

    ArpPattern& operator=(const ArpPattern &p) noexcept;


    /**
     * Gets the timebase of the pattern.
     *
     * @return the timebase of the pattern in PPQ
     */
    int getTimebase();

    /**
     * Gets the vector of notes in this pattern.
     *
     * @return the vector of notes in this pattern.
     */
    std::vector<ArpNote> &getNotes();


    /**
     * Builds events from this pattern.
     *
     * @return ArpBuiltEvents built from this pattern
     */
    ArpBuiltEvents buildEvents();


    /**
     * Gets this pattern's mutex.
     *
     * @return this pattern's mutex
     */
    std::recursive_mutex &getMutex();


    /**
     * Serializes this pattern into a ValueTree.
     *
     * @return the value tree representing this pattern
     */
    ValueTree toValueTree();

    /**
     * Serializes this pattern and saves it to the specified file.
     *
     * @param file the file where the pattern is to be saved
     */
    void toFile(const File &file);

    /**
     * Deserializes the specified ValueTree into the pattern it represents.
     *
     * @param tree the tree to deserialize
     * @return the pattern represented by the ValueTree (empty if failed)
     */
    static ArpPattern fromValueTree(ValueTree &tree);

    /**
     * Loads the specified file and deserializes it into the pattern it represents.
     *
     * @param file the file to load
     * @return the pattern represented by the file (empty if failed)
     */
    static ArpPattern fromFile(const File &file);

private:

    /**
     * The timebase of the pattern.
     * Defines the amount of pulses in one beat.
     */
    int timebase;

    /**
     * The notes in the pattern.
     */
    std::vector<ArpNote> notes;

    /**
     * The pattern's mutex.
     */
    std::recursive_mutex mutex;
};
