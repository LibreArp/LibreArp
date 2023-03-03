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

#include "../NoteData.h"


struct EditorState {

    static constexpr int DEFAULT_WIDTH = 800;
    static constexpr int DEFAULT_HEIGHT = 600;

    static const juce::Identifier TREEID_EDITOR_STATE;
    static const juce::Identifier TREEID_WIDTH;
    static const juce::Identifier TREEID_HEIGHT;
    static const juce::Identifier TREEID_DIVISOR;
    static const juce::Identifier TREEID_LAST_NOTE_LENGTH;
    static const juce::Identifier TREEID_LAST_NOTE_VELOCITY;
    static const juce::Identifier TREEID_PIXELS_PER_BEAT;
    static const juce::Identifier TREEID_PIXELS_PER_NOTE;
    static const juce::Identifier TREEID_OFFSET_X;
    static const juce::Identifier TREEID_OFFSET_Y;

    // Main
    int width = DEFAULT_WIDTH;
    int height = DEFAULT_HEIGHT;

    // Pattern editor
    int divisor = 4;
    int64_t lastNoteLength = -1;
    double lastNoteVelocity = NoteData::DEFAULT_VELOCITY;

    float targetPixelsPerBeat = 100;
    float targetPixelsPerNote = 12;
    float displayPixelsPerBeat = 100;
    float displayPixelsPerNote = 12;

    float targetOffsetX = 0;        ///< Target X-axis pattern editor offset
    float targetOffsetY = 0;        ///< Target Y-axis pattern editor offset
    float displayOffsetX = 0;       ///< Actually displayed X-axis pattern editor offset (for animation)
    float displayOffsetY = 0;       ///< Actually displayed Y-axis pattern editor offset (for animation)

    [[nodiscard]] juce::ValueTree toValueTree() const;
    static EditorState fromValueTree(juce::ValueTree &tree);

};


