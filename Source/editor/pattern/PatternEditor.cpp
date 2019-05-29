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

#include <new>

#include "PatternEditor.h"
#include "PatternEditorView.h"

const Colour BACKGROUND_COLOUR = Colour(82, 78, 67);
const Colour GRIDLINES_COLOUR = Colour(42, 40, 34);
const Colour POSITION_INDICATOR_COLOUR = Colour(255, 255, 255);
const Colour LOOP_LINE_COLOUR = Colour(155, 36, 36);

const Colour ZERO_LINE_COLOUR = Colour((uint8) 0, 0, 0, 0.1f);
const Colour ZERO_OCTAVE_COLOUR = Colour((uint8) 171, 204, 41, 0.1f);
const Colour OCTAVE_LINE_COLOUR = Colour((uint8) 0, 0, 0, 1.0f);

const Colour BAR_SHADE_COLOUR = Colour((uint8) 0, 0, 0, 0.1f);

const Colour NOTE_FILL_COLOUR = Colour(171, 204, 41);
const Colour NOTE_ACTIVE_FILL_COLOUR = Colour(228, 255, 122);
const Colour NOTE_SELECTED_FILL_COLOUR = Colour(245, 255, 209);
const Colour NOTE_SELECTED_ACTIVE_FILL_COLOUR = Colour(255, 255, 255);
const Colour NOTE_BORDER_COLOUR = Colour((uint8) 0, 0, 0, 0.7f);
const Colour NOTE_VELOCITY_COLOUR = Colour((uint8) 0, 0, 0, 0.2f);

const Colour CURSOR_TIME_COLOUR = Colour((uint8) 255, 255, 255, 0.7f);
const Colour CURSOR_NOTE_COLOUR = Colour((uint8) 255, 255, 255, 0.05f);

const Colour SELECTION_BORDER_COLOUR = Colour(255, 0, 0);

const int NOTE_RESIZE_TOLERANCE = 8;
const int LOOP_RESIZE_TOLERANCE = 5;


PatternEditor::PatternEditor(LibreArp &p, EditorState &e, PatternEditorView *ec)
        : processor(p), state(e), view(ec)
{
    setSize(1, 1); // We have to set this, otherwise it won't render at all

    cursorPulse = 0;
    new(dragAction) DragAction(); // initialize a no-op drag action
    if (state.lastNoteLength < 1) {
        state.lastNoteLength = processor.getPattern().getTimebase() / state.divisor;
    }
    snapEnabled = true;
    selection = Rectangle<int>(0, 0, 0, 0);

    setWantsKeyboardFocus(true);
}

void PatternEditor::paint(Graphics &g) {
    ArpPattern &pattern = processor.getPattern();
    auto pixelsPerBeat = state.pixelsPerBeat;
    auto pixelsPerNote = state.pixelsPerNote;
    auto drawRegion = g.getClipBounds();

    // Set size
    setSize(
            jmax(view->getRenderWidth(), getParentWidth()),
            jmax(view->getRenderHeight(), getParentHeight()));

    // Draw background
    g.setColour(BACKGROUND_COLOUR);
    g.fillRect(drawRegion);

    // Draw bars
    if (processor.getTimeSigDenominator() > 0 && processor.getTimeSigDenominator() <= 32) {
        auto beat = (pixelsPerBeat * 4) / processor.getTimeSigDenominator();
        auto bar = beat * processor.getTimeSigNumerator();
        g.setColour(BAR_SHADE_COLOUR);
        for (int i = (drawRegion.getX() / bar) * bar; i < drawRegion.getWidth(); i += bar * 2) {
            g.fillRect(i + bar, 0, bar, getHeight());
        }
    }

    // Draw octave 0
    auto numInputNotes = processor.getNumInputNotes();
    int noteZeroY = noteToY(0);
    if (numInputNotes > 0) {
        g.setColour(ZERO_OCTAVE_COLOUR);
        auto height = numInputNotes * pixelsPerNote;
        auto rect = Rectangle<int>(
                drawRegion.getX(), noteZeroY - height + pixelsPerNote, drawRegion.getWidth(), height);
        if (rect.intersects(drawRegion)) {
            g.fillRect(rect);
        }
    } else {
        g.setColour(ZERO_LINE_COLOUR);
        auto rect = Rectangle<int>(drawRegion.getX(), noteZeroY, drawRegion.getWidth(), pixelsPerNote);
        if (rect.intersects(drawRegion)) {
            g.fillRect(rect);
        }
    }

    // Draw gridlines
    // - Horizontal
    g.setColour(GRIDLINES_COLOUR);
    for (int i = (getHeight() / 2) % pixelsPerNote - pixelsPerNote / 2; i < getHeight(); i += pixelsPerNote) {
        g.fillRect(0, i, getWidth(), 2);
    }

    // - Vertical
    float beatDiv = (pixelsPerBeat / static_cast<float>(state.divisor));
    int beatN = 0;
    for (float i = 0; i < getWidth(); i += beatDiv, beatN++) {
        if (beatN % state.divisor == 0) {
            g.fillRect(roundToInt(i), 0, 4, getHeight());
        } else {
            g.fillRect(roundToInt(i), 0, 2, getHeight());
        }
    }

    // Draw octaves
    if (numInputNotes > 0) {
        g.setColour(OCTAVE_LINE_COLOUR);
        auto pixelsPerOctave = pixelsPerNote * numInputNotes;

        int i = (getHeight() / 2) % pixelsPerOctave - pixelsPerNote / 2 + pixelsPerNote;
        for (/* above */; i < getHeight(); i += pixelsPerOctave) {
            g.fillRect(drawRegion.getX(), i, drawRegion.getWidth(), 1);
        }
    }

    // Draw notes
    auto &notes = pattern.getNotes();
    for (unsigned long i = 0; i < notes.size(); i++) {
        auto &note = notes[i];
        Rectangle<int> noteRect = getRectangleForNote(note);

        if (noteRect.intersects(drawRegion)) {
            auto isPlaying = processor.getPlayingPatternIndices().contains(i);

            if (selectedNotes.find(i) == selectedNotes.end()) {
                g.setColour(isPlaying ? NOTE_ACTIVE_FILL_COLOUR : NOTE_FILL_COLOUR);
            } else {
                g.setColour(isPlaying ? NOTE_SELECTED_ACTIVE_FILL_COLOUR : NOTE_SELECTED_FILL_COLOUR);
            }
            g.fillRect(noteRect);

            g.setColour(NOTE_VELOCITY_COLOUR);
            g.fillRect(noteRect.withTrimmedBottom(static_cast<int>(pixelsPerNote * note.data.velocity)));

            g.setColour(NOTE_BORDER_COLOUR);
            g.drawRect(noteRect, 2);
        }
    }

    // Draw cursor indicator
    g.setColour(CURSOR_TIME_COLOUR);
    auto cursorPulseX = pulseToX(cursorPulse);
    g.fillRect(cursorPulseX, 0, 1, getHeight());

    // Draw loop line
    g.setColour(LOOP_LINE_COLOUR);
    auto loopLine = pulseToX(pattern.loopLength);
    auto loopLineRect = Rectangle<int>(loopLine, drawRegion.getY(), 4, drawRegion.getHeight());
    if (loopLineRect.intersects(drawRegion)){
        g.fillRect(loopLineRect);
    }

    // Draw position indicator
    if (lastPlayPositionX > 0) {
        auto positionRect = Rectangle<int>(lastPlayPositionX, drawRegion.getY(), 1, drawRegion.getHeight());
        if (positionRect.intersects(drawRegion)) {
            g.setColour(POSITION_INDICATOR_COLOUR);
            g.fillRect(positionRect);
            repaint(positionRect);
        }
    }

    // Draw selection
    if (selection.getWidth() != 0 && selection.getHeight() != 0) {
        if (selection.intersects(drawRegion)) {
            g.setColour(SELECTION_BORDER_COLOUR);
            g.drawRect(selection, 3);
        }
    }


    auto cursorNoteY = noteToY(cursorNote);
    auto cursorNoteRect = Rectangle<int>(drawRegion.getX(), cursorNoteY, drawRegion.getWidth(), pixelsPerNote);
    if (cursorNoteRect.intersects(drawRegion)) {
        g.setColour(CURSOR_NOTE_COLOUR);
        g.fillRect(cursorNoteRect);
    }
}


void PatternEditor::mouseWheelMove(const MouseEvent &event, const MouseWheelDetails &wheel) {
    if (event.mods.isCtrlDown()) {
        if (event.mods.isShiftDown()) {
            view->zoomPattern(0, wheel.deltaY);
        } else {
            view->zoomPattern(wheel.deltaY, 0);
        }
    } else {
        if (event.mods.isAltDown()) {
            if (this->dragAction != nullptr && (this->dragAction->type & DragAction::TYPE_MASK) == DragAction::TYPE_NOTE) {
                auto *dragAction = (NoteDragAction *) this->dragAction;
                std::scoped_lock lock(this->processor.getPattern().getMutex());
                for (auto &noteOffset : dragAction->noteOffsets) {
                    auto &note = this->processor.getPattern().getNotes()[noteOffset.noteIndex];
                    note.data.velocity = jmax(0.0, jmin(note.data.velocity + wheel.deltaY * 0.1, 1.0));
                }
                processor.buildPattern();
            }
        } else {
            Component::mouseWheelMove(event, wheel);
        }
    }
}

void PatternEditor::mouseMove(const MouseEvent &event) {
    auto &pattern = processor.getPattern();
    std::scoped_lock lock(pattern.getMutex());

    mouseAnyMove(event);

    auto &notes = pattern.getNotes();
    for (uint64 i = 0; i < notes.size(); i++) {
        auto &note = notes[i];
        auto noteRect = getRectangleForNote(note);
        if (noteRect.contains(event.x, event.y)) {
            if (event.x <= (noteRect.getX() + NOTE_RESIZE_TOLERANCE)) {
                setMouseCursor(MouseCursor::LeftEdgeResizeCursor);
                if (selectedNotes.find(i) == selectedNotes.end()) {
                    new(dragAction) NoteDragAction(this, DragAction::TYPE_NOTE_START_RESIZE, i, notes, event);
                } else {
                    new(dragAction) NoteDragAction(this, DragAction::TYPE_NOTE_START_RESIZE, i, selectedNotes, notes, event);
                }
                return;
            } else if (event.x >= (noteRect.getX() + noteRect.getWidth() - NOTE_RESIZE_TOLERANCE)) {
                setMouseCursor(MouseCursor::RightEdgeResizeCursor);
                if (selectedNotes.find(i) == selectedNotes.end()) {
                    new(dragAction) NoteDragAction(this, DragAction::TYPE_NOTE_END_RESIZE, i, notes, event);
                } else {
                    new(dragAction) NoteDragAction(this, DragAction::TYPE_NOTE_END_RESIZE, i, selectedNotes, notes, event);
                }
                return;
            } else {
                setMouseCursor(MouseCursor::DraggingHandCursor);
                if (selectedNotes.find(i) == selectedNotes.end()) {
                    new(dragAction) NoteDragAction(this, DragAction::TYPE_NOTE_MOVE, i, notes, event);
                } else {
                    new(dragAction) NoteDragAction(this, DragAction::TYPE_NOTE_MOVE, i, selectedNotes, notes, event);
                }
                return;
            }
        }
    }

    auto loopRect = getRectangleForLoop();
    if (loopRect.contains(event.x, event.y)) {
        setMouseCursor(MouseCursor::LeftRightResizeCursor);
        new(dragAction) DragAction(DragAction::TYPE_LOOP_RESIZE);
        return;
    }

    new(dragAction) DragAction();
}

void PatternEditor::mouseDrag(const MouseEvent &event) {
    mouseAnyMove(event);

    if (event.mods.isLeftButtonDown() && !event.mods.isRightButtonDown() && !event.mods.isMiddleButtonDown()) {
        if (this->dragAction != nullptr && this->dragAction->type != DragAction::TYPE_NONE) {
            switch (this->dragAction->type) {
                case DragAction::TYPE_LOOP_RESIZE:
                    loopResize(event);
                    return;
                case DragAction::TYPE_NOTE_START_RESIZE:
                    noteStartResize(event, (NoteDragAction *) (this->dragAction));
                    return;
                case DragAction::TYPE_NOTE_END_RESIZE:
                    noteEndResize(event, (NoteDragAction *) (this->dragAction));
                    return;
                case DragAction::TYPE_NOTE_MOVE:
                    noteMove(event, (NoteDragAction *) (this->dragAction));
                    return;
                case DragAction::TYPE_SELECTION_DRAG:
                    select(event, (SelectionDragAction *) (this->dragAction));
                    return;
                default:
                    return;
            }
        }
    }

    if (!event.mods.isLeftButtonDown() && event.mods.isRightButtonDown() && !event.mods.isMiddleButtonDown()) {
        noteDelete(event);
        return;
    }
}

void PatternEditor::mouseAnyMove(const MouseEvent &event) {
    repaint(pulseToX(cursorPulse), 0, 1, getHeight());
    repaint(0, noteToY(cursorNote), getWidth(), state.pixelsPerNote);

    cursorPulse = xToPulse(event.x);
    cursorNote = yToNote(event.y);

    snapEnabled = !(event.mods.isAltDown() || (event.mods.isCtrlDown() && event.mods.isShiftDown()));

    setMouseCursor(MouseCursor::NormalCursor);

    repaint(pulseToX(cursorPulse), 0, 1, getHeight());
    repaint(0, noteToY(cursorNote), getWidth(), state.pixelsPerNote);
}

void PatternEditor::mouseDown(const MouseEvent &event) {
    if (event.mods.isLeftButtonDown() && !event.mods.isRightButtonDown() && !event.mods.isMiddleButtonDown()) {
        if (this->dragAction == nullptr || this->dragAction->type == DragAction::TYPE_NONE) {
            if (event.mods.isCtrlDown()) {
                if (!event.mods.isShiftDown()) {
                    selectedNotes.clear();
                }

                new(dragAction) SelectionDragAction(event.x, event.y);
                repaintNotes();
            } else {
                selectedNotes.clear();
                noteCreate(event);
                repaintNotes();
            }
        } else {
            switch(this->dragAction->type) {
                case DragAction::TYPE_NOTE_MOVE: {
                    repaintNotes();
                        if (selectedNotes.empty()) {
                            auto &offsets = ((NoteDragAction *) this->dragAction)->noteOffsets;
                            if (offsets.size() == 1) {
                                auto &note = processor.getPattern().getNotes()[offsets[0].noteIndex];
                                state.lastNoteLength = note.endPoint - note.startPoint;
                            }
                        }
                        if (event.mods.isShiftDown() && !event.mods.isCtrlDown() && !event.mods.isAltDown()) {
                            noteDuplicate((NoteDragAction *) (this->dragAction));
                        }
                        if (event.mods.isCtrlDown() && !event.mods.isAltDown()) {
                            if (!event.mods.isShiftDown()) {
                                selectedNotes.clear();
                                selectedNotes.insert(((NoteDragAction *) dragAction)->initiatorIndex);
                            } else {
                                if (selectedNotes.find(((NoteDragAction *) dragAction)->initiatorIndex) == selectedNotes.end()) {
                                    selectedNotes.insert(((NoteDragAction *) dragAction)->initiatorIndex);
                                } else {
                                    selectedNotes.erase(((NoteDragAction *) dragAction)->initiatorIndex);
                                }
                            }
                            repaintNotes();
                        }
                    }
                    break;
                default:
                    break;
            }
        }

        Component::mouseDown(event);
        return;
    }

    if (!event.mods.isLeftButtonDown() && event.mods.isRightButtonDown() && !event.mods.isMiddleButtonDown()) {
        selectedNotes.clear();
        noteDelete(event);
        repaintNotes();
        Component::mouseDown(event);
        return;
    }

    Component::mouseDown(event);
}

void PatternEditor::mouseUp(const MouseEvent &event) {
    new(dragAction) DragAction();
    repaint(selection);
    selection = Rectangle<int>(0, 0, 0, 0);
    setMouseCursor(MouseCursor::NormalCursor);
    repaintNotes();
    Component::mouseUp(event);
}


bool PatternEditor::keyPressed(const KeyPress &key) {
    if (key == KeyPress::deleteKey || key == KeyPress::numberPadDelete) {
        deleteSelected();
        return true;
    }

    if (key.isKeyCode(KeyPress::upKey)) {
        moveSelectedUp(key.getModifiers().isCtrlDown());
        return true;
    }

    if (key.isKeyCode(KeyPress::downKey)) {
        moveSelectedDown(key.getModifiers().isCtrlDown());
        return true;
    }

    if (key == KeyPress::createFromDescription("CTRL+A")) {
        selectAll();
        return true;
    }

    if (key == KeyPress::createFromDescription("CTRL+D")) {
        deselectAll();
        return true;
    }

    return false;
}


void PatternEditor::loopResize(const MouseEvent &event) {
    std::scoped_lock lock(processor.getPattern().getMutex());

    int64 lastNoteEnd = 0;
    for (auto &note : processor.getPattern().getNotes()) {
        if (note.endPoint > lastNoteEnd) {
            lastNoteEnd = note.endPoint;
        }
    }

    processor.getPattern().loopLength = jmax((int64) 1, lastNoteEnd, xToPulse(event.x));
    processor.buildPattern();
    view->repaint();
    setMouseCursor(MouseCursor::LeftRightResizeCursor);
}


void PatternEditor::noteStartResize(const MouseEvent &event, NoteDragAction *dragAction) {
    std::scoped_lock lock(processor.getPattern().getMutex());

    auto timebase = processor.getPattern().getTimebase();
    auto &notes = processor.getPattern().getNotes();

    repaintNotes();
    for (auto &noteOffset : dragAction->noteOffsets) {
        auto &note = notes[noteOffset.noteIndex];
        int64 minSize = (snapEnabled) ? (timebase / state.divisor) : 1;
        note.startPoint = jmax((int64) 0, jmin(xToPulse(event.x) + noteOffset.startOffset, note.endPoint - minSize));

        state.lastNoteLength = note.endPoint - note.startPoint;
    }

    processor.buildPattern();
    repaintNotes();
    setMouseCursor(MouseCursor::LeftEdgeResizeCursor);
}

void PatternEditor::noteEndResize(const MouseEvent &event, NoteDragAction *dragAction) {
    std::scoped_lock lock(processor.getPattern().getMutex());

    auto timebase = processor.getPattern().getTimebase();
    auto &notes = processor.getPattern().getNotes();

    repaintNotes();
    for (auto &noteOffset : dragAction->noteOffsets) {
        auto &note = notes[noteOffset.noteIndex];
        int64 minSize = (snapEnabled) ? (timebase / state.divisor) : 1;
        note.endPoint =
                jmin(jmax(xToPulse(event.x) + noteOffset.endOffset, note.startPoint + minSize),
                     processor.getPattern().loopLength);

        state.lastNoteLength = note.endPoint - note.startPoint;
    }

    processor.buildPattern();
    repaintNotes();
    setMouseCursor(MouseCursor::RightEdgeResizeCursor);
}

void PatternEditor::noteMove(const MouseEvent &event, PatternEditor::NoteDragAction *dragAction) {
    std::scoped_lock lock(processor.getPattern().getMutex());

    repaintNotes();
    auto &notes = processor.getPattern().getNotes();
    for (auto &noteOffset : dragAction->noteOffsets) {
        auto &note = notes[noteOffset.noteIndex];
        auto noteLength = note.endPoint - note.startPoint;
        auto wantedEnd = xToPulse(event.x) + noteOffset.endOffset;

        if (!event.mods.isCtrlDown()) {
            note.endPoint = jmin(
                    jmax(wantedEnd, noteLength),
                    processor.getPattern().loopLength);
            note.startPoint = note.endPoint - noteLength;
        }

        if (!event.mods.isShiftDown()) {
            note.data.noteNumber = yToNote(event.y) + noteOffset.noteOffset;
        }
    }

    processor.buildPattern();
    repaintNotes();

    setMouseCursor(MouseCursor::DraggingHandCursor);
}

void PatternEditor::noteDuplicate(PatternEditor::NoteDragAction *dragAction) {
    std::scoped_lock lock(processor.getPattern().getMutex());

    auto &notes = processor.getPattern().getNotes();
    for (auto &noteOffset : dragAction->noteOffsets) {
        processor.getPattern().getNotes().push_back(notes[noteOffset.noteIndex]);
    }
    processor.buildPattern();
}

void PatternEditor::noteCreate(const MouseEvent &event) {
    std::scoped_lock lock(processor.getPattern().getMutex());

    auto &pattern = processor.getPattern();
    auto &notes = pattern.getNotes();
    auto pulse = xToPulse(event.x, true, true);
    if (event.mods.isShiftDown()) {
        state.lastNoteLength = pattern.getTimebase() / state.divisor;
    }

    ArpNote note = ArpNote();
    note.startPoint = jmin(pulse, pattern.loopLength - state.lastNoteLength);
    note.endPoint = note.startPoint + state.lastNoteLength;
    note.data.noteNumber = yToNote(event.y);

    auto index = notes.size();
    notes.push_back(note);

    processor.buildPattern();
    repaintNotes();

    if (event.mods.isShiftDown()) {
        new(dragAction) NoteDragAction(this, DragAction::TYPE_NOTE_END_RESIZE, index, notes, event, false);
    } else {
        new(dragAction) NoteDragAction(this, DragAction::TYPE_NOTE_MOVE, index, notes, event);
    }
}

void PatternEditor::noteDelete(const MouseEvent &event) {
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
            new(dragAction) DragAction();
            break;
        }
    }

    if (erased) {
        processor.buildPattern();
        repaintNotes();
    }
}


void PatternEditor::selectAll() {
    auto &notes = processor.getPattern().getNotes();
    for (int i = 0; i < notes.size(); i++) {
        selectedNotes.insert(i);
    }
    repaintNotes();
}

void PatternEditor::deselectAll() {
    selectedNotes.clear();
    repaintNotes();
}

void PatternEditor::deleteSelected() {
    repaintNotes();
    auto &notes = processor.getPattern().getNotes();
    for (auto it = selectedNotes.rbegin(); it != selectedNotes.rend(); it++) {
        auto index = *it;
        notes[index] = notes.back();
        notes.pop_back();
    }
    selectedNotes.clear();
    new(dragAction) DragAction();
    processor.buildPattern();
    repaintNotes();
}

void PatternEditor::moveSelectedUp(bool octave) {
    std::scoped_lock lock(processor.getPattern().getMutex());

    repaintNotes();
    auto &notes = processor.getPattern().getNotes();
    for (auto index : selectedNotes) {
        if (octave) {
            notes[index].data.noteNumber += processor.getNumInputNotes();
        } else {
            notes[index].data.noteNumber++;
        }
    }
    processor.buildPattern();
    repaintNotes();
}

void PatternEditor::moveSelectedDown(bool octave) {
    std::scoped_lock lock(processor.getPattern().getMutex());

    repaintNotes();
    auto &notes = processor.getPattern().getNotes();
    for (auto index : selectedNotes) {
        if (octave) {
            notes[index].data.noteNumber -= processor.getNumInputNotes();
        } else {
            notes[index].data.noteNumber--;
        }
    }
    processor.buildPattern();
    repaintNotes();
}


void PatternEditor::select(const MouseEvent &event, PatternEditor::SelectionDragAction *dragAction) {
    repaint(selection);
    selection = Rectangle<int>(Point<int>(event.x, event.y), Point<int>(dragAction->startX, dragAction->startY));
    repaint(selection);
    repaintNotes();

    if (!event.mods.isShiftDown()) {
        selectedNotes.clear();
    }

    auto &notes = processor.getPattern().getNotes();
    for(int i = 0; i < notes.size(); i++) {
        auto &note = notes[i];
        auto noteRect = getRectangleForNote(note);
        if (selection.intersects(noteRect)) {
            selectedNotes.insert(i);
        }
    }
}


void PatternEditor::audioUpdate(uint32 type) {
    auto position = processor.getLastPosition();
    if (position > 0) {
        if (processor.getLoopReset() > 0.0) {
            position %= static_cast<int64>(processor.getLoopReset() * processor.getPattern().getTimebase());
        }
        position %= processor.getPattern().loopLength;
        lastPlayPositionX = pulseToX(position);
        repaint(lastPlayPositionX, 0, 1, getHeight());
    }

    repaintNotes();
}

void PatternEditor::repaintNotes() {
    bool willRepaint = false;
    auto notesRect = Rectangle<int>::leftTopRightBottom(INT32_MAX, INT32_MAX, 0, 0);
    auto &notes = processor.getPattern().getNotes();
    for(int i = 0; i < notes.size(); i++) {
        auto &note = notes[i];
        auto noteRect = getRectangleForNote(note);
        notesRect.setLeft(jmin(notesRect.getX(), noteRect.getX()));
        notesRect.setTop(jmin(notesRect.getY(), noteRect.getY()));
        notesRect.setRight(jmax(notesRect.getRight(), noteRect.getRight()));
        notesRect.setBottom(jmax(notesRect.getBottom(), noteRect.getBottom()));
        willRepaint = true;
    }

    if (willRepaint) {
        repaint(notesRect);
    }
}

PatternEditorView* PatternEditor::getView() {
    return view;
}


Rectangle<int> PatternEditor::getRectangleForNote(ArpNote &note) {
    ArpPattern &pattern = processor.getPattern();
    auto pixelsPerNote = state.pixelsPerNote;

    return Rectangle<int>(
            pulseToX(note.startPoint),
            noteToY(note.data.noteNumber),
            pulseToX(note.endPoint - note.startPoint),
            pixelsPerNote);
}

Rectangle<int> PatternEditor::getRectangleForLoop() {
    auto loopLine = pulseToX(processor.getPattern().loopLength);
    return Rectangle<int>(loopLine - LOOP_RESIZE_TOLERANCE, 0, LOOP_RESIZE_TOLERANCE * 2, getHeight());
}


int64 PatternEditor::snapPulse(int64 pulse, bool floor) {
    if (!snapEnabled) {
        return pulse;
    }

    auto &pattern = processor.getPattern();
    auto timebase = pattern.getTimebase();
    double doubleDivisor = state.divisor;

    double base = (pulse * doubleDivisor) / timebase;
    int64 roundedBase = static_cast<int64>((floor) ? std::floor(base) : std::round(base));

    return roundedBase * (timebase / state.divisor);
}


int64 PatternEditor::xToPulse(int x, bool snap, bool floor) {
    auto &pattern = processor.getPattern();
    auto timebase = pattern.getTimebase();
    double pixelsPerBeat = state.pixelsPerBeat;

    auto pulse = static_cast<int64>(
            std::round((x / pixelsPerBeat) * timebase));

    return jmax(static_cast<int64>(0), (snap) ? snapPulse(pulse, floor) : pulse);
}

int PatternEditor::yToNote(int y) {
    double pixelsPerNote = state.pixelsPerNote;
    return static_cast<int>(std::ceil(((getHeight() / 2.0) - y) / pixelsPerNote - 0.5));
}

int PatternEditor::pulseToX(int64 pulse) {
    auto &pattern = processor.getPattern();
    auto pixelsPerBeat = state.pixelsPerBeat;

    return jmax(0, roundToInt((pulse / static_cast<float>(pattern.getTimebase())) * pixelsPerBeat) + 1);
}

int PatternEditor::noteToY(int note) {
    double pixelsPerNote = state.pixelsPerNote;
    return roundToInt(std::floor((getHeight() / 2.0) - (note + 0.5) * pixelsPerNote)) + 1;
}


PatternEditor::NoteDragAction::NoteOffset::NoteOffset(uint64 i)
        : noteIndex(i) {
    this->startOffset = 0;
    this->endOffset = 0;
    this->noteOffset = 0;
}

PatternEditor::DragAction::DragAction(uint8 type)
        : type(type) {
}

PatternEditor::NoteDragAction::NoteDragAction(
        PatternEditor *editor,
        uint8 type,
        uint64 index,
        std::vector<ArpNote> &allNotes,
        const MouseEvent &event,
        bool offset)
        :
        DragAction(type),
        initiatorIndex(index) {

    noteOffsets.push_back(
            (offset) ? createOffset(editor, allNotes, index, event) : NoteOffset(index));
}

PatternEditor::NoteDragAction::NoteDragAction(
        PatternEditor *editor,
        uint8 type,
        uint64 initiatorIndex,
        std::set<uint64> &indices,
        std::vector<ArpNote> &allNotes,
        const MouseEvent &event,
        bool offset)
        :
        DragAction(type),
        initiatorIndex(initiatorIndex) {

    for (auto index : indices) {
        noteOffsets.push_back(
                (offset) ? createOffset(editor, allNotes, index, event) : NoteOffset(index));
    }
}

PatternEditor::NoteDragAction::NoteOffset PatternEditor::NoteDragAction::createOffset(
        PatternEditor *editor,
        std::vector<ArpNote> &allNotes,
        uint64 noteIndex,
        const MouseEvent &event) {

    auto pulse = editor->xToPulse(event.x);

    auto &note = allNotes[noteIndex];
    auto offset = NoteOffset(noteIndex);
    offset.endOffset = note.endPoint - pulse;
    offset.startOffset = note.startPoint - pulse;
    offset.noteOffset = note.data.noteNumber - editor->yToNote(event.y);

    return offset;
}


PatternEditor::SelectionDragAction::SelectionDragAction(int startX, int startY)
        : DragAction(TYPE_SELECTION_DRAG), startX(startX), startY(startY) {
}
