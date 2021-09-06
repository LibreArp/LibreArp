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

#include "BeatBar.h"
#include "PatternEditorView.h"
#include "../style/Colours.h"

const juce::String LOOP_TEXT = "loop"; // NOLINT

const int TEXT_OFFSET = 6;

BeatBar::BeatBar(LibreArp &p, EditorState &e, PatternEditorView *ec)
        : processor(p), state(e), view(ec) {

    setOpaque(true);
}

void BeatBar::paint(juce::Graphics &g) {
    auto &pattern = processor.getPattern();
    auto pixelsPerBeat = state.pixelsPerBeat;

    // Draw background
    g.setColour(Style::BEATBAR_BACKGROUND_COLOUR);
    g.fillRect(getLocalBounds());
    g.setColour(Style::BEATBAR_BORDER_COLOUR);
    g.fillRect(0, getHeight() - 1, getWidth(), 1);

    auto loopStartLine = static_cast<int>((pattern.loopStart / static_cast<float>(pattern.getTimebase())) * pixelsPerBeat) + 1 - state.offsetX;
    auto loopEndLine = static_cast<int>((pattern.loopEnd / static_cast<float>(pattern.getTimebase())) * pixelsPerBeat) + 1 - state.offsetX;

    // Draw outside-the-loop area
    g.setColour(Style::LOOP_OUTSIDE_COLOUR);
    if (loopStartLine > 0) g.fillRect(0, 0, loopStartLine, getHeight());
    if (loopEndLine < getWidth()) g.fillRect(loopEndLine, 0, getWidth() - loopEndLine, getHeight());

    // Draw beat lines
    g.setFont(20);
    int n = 1 + state.offsetX / pixelsPerBeat;
    for (float i = (1 - state.offsetX) % pixelsPerBeat; i < getWidth(); i += pixelsPerBeat, n++) {
        g.setColour(Style::BEATBAR_LINE_COLOUR);
        g.fillRect(juce::roundToInt(i), 0, 4, getHeight());

        g.setColour(Style::BEATBAR_NUMBER_COLOUR);
        g.drawText(juce::String(n), static_cast<int>(i) + TEXT_OFFSET, 0, 32, getHeight(), juce::Justification::centredLeft);
    }

    // Draw loop lines
    g.setColour(Style::LOOP_LINE_COLOUR);
    g.fillRect(loopStartLine, 0, 4, getHeight());
    g.fillRect(loopEndLine, 0, 4, getHeight());
}

void BeatBar::mouseWheelMove(const juce::MouseEvent &event, const juce::MouseWheelDetails &wheel) {
    if (event.mods.isShiftDown()) {
        view->zoomPattern(0, wheel.deltaY);
    } else {
        view->zoomPattern(wheel.deltaY, 0);
    }
}

void BeatBar::mouseDown(const juce::MouseEvent& event) {
    if (!event.mods.isLeftButtonDown() && !event.mods.isRightButtonDown() && event.mods.isMiddleButtonDown()) {
        view->resetPatternOffset();
        return;
    }

    Component::mouseDown(event);
}
