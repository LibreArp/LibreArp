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

#include "NoteData.h"

/**
 * A data class of built events of a pattern, ready for playback.
 */
class ArpBuiltEvents {
public:

    /**
     * Data class containing information about a playing note and its channel number.
     */
    class PlayingNote {
    public:

        explicit PlayingNote(int noteNumber, int outChannel);

        int noteNumber;
        int outChannel;
    };

    /**
     * Data class of a single event in time. Contains the time the event fires (in the set timebase) and indices of
     * on-data and off-data.
     */
    class Event {
    public:

        /**
         * The time in the pattern on which the event fires.
         */
        int64_t time;

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
        PlayingNote lastNote = PlayingNote(-1, -1);

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



    /**
     * The timebase of the built pattern.
     */
    int timebase;

    /**
     * The loop length of the built pattern.
     */
    int64_t loopLength;
};

bool operator> (ArpBuiltEvents::PlayingNote const &a, ArpBuiltEvents::PlayingNote const &b);
bool operator< (ArpBuiltEvents::PlayingNote const &a, ArpBuiltEvents::PlayingNote const &b);
bool operator>=(ArpBuiltEvents::PlayingNote const &a, ArpBuiltEvents::PlayingNote const &b);
bool operator<=(ArpBuiltEvents::PlayingNote const &a, ArpBuiltEvents::PlayingNote const &b);
bool operator==(ArpBuiltEvents::PlayingNote const &a, ArpBuiltEvents::PlayingNote const &b);
