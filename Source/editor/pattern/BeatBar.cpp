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

#include "PatternEditorView.h"
#include "../style/Colours.h"
#include "../style/DragActionTolerances.h"
#include "../../util/Defer.h"

#include "BeatBar.h"

const int TEXT_OFFSET = 6;

BeatBar::BeatBar(LibreArp &p, EditorState &e, PatternEditorView &ec)
        : processor(p), state(e), view(ec) {

    setOpaque(true);
}

void BeatBar::paint(juce::Graphics &g) {
    auto &pattern = processor.getPattern();

    // Draw background
    g.setColour(Style::BEATBAR_BACKGROUND_COLOUR);
    g.fillRect(getLocalBounds());
    g.setColour(Style::BEATBAR_BORDER_COLOUR);
    g.fillRect(0, getHeight() - 1, getWidth(), 1);

    auto loopStartLine = pulseToX(pattern.loopStart);
    auto loopEndLine = pulseToX(pattern.loopEnd);

    // Draw outside-the-loop area
    g.setColour(Style::LOOP_OUTSIDE_COLOUR);
    if (loopStartLine > 0) g.fillRect(0, 0, loopStartLine, getHeight());
    if (loopEndLine < getWidth()) g.fillRect(loopEndLine, 0, getWidth() - loopEndLine, getHeight());

    // Draw beat lines
    g.setFont(20);
    int startingPulse = (xToPulse(0, false) / pattern.getTimebase()) * pattern.getTimebase();
    int endingPulse = (xToPulse(getWidth(), false) / pattern.getTimebase() + 1) * pattern.getTimebase();
    for (int i = startingPulse; i < endingPulse; i += pattern.getTimebase()) {
        g.setColour(Style::BEATBAR_LINE_COLOUR);
        g.fillRect(pulseToX(i) - 2, 0, 4, getHeight());

        g.setColour(Style::BEATBAR_NUMBER_COLOUR);
        g.drawText(juce::String(1 + i / pattern.getTimebase()), pulseToX(i) + TEXT_OFFSET, 0, 32, getHeight(), juce::Justification::centredLeft);
    }

    // Draw loop lines
    g.setColour(Style::LOOP_LINE_COLOUR);
    g.fillRect(loopStartLine, 0, 4, getHeight());
    g.fillRect(loopEndLine, 0, 4, getHeight());
}

void BeatBar::mouseMove(const juce::MouseEvent& event) {
    mouseAnyMove(event);
    mouseDetermineDragAction(event);
    updateMouseCursor();
}

void BeatBar::mouseDrag(const juce::MouseEvent& event) {
    mouseAnyMove(event);
    defer d([this] { updateMouseCursor(); });

    if (event.mods.isLeftButtonDown() && !event.mods.isRightButtonDown() && !event.mods.isMiddleButtonDown()) {
        switch (dragAction.type) {
            case DragAction::TYPE_LOOP_START_RESIZE:
                loopStartResize(event);
                return;
            case DragAction::TYPE_LOOP_END_RESIZE:
                loopEndResize(event);
                return;
            case DragAction::TYPE_LOOP_MOVE:
                loopMove(event);
                return;
            default:
                return;
        }
    }
}

void BeatBar::mouseAnyMove(const juce::MouseEvent& event) {
    snapEnabled = !(event.mods.isAltDown() || (event.mods.isCtrlDown() && event.mods.isShiftDown()));
    mouseCursor = juce::MouseCursor::NormalCursor;
}

void BeatBar::mouseDetermineDragAction(const juce::MouseEvent& event) {\
    auto &pattern = processor.getPattern();
    std::scoped_lock lock(pattern.getMutex());
    setTooltip("");

    auto loopStartLine = pulseToX(pattern.loopStart);
    auto loopEndLine = pulseToX(pattern.loopEnd);

    {
        auto loopMinX = loopStartLine - Style::LINE_RESIZE_TOLERANCE;
        auto loopMaxX = loopStartLine + Style::LINE_RESIZE_TOLERANCE;
        if (event.x >= loopMinX && event.x <= loopMaxX) {
            setTooltip("Drag to resize the loop");
            mouseCursor = juce::MouseCursor::LeftRightResizeCursor;
            dragAction.basicDragAction(DragAction::TYPE_LOOP_START_RESIZE);
            return;
        }
    }

    {
        auto loopMinX = loopEndLine - Style::LINE_RESIZE_TOLERANCE;
        auto loopMaxX = loopEndLine + Style::LINE_RESIZE_TOLERANCE;
        if (event.x >= loopMinX && event.x <= loopMaxX) {
            setTooltip("Drag to resize the loop");
            mouseCursor = juce::MouseCursor::LeftRightResizeCursor;
            dragAction.basicDragAction(DragAction::TYPE_LOOP_END_RESIZE);
            return;
        }
    }

    if (event.x >= loopStartLine && event.x <= loopEndLine) {
        setTooltip("Drag to move the loop");
        mouseCursor = juce::MouseCursor::DraggingHandCursor;
        dragAction.offsetDragAction(
                DragAction::TYPE_LOOP_MOVE,
                xToPulse(event.x) - pattern.loopStart,
                pattern.loopLength());
        return;
    }

    dragAction.basicDragAction();
}

void BeatBar::mouseWheelMove(const juce::MouseEvent &event, const juce::MouseWheelDetails &wheel) {
    if (event.mods.isShiftDown()) {
        view.zoomPattern(0, wheel.deltaY);
    } else {
        view.zoomPattern(wheel.deltaY, 0);
    }
}

void BeatBar::mouseDown(const juce::MouseEvent& event) {
    if (!event.mods.isLeftButtonDown() && !event.mods.isRightButtonDown() && event.mods.isMiddleButtonDown()) {
        view.resetPatternOffset();
        return;
    }

    Component::mouseDown(event);
}

void BeatBar::mouseUp(const juce::MouseEvent& event) {
    mouseDetermineDragAction(event);
    repaint();
}

void BeatBar::updateMouseCursor() {
    if (mouseCursor != getMouseCursor()) {
        setMouseCursor(mouseCursor);
    }
}


void BeatBar::DragAction::basicDragAction(uint8_t type) {
    this->type = type;
}

void BeatBar::DragAction::offsetDragAction(uint8_t type, int64_t startOffset, int64_t loopLength) {
    this->type = type;
    this->startOffset = startOffset;
    this->loopLength = loopLength;
}
