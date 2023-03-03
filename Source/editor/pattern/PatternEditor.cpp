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

#include "../../util/Defer.h"

#include "PatternEditor.h"
#include "PatternEditorView.h"
#include "../style/Colours.h"
#include "../style/DragActionTolerances.h"


PatternEditor::PatternEditor(LibreArp &p, EditorState &e, PatternEditorView &ec) :
        processor(p),
        state(e),
        view(ec)
{
    setOpaque(true);

    cursorPulse = 0;
    if (state.lastNoteLength < 1) {
        state.lastNoteLength = processor.getPattern().getTimebase() / state.divisor;
    }
    snapEnabled = true;
    selection = juce::Rectangle<int>(0, 0, 0, 0);

    cursorNote = 0;
    lastPlayPositionX = 0;
    lastNumInputNotes = 0;

    timeSelectionStart = 0;
    timeSelectionEnd = 0;

    setWantsKeyboardFocus(true);
}

void PatternEditor::paint(juce::Graphics &g) {
    view.updateDisplayDimensions();

    ArpPattern &pattern = processor.getPattern();
    int pixelsPerNote = state.displayPixelsPerNote;
    int offsetX = static_cast<int>(state.displayOffsetX);
    int offsetY = static_cast<int>(state.displayOffsetY);

    auto unoffsDrawRegion = g.getClipBounds();
    auto drawRegion = unoffsDrawRegion;
    drawRegion.translate(-offsetX, -offsetY);

    // Draw background
    g.setColour(Style::EDITOR_BACKGROUND_COLOUR);
    g.fillRect(unoffsDrawRegion);

    // Draw bars
    if (processor.getTimeSigDenominator() > 0 && processor.getTimeSigDenominator() <= 32) {
        g.setColour(Style::BAR_SHADE_COLOUR);
        int barPulses = (pattern.getTimebase() * processor.getTimeSigNumerator() * 4) / processor.getTimeSigDenominator();
        int twoBarPulses = 2 * barPulses;
        int startingPulse = (xToPulse(0, false) / twoBarPulses - 1) * twoBarPulses;
        int endingPulse = (xToPulse(getWidth(), false) / twoBarPulses + 1) * twoBarPulses;
        for (int i = startingPulse + twoBarPulses; i < endingPulse; i += twoBarPulses) {
            g.fillRect(pulseToX(i), unoffsDrawRegion.getY(),
                    pulseToAbsX(barPulses), unoffsDrawRegion.getHeight());
        }
    }

    // Draw octave 0
    auto numInputNotes = processor.getNumInputNotes();
    int noteZeroY = noteToY(-1);
    int topNoteY = noteToY(numInputNotes - 1);
    int octaveHeight = noteZeroY - topNoteY;
    if (numInputNotes > 0)
        g.setColour(Style::ZERO_OCTAVE_COLOUR);
    else
        g.setColour(Style::ZERO_LINE_COLOUR);
    g.fillRect(juce::Rectangle<int>(unoffsDrawRegion.getX(), topNoteY, unoffsDrawRegion.getWidth(), octaveHeight));

    // Draw gridlines
    // - Horizontal
    g.setColour(Style::EDITOR_GRIDLINES_COLOUR);
    int startingNote = yToNote(unoffsDrawRegion.getBottom()) - 1;
    int endingNote = yToNote(unoffsDrawRegion.getY()) + 1;
    for (int i = startingNote; i < endingNote; i++) {
        g.fillRect(0, noteToY(i) - 1, getWidth(), 2);
    }

    // - Vertical
    float stepInc = (float) pattern.getTimebase() / (float) state.divisor;
    int si = (int) stepInc;
    int startingPulse = (xToPulse(unoffsDrawRegion.getX(), false) / si - 1) * si;
    int endingPulse = (xToPulse(unoffsDrawRegion.getRight(), false) / si + 1) * si;
    for (float i = startingPulse; i < endingPulse; i += stepInc) {
        g.fillRect(pulseToX((int) i) - 1, 0, 2, getHeight());
    }

    int beatInc = pattern.getTimebase();
    startingPulse = (xToPulse(unoffsDrawRegion.getX(), false) / beatInc - 1) * beatInc;
    endingPulse = (xToPulse(unoffsDrawRegion.getRight(), false) / beatInc + 1) * beatInc;
    for (int i = startingPulse; i < endingPulse; i += beatInc) {
        g.fillRect(pulseToX(i) - 2, 0, 4, getHeight());
    }

    // Draw octaves
    if (numInputNotes > 0) {
        g.setColour(Style::OCTAVE_LINE_COLOUR);

        int startingNote = (yToNote(unoffsDrawRegion.getBottom()) / numInputNotes - 1) * numInputNotes - 1;
        int endingNote = (yToNote(unoffsDrawRegion.getY()) / numInputNotes + 1) * numInputNotes;
        for (int i = startingNote; i < endingNote; i += numInputNotes) {
            g.fillRect(unoffsDrawRegion.getX(), noteToY(i), unoffsDrawRegion.getWidth(), 1);
        }
    }

    // Get playback position
    int64_t position = 0;
    if (processor.getPattern().loopLength() > 0) {
        position = processor.getLastPosition();
        if (position > 0) {
            if (processor.getLoopReset() > 0.0) {
                position %= static_cast<int64_t>(processor.getLoopReset() * processor.getPattern().getTimebase());
            }
            position %= pattern.loopLength();
            position += pattern.loopStart;
        }
    }

    // Draw notes
    auto &notes = pattern.getNotes();
    for (size_t i = 0; i < notes.size(); i++) {
        auto &note = notes[i];
        juce::Rectangle<int> noteRect = getRectangleForNote(note);

        if (noteRect.intersects(unoffsDrawRegion)) {
            bool isEnabled = (note.startPoint >= pattern.loopStart && note.endPoint <= pattern.loopEnd);
            bool isPlaying = (position > 0 && position >= note.startPoint && position < note.endPoint);
            bool isSelected = (selectedNotes.find(i) != selectedNotes.end());

            if (isEnabled) {
                if (isSelected) {
                    g.setColour(isPlaying ? Style::NOTE_SELECTED_ACTIVE_FILL_COLOUR : Style::NOTE_SELECTED_FILL_COLOUR);
                } else {
                    g.setColour(isPlaying ? Style::NOTE_ACTIVE_FILL_COLOUR : Style::NOTE_FILL_COLOUR);
                }
            } else {
                if (isSelected) {
                    g.setColour(Style::NOTE_SELECTED_DISABLED_FILL_COLOUR);
                } else {
                    g.setColour(Style::NOTE_DISABLED_FILL_COLOUR);
                }
            }

            g.fillRect(noteRect);

            g.setColour(Style::NOTE_VELOCITY_COLOUR);
            g.fillRect(noteRect.withTrimmedBottom(static_cast<int>(pixelsPerNote * note.data.velocity)));

            g.setColour(Style::NOTE_BORDER_COLOUR);
            g.drawRect(noteRect, 2);
        }
    }

    // Draw cursor indicator
    if (cursorActive) {
        g.setColour(Style::CURSOR_TIME_COLOUR);
        auto cursorPulseX = pulseToX(cursorPulse);
        g.fillRect(cursorPulseX, 0, 1, getHeight());
    }

    // Draw loop lines
    auto loopStartLine = pulseToX(pattern.loopStart);
    auto loopEndLine = pulseToX(pattern.loopEnd);
    g.setColour(Style::LOOP_OUTSIDE_COLOUR);
    if (loopStartLine > 0) g.fillRect(0, 0, loopStartLine, getHeight());
    if (loopEndLine < getWidth()) g.fillRect(loopEndLine, 0, getWidth() - loopEndLine, getHeight());

    g.setColour(Style::LOOP_LINE_COLOUR);
    g.fillRect(loopStartLine - 2, 0, 4, getHeight());
    g.fillRect(loopEndLine - 2, 0, 4, getHeight());

    // Draw playback position indicator
    if (lastPlayPositionX > 0) {
        auto positionRect = juce::Rectangle<int>(lastPlayPositionX - offsetX, unoffsDrawRegion.getY(), 1, unoffsDrawRegion.getHeight());
        if (positionRect.intersects(unoffsDrawRegion)) {
            g.setColour(Style::PLAYHEAD_POSITION_COLOUR);
            g.fillRect(positionRect);
        }
    }

    // Selected time border
    if (!selectedNotes.empty()) {
        auto startX = pulseToX(timeSelectionStart);
        auto endX = pulseToX(timeSelectionEnd);

        g.setColour(Style::SELECTED_TIME_BORDER_COLOUR);
        g.fillRect(startX - 1, 0, 2, getHeight());
        g.fillRect(endX - 1, 0, 2, getHeight());

        g.setColour(Style::SELECTED_TIME_BACKGROUND_COLOUR);
        g.fillRect(startX, 0, endX - startX, getHeight());
    }

    // Draw selection
    if (selection.getWidth() != 0 && selection.getHeight() != 0) {
        if (selection.intersects(unoffsDrawRegion)) {
            g.setColour(Style::SELECTION_RECTANGLE_COLOUR);
            g.drawRect(selection, 3);
        }
    }

    if (cursorActive) {
        auto cursorNoteY = noteToY(cursorNote);
        auto cursorNoteRect = juce::Rectangle<int>(unoffsDrawRegion.getX(), cursorNoteY, unoffsDrawRegion.getWidth(), pixelsPerNote);
        if (cursorNoteRect.intersects(unoffsDrawRegion)) {
            g.setColour(Style::CURSOR_NOTE_COLOUR);
            g.fillRect(cursorNoteRect);
        }
    }
}


void PatternEditor::mouseWheelMove(const juce::MouseEvent &event, const juce::MouseWheelDetails &wheel) {
    if (event.mods.isCtrlDown()) {
        // Zooming
        if (event.mods.isShiftDown()) {
            view.zoomPattern(0, wheel.deltaY);
        } else {
            view.zoomPattern(wheel.deltaY, 0);
        }
    } else if (event.mods.isAltDown()) {
        // Note velocity
        if ((dragAction.type & DragAction::TYPE_MASK) == DragAction::TYPE_NOTE) {
            std::scoped_lock lock(this->processor.getPattern().getMutex());
            for (auto &noteOffset : dragAction.noteOffsets) {
                auto &note = this->processor.getPattern().getNotes()[noteOffset.noteIndex];
                note.data.velocity = juce::jmax(0.0, juce::jmin(note.data.velocity + wheel.deltaY * 0.1, 1.0));
            }
            if (dragAction.noteOffsets.size() == 1) {
                auto noteIndex = dragAction.noteOffsets[0].noteIndex;
                auto &note = this->processor.getPattern().getNotes()[noteIndex];
                state.lastNoteVelocity = note.data.velocity;
                state.lastNoteLength = note.endPoint - note.startPoint;
            }
            processor.buildPattern();
        }
    } else {
        // Scrolling
        if (event.mods.isShiftDown()) {
            view.scrollPattern(wheel.deltaY, wheel.deltaX);
        } else {
            view.scrollPattern(wheel.deltaX, wheel.deltaY);
        }
    }
}

void PatternEditor::mouseMove(const juce::MouseEvent &event) {
    mouseAnyMove(event);
    mouseDetermineDragAction(event);
    updateMouseCursor();
}

void PatternEditor::mouseDrag(const juce::MouseEvent &event) {
    mouseAnyMove(event);
    defer d([this]() { updateMouseCursor(); });

    if (event.mods.isLeftButtonDown() && !event.mods.isRightButtonDown() && !event.mods.isMiddleButtonDown()) {
        switch (dragAction.type) {
            case DragAction::TYPE_LOOP_START_RESIZE:
                loopStartResize(event);
                return;
            case DragAction::TYPE_LOOP_END_RESIZE:
                loopEndResize(event);
                return;
            case DragAction::TYPE_NOTE_START_RESIZE:
                noteStartResize(event);
                return;
            case DragAction::TYPE_NOTE_END_RESIZE:
                noteEndResize(event);
                return;
            case DragAction::TYPE_NOTE_MOVE:
                noteMove(event);
                return;
            case DragAction::TYPE_SELECTION_DRAG:
                select(event);
                return;
            case DragAction::TYPE_STRETCH_START:
                selectionStartStretch(event);
                return;
            case DragAction::TYPE_STRETCH_END:
                selectionEndStretch(event);
                return;
            default:
                return;
        }
    }

    if (!event.mods.isLeftButtonDown() && event.mods.isRightButtonDown() && !event.mods.isMiddleButtonDown()) {
        noteDelete(event);
        return;
    }
}

void PatternEditor::updateMouseCursor() {
    if (mouseCursor != getMouseCursor()) {
        setMouseCursor(mouseCursor);
    }
}

void PatternEditor::mouseAnyMove(const juce::MouseEvent &event) {
    repaint(pulseToX(cursorPulse), 0, 1, getHeight());
    repaint(0, noteToY(cursorNote), getWidth(), state.displayPixelsPerNote);

    cursorPulse = xToPulse(event.x);
    cursorNote = yToNote(event.y);

    snapEnabled = !(event.mods.isAltDown() || (event.mods.isCtrlDown() && event.mods.isShiftDown()));

    mouseCursor = juce::MouseCursor::NormalCursor;

    repaint(pulseToX(cursorPulse), 0, 1, getHeight());
    repaint(0, noteToY(cursorNote), getWidth(), state.displayPixelsPerNote);
}

void PatternEditor::mouseDetermineDragAction(const juce::MouseEvent& event) {
    auto &pattern = processor.getPattern();
    std::scoped_lock lock(pattern.getMutex());
    auto &notes = pattern.getNotes();
    setTooltip("");

    const auto SIZE_TOOLTIP =
        "Drag to change this note's size\n"
        "Alt: disable snapping to grid";
    const auto SIZE_SELECTION_TOOLTIP =
        "Drag to change the selected notes' size\n"
        "Alt: disable snapping to grid";
    const auto MOVE_TOOLTIP =
        "Drag to move this note\n"
        "Right click: delete this note\n"
        "Alt: disable snapping to grid\n"
        "Shift: duplicate note / snap horizontally\n"
        "Ctrl: snap vertically";
    const auto MOVE_SELECTION_TOOLTIP =
        "Drag to move the selected notes\n"
        "Right click: delete this note\n"
        "Alt: disable snapping to grid\n"
        "Shift: duplicate the selected notes / snap horizontally\n"
        "Ctrl: snap vertically";
    const auto STRETCH_SELECTION_TOOLTIP =
        "Drag to stretch the selection\n"
        "Alt: disable snapping to grid";
    const auto RESIZE_LOOP_TOOLTIP =
        "Drag to resize the loop\n"
        "Alt: disable snapping to grid";

    for (uint64_t i = 0; i < notes.size(); i++) {
        auto &note = notes[i];
        auto noteRect = getRectangleForNote(note);
        if (noteRect.contains(event.x, event.y)) {
            if (event.x <= (noteRect.getX() + Style::NOTE_RESIZE_TOLERANCE)) {
                mouseCursor = juce::MouseCursor::LeftEdgeResizeCursor;
                if (selectedNotes.find(i) == selectedNotes.end()) {
                    dragAction.noteDragAction(this, DragAction::TYPE_NOTE_START_RESIZE, i, notes, event);
                    setTooltip(SIZE_TOOLTIP);
                } else {
                    dragAction.noteDragAction(this, DragAction::TYPE_NOTE_START_RESIZE, i, selectedNotes, notes, event);
                    setTooltip(SIZE_SELECTION_TOOLTIP);
                }
                return;
            } else if (event.x >= (noteRect.getX() + noteRect.getWidth() - Style::NOTE_RESIZE_TOLERANCE)) {
                mouseCursor = juce::MouseCursor::RightEdgeResizeCursor;
                if (selectedNotes.find(i) == selectedNotes.end()) {
                    dragAction.noteDragAction(this, DragAction::TYPE_NOTE_END_RESIZE, i, notes, event);
                    setTooltip(SIZE_TOOLTIP);
                } else {
                    dragAction.noteDragAction(this, DragAction::TYPE_NOTE_END_RESIZE, i, selectedNotes, notes, event);
                    setTooltip(SIZE_SELECTION_TOOLTIP);
                }
                return;
            } else {
                mouseCursor = juce::MouseCursor::DraggingHandCursor;
                if (selectedNotes.find(i) == selectedNotes.end()) {
                    dragAction.noteDragAction(this, DragAction::TYPE_NOTE_MOVE, i, notes, event);
                    setTooltip(MOVE_TOOLTIP);
                } else {
                    dragAction.noteDragAction(this, DragAction::TYPE_NOTE_MOVE, i, selectedNotes, notes, event);
                    setTooltip(MOVE_SELECTION_TOOLTIP);
                }
                return;
            }
        }
    }

    {
        if (!selectedNotes.empty()) {
            auto startX = pulseToX(timeSelectionStart);
            auto startMinX = startX - Style::LINE_RESIZE_TOLERANCE;
            auto startMaxX = startX + Style::LINE_RESIZE_TOLERANCE;
            if (event.x >= startMinX && event.x <= startMaxX) {
                setTooltip(STRETCH_SELECTION_TOOLTIP);
                mouseCursor = juce::MouseCursor::LeftRightResizeCursor;
                dragAction.stretchDragAction(DragAction::TYPE_STRETCH_START, selectedNotes, pattern.getNotes(),
                                             timeSelectionStart, timeSelectionEnd);
                return;
            }

            auto endX = pulseToX(timeSelectionEnd);
            auto endMinX = endX - Style::LINE_RESIZE_TOLERANCE;
            auto endMaxX = endX + Style::LINE_RESIZE_TOLERANCE;
            if (event.x >= endMinX && event.x <= endMaxX) {
                setTooltip(STRETCH_SELECTION_TOOLTIP);
                mouseCursor = juce::MouseCursor::LeftRightResizeCursor;
                dragAction.stretchDragAction(DragAction::TYPE_STRETCH_END, selectedNotes, pattern.getNotes(),
                                             timeSelectionStart, timeSelectionEnd);
                return;
            }
        }
    }

    {
        auto loopStartLine = pulseToX(processor.getPattern().loopStart);
        auto loopMinX = loopStartLine - Style::LINE_RESIZE_TOLERANCE;
        auto loopMaxX = loopStartLine + Style::LINE_RESIZE_TOLERANCE;
        if (event.x >= loopMinX && event.x <= loopMaxX) {
            setTooltip(RESIZE_LOOP_TOOLTIP);
            mouseCursor = juce::MouseCursor::LeftRightResizeCursor;
            dragAction.basicDragAction(DragAction::TYPE_LOOP_START_RESIZE);
            return;
        }
    }

    {
        auto loopEndLine = pulseToX(processor.getPattern().loopEnd);
        auto loopMinX = loopEndLine - Style::LINE_RESIZE_TOLERANCE;
        auto loopMaxX = loopEndLine + Style::LINE_RESIZE_TOLERANCE;
        if (event.x >= loopMinX && event.x <= loopMaxX) {
            setTooltip(RESIZE_LOOP_TOOLTIP);
            mouseCursor = juce::MouseCursor::LeftRightResizeCursor;
            dragAction.basicDragAction(DragAction::TYPE_LOOP_END_RESIZE);
            return;
        }
    }

    dragAction.basicDragAction();
}

void PatternEditor::mouseDown(const juce::MouseEvent &event) {
    if (event.mods.isLeftButtonDown() && !event.mods.isRightButtonDown() && !event.mods.isMiddleButtonDown()) {
        if (dragAction.type == DragAction::TYPE_NONE) {
            if (event.mods.isCtrlDown()) {
                if (!event.mods.isShiftDown()) {
                    repaintSelectedNotes();
                    selectedNotes.clear();
                }

                dragAction.selectionDragAction(DragAction::TYPE_SELECTION_DRAG, event.x, event.y);
                repaintNotes();
                repaintSelectedNotes();
            } else {
                repaintSelectedNotes();
                selectedNotes.clear();
                noteCreate(event);
                repaintNotes();
            }
        } else {
            if (dragAction.type == DragAction::TYPE_NOTE_MOVE) {
                repaintNotes();
                repaintSelectedNotes();

                // Pick clicked note properties
                if (selectedNotes.empty()) {
                    auto& offsets = dragAction.noteOffsets;
                    if (offsets.size() == 1) {
                        auto& note = processor.getPattern().getNotes()[offsets[0].noteIndex];
                        state.lastNoteVelocity = note.data.velocity;
                        state.lastNoteLength = note.endPoint - note.startPoint;
                    }
                }

                // Duplicate note
                if (event.mods.isShiftDown() && !event.mods.isCtrlDown() && !event.mods.isAltDown()) {
                    noteDuplicate();
                }

                // Add/remove note from selection
                if (event.mods.isCtrlDown() && !event.mods.isAltDown()) {
                    repaintSelectedNotes();
                    if (!event.mods.isShiftDown()) {
                        selectedNotes.clear();
                        selectedNotes.insert(dragAction.initiatorIndex);

                        std::scoped_lock lock(processor.getPattern().getMutex());
                        auto &note = processor.getPattern().getNotes()[dragAction.initiatorIndex];
                        timeSelectionStart = note.startPoint;
                        timeSelectionEnd = note.endPoint;
                    } else {
                        if (selectedNotes.find(dragAction.initiatorIndex) == selectedNotes.end()) {
                            std::scoped_lock lock(processor.getPattern().getMutex());
                            auto &note = processor.getPattern().getNotes()[dragAction.initiatorIndex];

                            if (selectedNotes.empty()) {
                                timeSelectionStart = note.startPoint;
                                timeSelectionEnd = note.endPoint;
                            } else {
                                if (timeSelectionStart > note.startPoint) timeSelectionStart = note.startPoint;
                                if (timeSelectionEnd < note.endPoint) timeSelectionEnd = note.endPoint;
                            }
                            selectedNotes.insert(dragAction.initiatorIndex);
                        } else {
                            selectedNotes.erase(dragAction.initiatorIndex);
                        }
                    }
                    repaintSelectedNotes();
                }
            }
        }

        Component::mouseDown(event);
        return;
    }

    if (!event.mods.isLeftButtonDown() && event.mods.isRightButtonDown() && !event.mods.isMiddleButtonDown()) {
        deselectAll();
        noteDelete(event);
        Component::mouseDown(event);
        return;
    }

    if (!event.mods.isLeftButtonDown() && !event.mods.isRightButtonDown() && event.mods.isMiddleButtonDown()) {
        if (!event.mods.isAltDown() && !event.mods.isShiftDown() && !event.mods.isCtrlDown()) {
            view.resetPatternOffset();
            return;
        }

        if (event.mods.isAltDown() && !event.mods.isShiftDown() && !event.mods.isCtrlDown()) {
            if (dragAction.type == DragAction::TYPE_NOTE_MOVE) {
                noteResetVelocity();
                return;
            }
        }
    }

    Component::mouseDown(event);
}

void PatternEditor::mouseUp(const juce::MouseEvent &event) {
    repaint(selection);
    selection = juce::Rectangle<int>(0, 0, 0, 0);
    mouseAnyMove(event);
    mouseDetermineDragAction(event);
    repaintNotes();
    updateMouseCursor();
}

void PatternEditor::mouseEnter(const juce::MouseEvent& event) {
    Component::mouseEnter(event);
    cursorActive = true;
    repaint();
}

void PatternEditor::mouseExit(const juce::MouseEvent& event) {
    Component::mouseExit(event);
    cursorActive = false;
    repaint();
}

bool PatternEditor::keyPressed(const juce::KeyPress &key) {
    if (key == juce::KeyPress::deleteKey || key == juce::KeyPress::numberPadDelete) {
        deleteSelected();
        return true;
    }

    if (key.isKeyCode(juce::KeyPress::upKey)) {
        moveSelectedUp(key.getModifiers().isCtrlDown());
        return true;
    }

    if (key.isKeyCode(juce::KeyPress::downKey)) {
        moveSelectedDown(key.getModifiers().isCtrlDown());
        return true;
    }

    if (key == juce::KeyPress::createFromDescription("CTRL+B")) {
        duplicateSelection(false);
        return true;
    }

    if (key == juce::KeyPress::createFromDescription("CTRL+SHIFT+B")) {
        duplicateSelection(true);
        return true;
    }

    if (key == juce::KeyPress::createFromDescription("CTRL+A")) {
        selectAll();
        return true;
    }

    if (key == juce::KeyPress::createFromDescription("CTRL+D")) {
        deselectAll();
        return true;
    }

    return false;
}


void PatternEditor::noteStartResize(const juce::MouseEvent& event) {
    std::scoped_lock lock(processor.getPattern().getMutex());

    auto timebase = processor.getPattern().getTimebase();
    auto &notes = processor.getPattern().getNotes();

    // TODO repaint according to dragAction
    repaintNotes();
    repaintSelectedNotes();
    for (auto &noteOffset : dragAction.noteOffsets) {
        auto &note = notes[noteOffset.noteIndex];
        int64_t minSize = (snapEnabled) ? (timebase / state.divisor) : 1;
        note.startPoint = juce::jmax((int64_t) 0, juce::jmin(xToPulse(event.x) + noteOffset.startOffset, note.endPoint - minSize));

        state.lastNoteLength = note.endPoint - note.startPoint;
    }

    getNoteSelectionBorder(timeSelectionStart, timeSelectionEnd);
    processor.buildPattern();
    repaintNotes();
    repaintSelectedNotes();
    mouseCursor = juce::MouseCursor::LeftEdgeResizeCursor;
}

void PatternEditor::noteEndResize(const juce::MouseEvent& event) {
    std::scoped_lock lock(processor.getPattern().getMutex());

    auto timebase = processor.getPattern().getTimebase();
    auto &notes = processor.getPattern().getNotes();

    // TODO repaint according to dragAction
    repaintNotes();
    repaintSelectedNotes();
    for (auto &noteOffset : dragAction.noteOffsets) {
        auto &note = notes[noteOffset.noteIndex];
        int64_t minSize = (snapEnabled) ? (timebase / state.divisor) : 1;
        note.endPoint = juce::jmax(xToPulse(event.x) + noteOffset.endOffset, note.startPoint + minSize);

        state.lastNoteLength = note.endPoint - note.startPoint;
    }

    getNoteSelectionBorder(timeSelectionStart, timeSelectionEnd);
    processor.buildPattern();
    repaintNotes();
    repaintSelectedNotes();
    mouseCursor = juce::MouseCursor::RightEdgeResizeCursor;
}

void PatternEditor::noteMove(const juce::MouseEvent& event) {
    std::scoped_lock lock(processor.getPattern().getMutex());

    // TODO repaint according to dragAction
    repaintNotes();
    repaintSelectedNotes();
    auto &notes = processor.getPattern().getNotes();
    for (auto &noteOffset : dragAction.noteOffsets) {
        auto &note = notes[noteOffset.noteIndex];
        auto noteLength = note.endPoint - note.startPoint;
        auto wantedEnd = xToPulse(event.x) + noteOffset.endOffset;

        if (!event.mods.isCtrlDown()) {
            note.endPoint = juce::jmax(wantedEnd, noteLength);
            note.startPoint = note.endPoint - noteLength;
        }

        if (!event.mods.isShiftDown()) {
            note.data.noteNumber = yToNote(event.y) + noteOffset.noteOffset;
        }
    }

    getNoteSelectionBorder(timeSelectionStart, timeSelectionEnd);
    processor.buildPattern();
    repaintNotes();
    repaintSelectedNotes();

    mouseCursor = juce::MouseCursor::DraggingHandCursor;
}

void PatternEditor::noteDuplicate() {
    std::scoped_lock lock(processor.getPattern().getMutex());

    auto &notes = processor.getPattern().getNotes();
    for (auto &noteOffset : dragAction.noteOffsets) {
        processor.getPattern().getNotes().push_back(notes[noteOffset.noteIndex]);
    }
    processor.buildPattern();
    repaintNotes();
}

void PatternEditor::noteResetVelocity() {
    std::scoped_lock lock(processor.getPattern().getMutex());

    auto &notes = processor.getPattern().getNotes();
    for (auto &noteOffset : dragAction.noteOffsets) {
        notes[noteOffset.noteIndex].data.velocity = NoteData::DEFAULT_VELOCITY;
    }
    if (!dragAction.noteOffsets.empty()) {
        state.lastNoteVelocity = NoteData::DEFAULT_VELOCITY;
    }
    if (dragAction.noteOffsets.size() == 1) {
        auto noteIndex = dragAction.noteOffsets[0].noteIndex;
        auto &note = this->processor.getPattern().getNotes()[noteIndex];
        state.lastNoteLength = note.endPoint - note.startPoint;
    }
    processor.buildPattern();
    repaintNotes();
}

void PatternEditor::noteCreate(const juce::MouseEvent &event) {
    std::scoped_lock lock(processor.getPattern().getMutex());

    auto &pattern = processor.getPattern();
    auto &notes = pattern.getNotes();
    auto pulse = xToPulse(event.x, true, true);
    if (event.mods.isShiftDown()) {
        state.lastNoteLength = pattern.getTimebase() / state.divisor;
    }

    ArpNote note = ArpNote();
    note.startPoint = pulse;
    note.endPoint = note.startPoint + state.lastNoteLength;
    note.data.noteNumber = yToNote(event.y);
    note.data.velocity = state.lastNoteVelocity;

    auto index = notes.size();
    notes.push_back(note);

    processor.buildPattern();
    repaintNotes();

    if (event.mods.isShiftDown()) {
        dragAction.noteDragAction(this, DragAction::TYPE_NOTE_END_RESIZE, index, notes, event, false);
    } else {
        dragAction.noteDragAction(this, DragAction::TYPE_NOTE_MOVE, index, notes, event);
    }
}

void PatternEditor::noteDelete(const juce::MouseEvent &event) {
    std::scoped_lock lock(processor.getPattern().getMutex());

    auto &pattern = processor.getPattern();
    auto &notes = pattern.getNotes();
    bool erased = false;

    for (auto it = notes.begin(); it != notes.end(); it++) {
        auto &note = *it;
        auto noteRect = getRectangleForNote(note);

        if (noteRect.contains(event.x, event.y)) {
            notes.erase(it);
            erased = true;
            dragAction.basicDragAction();
            break;
        }
    }

    if (erased) {
        processor.buildPattern();
        repaintNotes();
        repaintSelectedNotes();
    }

    updateMouseCursor();
}


void PatternEditor::selectAll() {
    repaintSelectedNotes();
    auto &notes = processor.getPattern().getNotes();
    for (size_t i = 0; i < notes.size(); i++) {
        selectedNotes.insert(i);
    }
    getNoteSelectionBorder(timeSelectionStart, timeSelectionEnd);
    repaintSelectedNotes();
}

void PatternEditor::deselectAll() {
    repaintSelectedNotes();
    selectedNotes.clear();
}

void PatternEditor::deleteSelected() {
    repaintSelectedNotes();
    auto &notes = processor.getPattern().getNotes();
    for (auto it = selectedNotes.rbegin(); it != selectedNotes.rend(); it++) {
        auto index = *it;
        notes[index] = notes.back();
        notes.pop_back();
    }
    selectedNotes.clear();
    dragAction.basicDragAction();
    processor.buildPattern();
}

void PatternEditor::moveSelectedUp(bool octave) {
    std::scoped_lock lock(processor.getPattern().getMutex());

    repaintSelectedNotes();
    auto &notes = processor.getPattern().getNotes();
    for (auto index : selectedNotes) {
        if (octave) {
            notes[index].data.noteNumber += processor.getNumInputNotes();
        } else {
            notes[index].data.noteNumber++;
        }
    }
    processor.buildPattern();
    repaintSelectedNotes();
}

void PatternEditor::moveSelectedDown(bool octave) {
    std::scoped_lock lock(processor.getPattern().getMutex());

    repaintSelectedNotes();
    auto &notes = processor.getPattern().getNotes();
    for (auto index : selectedNotes) {
        if (octave) {
            notes[index].data.noteNumber -= processor.getNumInputNotes();
        } else {
            notes[index].data.noteNumber--;
        }
    }
    processor.buildPattern();
    repaintSelectedNotes();
}


void PatternEditor::select(const juce::MouseEvent& event) {
    repaint(selection);
    repaintSelectedNotes();
    selection = juce::Rectangle<int>(juce::Point<int>(event.x, event.y), juce::Point<int>(dragAction.startX, dragAction.startY));
    repaint(selection);

    if (!event.mods.isShiftDown()) {
        selectedNotes.clear();
    }

    auto &notes = processor.getPattern().getNotes();
    for(size_t i = 0; i < notes.size(); i++) {
        auto &note = notes[i];
        auto noteRect = getRectangleForNote(note);
        if (selection.intersects(noteRect)) {
            selectedNotes.insert(i);
        }
    }

    int64_t notesStart, notesEnd;
    if (getNoteSelectionBorder(notesStart, notesEnd)) {
	bool snap = !event.mods.isAltDown();
        timeSelectionStart = juce::jmin(notesStart, xToPulse(selection.getX(), snap));
        timeSelectionEnd = juce::jmax(notesEnd, xToPulse(selection.getRight(), snap));
    }
    repaintSelectedNotes();
}

void PatternEditor::duplicateSelection(bool back) {
    if (selectedNotes.size() <= 0)
        return;

    repaint();

    auto& pattern = processor.getPattern();
    std::scoped_lock lock(pattern.getMutex());
    auto& notes = pattern.getNotes();

    auto offset = ((back) ? -1 : 1) * (timeSelectionEnd - timeSelectionStart);
    size_t startIndex = notes.size();
    size_t addedNotes = 0;
    for (auto origIndex : selectedNotes) {
        auto newNote = notes[origIndex];
        if (-offset > newNote.startPoint)
            continue;

        newNote.startPoint += offset;
        newNote.endPoint += offset;
        notes.push_back(newNote);
        addedNotes++;
    }

    processor.buildPattern();

    if (addedNotes <= 0)
        return;

    size_t endIndex = startIndex + addedNotes;
    selectedNotes.clear();
    for (size_t i = startIndex; i < endIndex; i++)
        selectedNotes.insert(i);

    getNoteSelectionBorder(timeSelectionStart, timeSelectionEnd);
}


void PatternEditor::selectionStartStretch(const juce::MouseEvent& event) {
    selectionStretch(xToPulse(event.x, !event.mods.isAltDown()), timeSelectionEnd);
}

void PatternEditor::selectionEndStretch(const juce::MouseEvent& event) {
    selectionStretch(timeSelectionStart, xToPulse(event.x, !event.mods.isAltDown()));
}

void PatternEditor::selectionStretch(int64_t selectionStart, int64_t selectionEnd) {
    repaintSelectedNotes();
    auto& pattern = processor.getPattern();
    std::scoped_lock lock(pattern.getMutex());
    auto& notes = pattern.getNotes();

    auto length = static_cast<double>(selectionEnd - selectionStart);
    for (auto selectedNote : dragAction.selectedNotes) {
        auto& note = notes[selectedNote.noteIndex];
        note.startPoint = selectionStart + static_cast<int64_t>(round(selectedNote.relativeStart * length));
        note.endPoint = selectionStart + static_cast<int64_t>(round(selectedNote.relativeEnd * length));
    }
    timeSelectionStart = selectionStart;
    timeSelectionEnd = selectionEnd;
    repaintSelectedNotes();
    processor.buildPattern();
}


void PatternEditor::audioUpdate() {
    if (!processor.wasPlaying) {
        return;
    }

    if (lastTimeSigNumerator != processor.getTimeSigNumerator()
        || lastTimeSigDenominator != processor.getTimeSigDenominator())
    {
        repaint();
    }

    lastTimeSigNumerator = processor.getTimeSigNumerator();
    lastTimeSigDenominator = processor.getTimeSigDenominator();

    int oldPosition = lastPlayPositionX;
    int newPosition;

    auto position = processor.getLastPosition();
    if (position > 0) {
        if (processor.getLoopReset() > 0.0) {
            position %= static_cast<int64_t>(processor.getLoopReset() * processor.getPattern().getTimebase());
        }
        position %= processor.getPattern().loopLength();
        newPosition = pulseToAbsX(processor.getPattern().loopStart + position);
    } else {
        newPosition = 0;
    }

    int offsetX = static_cast<int>(state.displayOffsetX);
    if (oldPosition <= newPosition) {
        repaint(oldPosition - offsetX, 0, newPosition - oldPosition + 1, getHeight());
    } else {
        repaint(oldPosition - offsetX, 0, 1, getHeight());
        repaint(newPosition - offsetX, 0, 1, getHeight());
    }

    lastPlayPositionX = newPosition;

    auto numInputNotes = processor.getNumInputNotes();
    if (numInputNotes != lastNumInputNotes) {
        repaint();
        lastNumInputNotes = numInputNotes;
    } else {
        repaintNotes();
    }
}

void PatternEditor::repaintNotes() {
    std::scoped_lock lock(processor.getPattern().getMutex());
    auto &notes = processor.getPattern().getNotes();

    if (notes.empty()) {
        return;
    }

    auto notesRect = juce::Rectangle<int>::leftTopRightBottom(INT32_MAX, INT32_MAX, 0, 0);
    for(auto &note : notes) {
        auto noteRect = getRectangleForNote(note);
        notesRect.setLeft(juce::jmin(notesRect.getX(), noteRect.getX()));
        notesRect.setTop(juce::jmin(notesRect.getY(), noteRect.getY()));
        notesRect.setRight(juce::jmax(notesRect.getRight(), noteRect.getRight()));
        notesRect.setBottom(juce::jmax(notesRect.getBottom(), noteRect.getBottom()));
    }
    repaint(notesRect);
}

void PatternEditor::repaintSelectedNotes() {
    std::scoped_lock lock(processor.getPattern().getMutex());

    if (selectedNotes.empty()) {
        return;
    }

    auto& notes = processor.getPattern().getNotes();
    int minX = INT32_MAX;
    int maxX = INT32_MIN;
    for (auto i : selectedNotes) {
        auto& note = notes[i];
        int startX = pulseToX(note.startPoint);
        if (startX < minX) minX = startX;

        int endX = pulseToX(note.endPoint);
        if (endX > maxX) maxX = endX;
    }

    int selectionStartX = pulseToX(timeSelectionStart);
    if (selectionStartX < minX) minX = selectionStartX;

    int selectionEndX = pulseToX(timeSelectionEnd);
    if (selectionEndX > maxX) maxX = selectionEndX;

    repaint(juce::Rectangle<int>::leftTopRightBottom(minX - 2, 0, maxX + 2, getHeight()));
}

juce::Rectangle<int> PatternEditor::getRectangleForNote(ArpNote &note) {
    int pixelsPerNote = state.displayPixelsPerNote;

    return {
            pulseToX(note.startPoint),
            noteToY(note.data.noteNumber),
            pulseToAbsX(note.endPoint - note.startPoint),
            pixelsPerNote
    };
}

bool PatternEditor::getNoteSelectionBorder(std::set<uint64_t>& indices,
                                           std::vector<ArpNote>& allNotes,
                                           int64_t& out_start, int64_t& out_end) {
    if (indices.empty()) {
        return false;
    }

    out_start = INT64_MAX;
    out_end = INT64_MIN;

    for (auto i : indices) {
        ArpNote& note = allNotes[i];
        if (note.startPoint < out_start) {
            out_start = note.startPoint;
        }
        if (note.endPoint > out_end) {
            out_end = note.endPoint;
        }
    }

    return true;
}

bool PatternEditor::getNoteSelectionBorder(int64_t& out_start, int64_t& out_end) {
    auto& pattern = processor.getPattern();
    std::scoped_lock lock(pattern.getMutex());
    return getNoteSelectionBorder(selectedNotes, pattern.getNotes(), out_start, out_end);
}

void PatternEditor::DragAction::basicDragAction(uint8_t type) {
    jassert(type == DragAction::TYPE_NONE || (type & DragAction::TYPE_MASK) == DragAction::TYPE_LOOP);
    this->type = type;
}

void PatternEditor::DragAction::noteDragAction(PatternEditor *editor,
                                               uint8_t type,
                                               uint64_t index,
                                               std::vector<ArpNote> &allNotes,
                                               const juce::MouseEvent &event,
                                               bool offset) {
    jassert((type & DragAction::TYPE_MASK) == DragAction::TYPE_NOTE);
    this->type = type;
    this->initiatorIndex = index;
    this->noteOffsets.clear();
    this->noteOffsets.push_back((offset)
            ? createOffset(editor, allNotes, index, event)
            : createOffset(index));
}

void PatternEditor::DragAction::noteDragAction(PatternEditor* editor,
                                               uint8_t type,
                                               uint64_t initiatorIndex,
                                               std::set<uint64_t>& indices,
                                               std::vector<ArpNote>& allNotes,
                                               const juce::MouseEvent& event,
                                               bool offset) {
    jassert((type & DragAction::TYPE_MASK) == DragAction::TYPE_NOTE);
    this->type = type;
    this->initiatorIndex = initiatorIndex;
    this->noteOffsets.clear();
    for (auto index : indices) {
        this->noteOffsets.push_back((offset)
                ? createOffset(editor, allNotes, index, event)
                : createOffset(index));
    }
}

void PatternEditor::DragAction::selectionDragAction(uint8_t type, int startX, int startY) {
    jassert((type & DragAction::TYPE_MASK) == DragAction::TYPE_SELECTION);
    this->type = type;
    this->startX = startX;
    this->startY = startY;
}

void PatternEditor::DragAction::stretchDragAction(uint8_t type,
                                                  std::set<uint64_t>& indices,
                                                  std::vector<ArpNote>& allNotes,
                                                  int64_t timeSelectionStart,
                                                  int64_t timeSelectionEnd) {
    jassert((type & DragAction::TYPE_MASK) == DragAction::TYPE_STRETCH);
    this->type = type;
    this->selectedNotes.clear();

    if (!indices.empty()) {
        double length = static_cast<double>(timeSelectionEnd) - static_cast<double>(timeSelectionStart);

        for (auto i : indices) {
            ArpNote& note = allNotes[i];

            SelectedNote selectedNote;
            selectedNote.noteIndex = i;
            selectedNote.relativeStart = static_cast<double>(note.startPoint - timeSelectionStart) / length;
            selectedNote.relativeEnd = static_cast<double>(note.endPoint - timeSelectionStart) / length;
            selectedNotes.push_back(selectedNote);
        }
    }
}

PatternEditor::DragAction::NoteOffset PatternEditor::DragAction::createOffset(
        PatternEditor *editor,
        std::vector<ArpNote> &allNotes,
        uint64_t noteIndex,
        const juce::MouseEvent &event) {

    auto pulse = editor->xToPulse(event.x);

    auto &note = allNotes[noteIndex];
    NoteOffset offset;
    offset.noteIndex = noteIndex;
    offset.endOffset = note.endPoint - pulse;
    offset.startOffset = note.startPoint - pulse;
    offset.noteOffset = note.data.noteNumber - editor->yToNote(event.y);

    return offset;
}

PatternEditor::DragAction::NoteOffset PatternEditor::DragAction::createOffset(uint64_t noteIndex) {
    NoteOffset offset;
    offset.noteIndex = noteIndex;
    return offset;
}
