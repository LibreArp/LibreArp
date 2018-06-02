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

#include "../JuceLibraryCode/JuceHeader.h"
#include "ArpEvent.h"
#include "ArpNote.h"
#include "ArpBuiltEvents.h"

class ArpPattern {
public:

    static const Identifier TREEID_PATTERN;
    static const Identifier TREEID_TIMEBASE;
    static const Identifier TREEID_LOOP_LENGTH;
    static const Identifier TREEID_NOTES;

    static constexpr int DEFAULT_TIMEBASE = 96;


    int64 loopLength;

    /**
     * Constructs a new pattern with the specified timebase.
     *
     * @param timebase the timebase in PPQ
     */
    explicit ArpPattern(int timebase = DEFAULT_TIMEBASE);

    ~ArpPattern();


    /**
     * Gets the timebase of the pattern.
     *
     * @return the timebase of the pattern in PPQ
     */
    int getTimebase();

    /**
     * Gets a pointer to the vector of notes in this pattern.
     *
     * @return
     */
    std::vector<ArpNote> &getNotes();


    /**
     * Builds a vector of ArpEvents, sorted by time, from this pattern.
     *
     * @return a vector of ArpEvents
     * @deprecated use buildEvents() instead
     */
     [[deprecated("Replaced by buildEvents()")]]
    std::vector<ArpEvent> build();

    /**
     * Builds events from this pattern.
     *
     * @return ArpBuiltEvents built from this pattern
     */
    ArpBuiltEvents buildEvents();

    /**
     * Gets the pattern as a ValueTree.
     *
     * @return the value tree representing this pattern
     */
    ValueTree toValueTree();


    static ArpPattern fromValueTree(ValueTree &tree);

private:
    int timebase;
    std::vector<ArpNote> notes;
};
