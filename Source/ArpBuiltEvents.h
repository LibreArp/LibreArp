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

class ArpBuiltEvents {
public:

    class Event {
    public:
        int64 time;
        std::set<unsigned long> ons;
        std::set<unsigned long> offs;
    };



    /**
     * Class of note data in an event.
     */
    class EventNoteData {
    public:

        /**
         * The index of the note among the input notes.
         */
        int noteNumber;

        /**
         * The velocity of the note.
         */
        double velocity;

        /**
         * The panning of the note.
         */
        double pan;



        /**
         * The last played MIDI note number.
         */
        int lastNote = -1;

        /**
         * The index of the note in the pattern from which the events were built.
         */
        unsigned long noteIndex = 0;



        /**
         * Creates EventNoteData from NoteData.
         *
         * @param orig
         * @return
         */
        static EventNoteData of(NoteData &orig, unsigned long noteIndex);
    };



    /**
     * The event data.
     */
    std::vector<Event> events;

    /**
     * The data of notes in the pattern.
     */
    std::vector<EventNoteData> data;

    int timebase;
    int64 loopLength;
};


