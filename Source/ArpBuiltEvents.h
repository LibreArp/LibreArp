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

#include <set>
#include "JuceHeader.h"
#include "NoteData.h"

/**
 * A data class of built events of a pattern, ready for playback.
 */
class ArpBuiltEvents {
public:

    /**
     * Data class of a single event in time. Contains the time the event fires (in the set timebase) and indices of
     * on-data and off-data.
     */
    class Event {
    public:

        /**
         * The time in the pattern on which the event fires.
         */
        int64 time;

        /**
         * The indices of on-data.
         */
        std::set<unsigned long> ons;

        /**
         * The indices of off-data.
         */
        std::set<unsigned long> offs;
    };

    /**
     * The event data.
     */
    std::vector<Event> events;

    /**
     * The data of notes in the pattern.
     */
    std::vector<NoteData> data;



    /**
     * The timebase of the built pattern.
     */
    int timebase;

    /**
     * The loop length of the built pattern.
     */
    int64 loopLength;
};


