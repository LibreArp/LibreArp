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

#include <juce_core/juce_core.h>
#include <juce_data_structures/juce_data_structures.h>

/**
 * The data of a note.
 */
class NoteData {
public:
    static const juce::Identifier TREEID_NOTE_DATA;
    static const juce::Identifier TREEID_NOTE_NUMBER;
    static const juce::Identifier TREEID_VELOCITY;
    static const juce::Identifier TREEID_PAN;

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
     * Constructs new note data.
     */
    NoteData();



    /**
     * Serializes this data into a ValueTree.
     *
     * @return a ValueTree representing this note
     */
    juce::ValueTree toValueTree();

    /**
     * Deserializes the specified ValueTree into note data.
     *
     * @param tree the tree to deserialize
     * @return the note represented by the ValueTree
     */
    static NoteData fromValueTree(juce::ValueTree &tree);
};


