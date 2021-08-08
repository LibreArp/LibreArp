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

const juce::Colour BACKGROUND_COLOUR = juce::Colour(42, 40, 34);
const juce::Colour BOTTOM_LINE_COLOUR = juce::Colour(0, 0, 0);
const juce::Colour BEAT_LINE_COLOUR = juce::Colour(107, 104, 94);
const juce::Colour BEAT_NUMBER_COLOUR = juce::Colour(107, 104, 94);
const juce::Colour LOOP_LINE_COLOUR = juce::Colour(155, 36, 36);
const juce::Colour LOOP_TEXT_COLOUR = juce::Colour((uint8_t) 155, 36, 36);

const juce::String LOOP_TEXT = "loop"; // NOLINT

const int TEXT_OFFSET = 6;

BeatBar::BeatBar(LibreArp &p, EditorState &e, PatternEditorView *ec)
        : processor(p), state(e), view(ec) {

    setSize(1, 1);
    setOpaque(true);
}

void BeatBar::paint(juce::Graphics &g) {
    auto &pattern = processor.getPattern();
    auto pixelsPerBeat = state.pixelsPerBeat;

    // Draw background
    g.setColour(BACKGROUND_COLOUR);
    g.fillRect(getLocalBounds());
    g.setColour(BOTTOM_LINE_COLOUR);
    g.fillRect(0, getHeight() - 1, getWidth(), 1);

    auto loopLine = static_cast<int>((pattern.loopLength / static_cast<float>(pattern.getTimebase())) * pixelsPerBeat) + 1 - state.offsetX;

    // Draw beat lines
    g.setFont(20);
    int n = 1 + state.offsetX / pixelsPerBeat;
    for (float i = (1 - state.offsetX) % pixelsPerBeat; i < getWidth(); i += pixelsPerBeat, n++) {
        g.setColour(BEAT_LINE_COLOUR);
        g.fillRect(juce::roundToInt(i), 0, 4, getHeight());

        g.setColour((i == loopLine) ? LOOP_TEXT_COLOUR : BEAT_NUMBER_COLOUR);
        g.drawText(juce::String(n), static_cast<int>(i) + TEXT_OFFSET, 0, 32, getHeight(), juce::Justification::centredLeft);
    }

    // Draw loop line
    g.setFont(16);
    g.setColour(LOOP_LINE_COLOUR);
    g.fillRect(loopLine, 0, 4, getHeight());

    g.setColour(LOOP_TEXT_COLOUR);
    auto loopTextWidth = g.getCurrentFont().getStringWidth(LOOP_TEXT);
    auto loopLineWithOffset = loopLine - loopTextWidth - TEXT_OFFSET;
    g.drawText(LOOP_TEXT, loopLineWithOffset, 0, loopTextWidth, getHeight(), juce::Justification::centredRight);
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
