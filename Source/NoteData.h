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
struct NoteData {

    static const juce::Identifier TREEID_NOTE_DATA;
    static const juce::Identifier TREEID_NOTE_NUMBER;
    static const juce::Identifier TREEID_VELOCITY;
    static const juce::Identifier TREEID_PAN;

    constexpr static const double DEFAULT_VELOCITY = 0.8;

    /**
     * The index of the note among the input notes.
     */
    int noteNumber = 0;

    /**
     * The velocity of the note.
     */
    double velocity = DEFAULT_VELOCITY;

    /**
     * The panning of the note.
     */
    double pan = 0;


    /**
     * Serializes this data into a ValueTree.
     *
     * @return a ValueTree representing this note
     */
    [[nodiscard]] juce::ValueTree toValueTree() const;

    /**
     * Deserializes the specified ValueTree into note data.
     *
     * @param tree the tree to deserialize
     * @return the note represented by the ValueTree
     */
    static NoteData fromValueTree(juce::ValueTree &tree);
};


