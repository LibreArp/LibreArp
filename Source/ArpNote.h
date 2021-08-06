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

#include "NoteData.h"

/**
 * Data of a single note, with a start and end point in the pattern.
 */
class ArpNote {
public:
    static const juce::Identifier TREEID_NOTE;
    static const juce::Identifier TREEID_START_POINT;
    static const juce::Identifier TREEID_END_POINT;

    /**
     * Constructs a note with the specified data, or empty data if unspecified.
     *
     * @param data the note data
     */
    explicit ArpNote(NoteData data = NoteData());

    /**
     * The note data.
     */
    NoteData data;

    /**
     * The start point of the note in the pattern.
     */
    int64_t startPoint;

    /**
     * The end point of the note in the pattern.
     */
    int64_t endPoint;



    /**
     * Serializes this note into a ValueTree.
     *
     * @return a ValueTree representing this note
     */
    juce::ValueTree toValueTree();

    /**
     * Deserializes the specified ValueTree into a note it represents.
     *
     * @param tree the tree to deserialize
     * @return the note represented by the ValueTree
     */
    static ArpNote fromValueTree(juce::ValueTree &tree);
};


