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

const int NOTE_RESIZE_TOLERANCE = 8;
const int LINE_RESIZE_TOLERANCE = 5;


PatternEditor::PatternEditor(LibreArp &p, EditorState &e, PatternEditorView *ec) :
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

    setWantsKeyboardFocus(true);
}

void PatternEditor::paint(juce::Graphics &g) {
    ArpPattern &pattern = processor.getPattern();
    auto pixelsPerBeat = state.pixelsPerBeat;
    auto pixelsPerNote = state.pixelsPerNote;

    auto unoffsDrawRegion = g.getClipBounds();
    auto drawRegion = unoffsDrawRegion;
    drawRegion.translate(-state.offsetX, -state.offsetY);

    // Draw background
    g.setColour(Style::EDITOR_BACKGROUND_COLOUR);
    g.fillRect(unoffsDrawRegion);

    // Draw bars
    if (processor.getTimeSigDenominator() > 0 && processor.getTimeSigDenominator() <= 32) {
        auto beat = (pixelsPerBeat * 4) / processor.getTimeSigDenominator();
        auto bar = beat * processor.getTimeSigNumerator();
        g.setColour(Style::BAR_SHADE_COLOUR);
        int firstBarX = unoffsDrawRegion.getX() - unoffsDrawRegion.getX() % bar - state.offsetX % (bar * 2);
        for (int i = firstBarX; i < unoffsDrawRegion.getWidth(); i += bar * 2) {
            g.fillRect(i + bar, unoffsDrawRegion.getY(), bar, unoffsDrawRegion.getHeight());
        }
    }

    // Draw octave 0
    auto numInputNotes = processor.getNumInputNotes();
    int noteZeroY = noteToY(0);
    if (numInputNotes > 0) {
        g.setColour(Style::ZERO_OCTAVE_COLOUR);
        auto height = numInputNotes * pixelsPerNote;
        auto rect = juce::Rectangle<int>(
                unoffsDrawRegion.getX(), noteZeroY - height + pixelsPerNote, unoffsDrawRegion.getWidth(), height);
        g.fillRect(rect);
    } else {
        g.setColour(Style::ZERO_LINE_COLOUR);
        auto rect = juce::Rectangle<int>(unoffsDrawRegion.getX(), noteZeroY, unoffsDrawRegion.getWidth(), pixelsPerNote);
        g.fillRect(rect);
    }

    // Draw gridlines
    // - Horizontal
    g.setColour(Style::EDITOR_GRIDLINES_COLOUR);
    int horizontalGridlineStart = (getHeight() / 2 - state.offsetY) % pixelsPerNote - pixelsPerNote / 2;
    for (int i = horizontalGridlineStart; i < getHeight(); i += pixelsPerNote) {
        g.fillRect(0, i, getWidth(), 2);
    }

    // - Vertical
    float beatDiv = (pixelsPerBeat / static_cast<float>(state.divisor));
    int beatN = 0;
    for (auto i = static_cast<float>((-state.offsetX) % pixelsPerBeat); i < static_cast<float>(getWidth()); i += beatDiv, beatN++) {
        if (beatN % state.divisor == 0) {
            g.fillRect(juce::roundToInt(i), 0, 4, getHeight());
        } else {
            g.fillRect(juce::roundToInt(i), 0, 2, getHeight());
        }
    }

    // Draw octaves
    if (numInputNotes > 0) {
        g.setColour(Style::OCTAVE_LINE_COLOUR);
        auto pixelsPerOctave = pixelsPerNote * numInputNotes;

        int i = (getHeight() / 2 - state.offsetY) % pixelsPerOctave - pixelsPerNote / 2 + pixelsPerNote;
        for (/* above */; i < getHeight(); i += pixelsPerOctave) {
            g.fillRect(drawRegion.getX(), i, drawRegion.getWidth(), 1);
        }
    }

    // Get playback position
    auto position = processor.getLastPosition();
    if (position > 0) {
        if (processor.getLoopReset() > 0.0) {
            position %= static_cast<int64_t>(processor.getLoopReset() * processor.getPattern().getTimebase());
        }
        position %= processor.getPattern().loopLength;
    }

    // Draw notes
    auto &notes = pattern.getNotes();
    for (unsigned long i = 0; i < notes.size(); i++) {
        auto &note = notes[i];
        juce::Rectangle<int> noteRect = getRectangleForNote(note);

        if (noteRect.intersects(unoffsDrawRegion)) {
            bool isPlaying = (position > 0 && position >= note.startPoint && position < note.endPoint);

            if (selectedNotes.find(i) == selectedNotes.end()) {
                g.setColour(isPlaying ? Style::NOTE_ACTIVE_FILL_COLOUR : Style::NOTE_FILL_COLOUR);
            } else {
                g.setColour(isPlaying ? Style::NOTE_SELECTED_ACTIVE_FILL_COLOUR : Style::NOTE_SELECTED_FILL_COLOUR);
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

    // Draw loop line
    g.setColour(Style::LOOP_LINE_COLOUR);
    auto loopLine = pulseToX(pattern.loopLength);
    auto loopLineRect = juce::Rectangle<int>(loopLine, 0, 4, getHeight());
    if (loopLineRect.intersects(unoffsDrawRegion)){
        g.fillRect(loopLineRect);
    }

    // Draw playback position indicator
    if (lastPlayPositionX > 0) {
        auto positionRect = juce::Rectangle<int>(lastPlayPositionX - state.offsetX, unoffsDrawRegion.getY(), 1, unoffsDrawRegion.getHeight());
        if (positionRect.intersects(unoffsDrawRegion)) {
            g.setColour(Style::PLAYHEAD_POSITION_COLOUR);
            g.fillRect(positionRect);
        }
    }

    // Selected time border
    int64_t selectionStart, selectionEnd;
    if (getSelectionBorder(selectionStart, selectionEnd)) {
        auto startX = pulseToX(selectionStart);
        auto endX = pulseToX(selectionEnd);

        g.setColour(Style::SELECTED_TIME_BORDER_COLOUR);
        g.fillRect(startX, 0, 2, getHeight());
        g.fillRect(endX, 0, 2, getHeight());

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
            view->zoomPattern(0, wheel.deltaY);
        } else {
            view->zoomPattern(wheel.deltaY, 0);
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
            view->scrollPattern(wheel.deltaY, wheel.deltaX);
        } else {
            view->scrollPattern(wheel.deltaX, wheel.deltaY);
        }
    }
}

void PatternEditor::mouseMove(const juce::MouseEvent &event) {
    auto &pattern = processor.getPattern();
    std::scoped_lock lock(pattern.getMutex());

    mouseAnyMove(event);
    defer d([this]() { updateMouseCursor(); });

    auto &notes = pattern.getNotes();
    for (uint64_t i = 0; i < notes.size(); i++) {
        auto &note = notes[i];
        auto noteRect = getRectangleForNote(note);
        if (noteRect.contains(event.x, event.y)) {
            if (event.x <= (noteRect.getX() + NOTE_RESIZE_TOLERANCE)) {
                mouseCursor = juce::MouseCursor::LeftEdgeResizeCursor;
                if (selectedNotes.find(i) == selectedNotes.end()) {
                    dragAction.noteDragAction(this, DragAction::TYPE_NOTE_START_RESIZE, i, notes, event);
                } else {
                    dragAction.noteDragAction(this, DragAction::TYPE_NOTE_START_RESIZE, i, selectedNotes, notes, event);
                }
                return;
            } else if (event.x >= (noteRect.getX() + noteRect.getWidth() - NOTE_RESIZE_TOLERANCE)) {
                mouseCursor = juce::MouseCursor::RightEdgeResizeCursor;
                if (selectedNotes.find(i) == selectedNotes.end()) {
                    dragAction.noteDragAction(this, DragAction::TYPE_NOTE_END_RESIZE, i, notes, event);
                } else {
                    dragAction.noteDragAction(this, DragAction::TYPE_NOTE_END_RESIZE, i, selectedNotes, notes, event);
                }
                return;
            } else {
                mouseCursor = juce::MouseCursor::DraggingHandCursor;
                if (selectedNotes.find(i) == selectedNotes.end()) {
                    dragAction.noteDragAction(this, DragAction::TYPE_NOTE_MOVE, i, notes, event);
                } else {
                    dragAction.noteDragAction(this, DragAction::TYPE_NOTE_MOVE, i, selectedNotes, notes, event);
                }
                return;
            }
        }
    }

    {
        int64_t start, end;
        if (getSelectionBorder(start, end)) {
            auto startX = pulseToX(start);
            auto startMinX = startX - LINE_RESIZE_TOLERANCE;
            auto startMaxX = startX + LINE_RESIZE_TOLERANCE;
            if (event.x >= startMinX && event.x <= startMaxX) {
                mouseCursor = juce::MouseCursor::LeftRightResizeCursor;
                dragAction.stretchDragAction(DragAction::TYPE_STRETCH_START, selectedNotes, pattern.getNotes());
                return;
            }

            auto endX = pulseToX(end);
            auto endMinX = endX - LINE_RESIZE_TOLERANCE;
            auto endMaxX = endX + LINE_RESIZE_TOLERANCE;
            if (event.x >= endMinX && event.x <= endMaxX) {
                mouseCursor = juce::MouseCursor::LeftRightResizeCursor;
                dragAction.stretchDragAction(DragAction::TYPE_STRETCH_END, selectedNotes, pattern.getNotes());
                return;
            }
        }
    }

    {
        auto loopLine = pulseToX(processor.getPattern().loopLength);
        auto loopMinX = loopLine - LINE_RESIZE_TOLERANCE;
        auto loopMaxX = loopLine + LINE_RESIZE_TOLERANCE;
        if (event.x >= loopMinX && event.x <= loopMaxX) {
            mouseCursor = juce::MouseCursor::LeftRightResizeCursor;
            dragAction.basicDragAction(DragAction::TYPE_LOOP_RESIZE);
            return;
        }
    }

    dragAction.basicDragAction();
}

void PatternEditor::mouseDrag(const juce::MouseEvent &event) {
    mouseAnyMove(event);
    defer d([this]() { updateMouseCursor(); });

    if (event.mods.isLeftButtonDown() && !event.mods.isRightButtonDown() && !event.mods.isMiddleButtonDown()) {
        switch (dragAction.type) {
            case DragAction::TYPE_LOOP_RESIZE:
                loopResize(event);
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
    repaint(0, noteToY(cursorNote), getWidth(), state.pixelsPerNote);

    cursorPulse = xToPulse(event.x);
    cursorNote = yToNote(event.y);

    snapEnabled = !(event.mods.isAltDown() || (event.mods.isCtrlDown() && event.mods.isShiftDown()));

    mouseCursor = juce::MouseCursor::NormalCursor;

    repaint(pulseToX(cursorPulse), 0, 1, getHeight());
    repaint(0, noteToY(cursorNote), getWidth(), state.pixelsPerNote);
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
                    } else {
                        if (selectedNotes.find(dragAction.initiatorIndex) == selectedNotes.end()) {
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
            view->resetPatternOffset();
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
    dragAction.basicDragAction();
    repaint(selection);
    selection = juce::Rectangle<int>(0, 0, 0, 0);
    mouseAnyMove(event);
    repaintNotes();
    Component::mouseUp(event);
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


void PatternEditor::loopResize(const juce::MouseEvent &event) {
    std::scoped_lock lock(processor.getPattern().getMutex());

    int64_t lastNoteEnd = 0;
    for (auto &note : processor.getPattern().getNotes()) {
        if (note.endPoint > lastNoteEnd) {
            lastNoteEnd = note.endPoint;
        }
    }

    processor.getPattern().loopLength = juce::jmax((int64_t) 1, lastNoteEnd, xToPulse(event.x));
    processor.buildPattern();
    view->repaint();
    mouseCursor = juce::MouseCursor::LeftRightResizeCursor;
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
        note.endPoint =
                juce::jmin(juce::jmax(xToPulse(event.x) + noteOffset.endOffset, note.startPoint + minSize),
                     processor.getPattern().loopLength);

        state.lastNoteLength = note.endPoint - note.startPoint;
    }

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
            note.endPoint = juce::jmin(
                    juce::jmax(wantedEnd, noteLength),
                    processor.getPattern().loopLength);
            note.startPoint = note.endPoint - noteLength;
        }

        if (!event.mods.isShiftDown()) {
            note.data.noteNumber = yToNote(event.y) + noteOffset.noteOffset;
        }
    }

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
    note.startPoint = juce::jmin(pulse, pattern.loopLength - state.lastNoteLength);
    note.endPoint = note.startPoint + state.lastNoteLength;
    note.data.noteNumber = yToNote(event.y);
    note.data.velocity = state.lastNoteVelocity;

    auto index = notes.size();
    notes.push_back(note);

    processor.buildPattern();
    repaintNotes();

    mouseAnyMove(event);

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

    mouseAnyMove(event);
    updateMouseCursor();
}


void PatternEditor::selectAll() {
    auto &notes = processor.getPattern().getNotes();
    for (size_t i = 0; i < notes.size(); i++) {
        selectedNotes.insert(i);
    }
    repaintNotes();
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
    repaintSelectedNotes();

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
}


void PatternEditor::selectionStartStretch(const juce::MouseEvent& event) {
    int64_t start, end;
    getSelectionBorder(start, end);
    selectionStretch(xToPulse(event.x, !event.mods.isAltDown()), end);
}

void PatternEditor::selectionEndStretch(const juce::MouseEvent& event) {
    int64_t start, end;
    getSelectionBorder(start, end);
    selectionStretch(start, xToPulse(event.x, !event.mods.isAltDown()));
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
    repaintSelectedNotes();
    processor.buildPattern();
}


void PatternEditor::audioUpdate() {
    auto position = processor.getLastPosition();
    if (position > 0) {
        if (processor.getLoopReset() > 0.0) {
            position %= static_cast<int64_t>(processor.getLoopReset() * processor.getPattern().getTimebase());
        }
        position %= processor.getPattern().loopLength;

        auto oldPosition = lastPlayPositionX;
        auto newPosition = pulseToAbsX(position);

        if (oldPosition <= newPosition) {
            repaint(oldPosition - state.offsetX, 0, newPosition - oldPosition + 1, getHeight());
        } else {
            repaint(oldPosition - state.offsetX, 0, 1, getHeight());
            repaint(newPosition - state.offsetX, 0, 1, getHeight());
        }

        lastPlayPositionX = newPosition;
    }

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

    repaint(juce::Rectangle<int>::leftTopRightBottom(minX - 2, 0, maxX + 2, getHeight()));
}

PatternEditorView* PatternEditor::getView() {
    return view;
}

juce::Rectangle<int> PatternEditor::getRectangleForNote(ArpNote &note) {
    auto pixelsPerNote = state.pixelsPerNote;

    return juce::Rectangle<int>(
            pulseToX(note.startPoint),
            noteToY(note.data.noteNumber),
            pulseToAbsX(note.endPoint - note.startPoint),
            pixelsPerNote);
}

bool PatternEditor::getSelectionBorder(std::set<uint64_t>& indices,
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

bool PatternEditor::getSelectionBorder(int64_t& out_start, int64_t& out_end) {
    auto& pattern = processor.getPattern();
    std::scoped_lock lock(pattern.getMutex());
    return getSelectionBorder(selectedNotes, pattern.getNotes(), out_start, out_end);
}

int64_t PatternEditor::snapPulse(int64_t pulse, bool floor) {
    if (!snapEnabled) {
        return pulse;
    }

    auto &pattern = processor.getPattern();
    auto timebase = pattern.getTimebase();
    double doubleDivisor = state.divisor;

    double base = (pulse * doubleDivisor) / timebase;
    int64_t roundedBase = static_cast<int64_t>((floor) ? std::floor(base) : std::round(base));

    return roundedBase * (timebase / state.divisor);
}


int64_t PatternEditor::xToPulse(int x, bool snap, bool floor) {
    auto &pattern = processor.getPattern();
    auto timebase = pattern.getTimebase();
    double pixelsPerBeat = state.pixelsPerBeat;

    auto pulse = static_cast<int64_t>(
            std::round(((x + state.offsetX) / pixelsPerBeat) * timebase));

    return juce::jmax(static_cast<int64_t>(0), (snap) ? snapPulse(pulse, floor) : pulse);
}

int PatternEditor::yToNote(int y) {
    double pixelsPerNote = state.pixelsPerNote;
    return static_cast<int>(std::ceil(((getHeight() / 2.0) - (y + state.offsetY)) / pixelsPerNote - 0.5));
}

int PatternEditor::pulseToX(int64_t pulse) {
    return pulseToAbsX(pulse) - state.offsetX;
}

int PatternEditor::pulseToAbsX(int64_t pulse) {
    auto &pattern = processor.getPattern();
    auto pixelsPerBeat = state.pixelsPerBeat;

    return juce::jmax(0, juce::roundToInt((pulse / static_cast<float>(pattern.getTimebase())) * pixelsPerBeat) + 1);
}

int PatternEditor::noteToY(int note) {
    return noteToAbsY(note) - state.offsetY;
}

int PatternEditor::noteToAbsY(int note) {
    double pixelsPerNote = state.pixelsPerNote;
    return juce::roundToInt(std::floor((getHeight() / 2.0) - (note + 0.5) * pixelsPerNote)) + 1;
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
                                                  std::vector<ArpNote>& allNotes) {
    jassert((type & DragAction::TYPE_MASK) == DragAction::TYPE_STRETCH);
    this->type = type;
    this->selectedNotes.clear();

    int64_t start, end;
    if (PatternEditor::getSelectionBorder(indices, allNotes, start, end)) {
        double length = static_cast<double>(end) - static_cast<double>(start);

        for (auto i : indices) {
            ArpNote& note = allNotes[i];

            SelectedNote selectedNote;
            selectedNote.noteIndex = i;
            selectedNote.relativeStart = static_cast<double>(note.startPoint - start) / length;
            selectedNote.relativeEnd = static_cast<double>(note.endPoint - start) / length;
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
