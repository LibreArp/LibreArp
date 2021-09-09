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

#include "../../LibreArp.h"
#include "LoopEditor.h"
#include "PulseConvertor.h"

class PatternEditorView;

class BeatBar :
        public juce::Component,
        public juce::SettableTooltipClient,
        PulseConvertor<BeatBar>,
        LoopEditor<BeatBar>
{

    friend PulseConvertor;
    friend LoopEditor;


    struct DragAction {

        static const uint8_t TYPE_MASK = 0xF0;

        static const uint8_t TYPE_NONE = 0x00;

        static const uint8_t TYPE_LOOP = 0x10;
        static const uint8_t TYPE_LOOP_START_RESIZE = 0x10;
        static const uint8_t TYPE_LOOP_END_RESIZE = 0x11;
        static const uint8_t TYPE_LOOP_MOVE = 0x12;


        /**
         * The type of the dragging action.
         */
        uint8_t type = TYPE_NONE;

        int64_t startOffset;
        int64_t loopLength;

        void basicDragAction(uint8_t type = TYPE_NONE);

        void offsetDragAction(uint8_t type, int64_t startOffset, int64_t loopLength);
    };

public:


    explicit BeatBar(LibreArp &p, EditorState &e, PatternEditorView &ec);

    void paint(juce::Graphics &g) override;

    void mouseMove(const juce::MouseEvent& event) override;
    void mouseDrag(const juce::MouseEvent& event) override;
    void mouseWheelMove(const juce::MouseEvent &event, const juce::MouseWheelDetails &wheel) override;
    void mouseDown(const juce::MouseEvent& event) override;
    void mouseUp(const juce::MouseEvent& event) override;

    /**
     * Fired on any cursor movement (dragging or non-dragging).
     */
    void mouseAnyMove(const juce::MouseEvent &event);

    /**
     * Sets the editor's current drag action according to the mouse position.
     */
    void mouseDetermineDragAction(const juce::MouseEvent &event);

private:

    LibreArp &processor;
    EditorState &state;
    PatternEditorView &view;

    bool snapEnabled = true;

    DragAction dragAction;

    /**
     * The desired mouse cursor that will actually be changed at the end of a mouse event.
     */
    juce::MouseCursor mouseCursor = juce::MouseCursor::NormalCursor;

    void updateMouseCursor();
};


