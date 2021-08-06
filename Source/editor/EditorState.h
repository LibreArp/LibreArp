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

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_data_structures/juce_data_structures.h>


class EditorState {
public:

    static const juce::Identifier TREEID_EDITOR_STATE;
    static const juce::Identifier TREEID_WIDTH;
    static const juce::Identifier TREEID_HEIGHT;
    static const juce::Identifier TREEID_DIVISOR;
    static const juce::Identifier TREEID_LAST_NOTE_LENGTH;
    static const juce::Identifier TREEID_PIXELS_PER_BEAT;
    static const juce::Identifier TREEID_PIXELS_PER_NOTE;
    static const juce::Identifier TREEID_OFFSET_X;
    static const juce::Identifier TREEID_OFFSET_Y;

    // Main
    int width = 640;
    int height = 480;

    // Pattern editor
    int divisor = 4;
    int64_t lastNoteLength = -1;
    int pixelsPerBeat = 100;
    int pixelsPerNote = 12;
    int offsetX = 0;
    int offsetY = 0;

    [[nodiscard]] juce::ValueTree toValueTree() const;
    static EditorState fromValueTree(juce::ValueTree &tree);

};


