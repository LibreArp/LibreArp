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

#include "PatternEditor.h"
#include "PatternEditorView.h"

const Colour GRIDLINES_COLOUR = Colour(0, 0, 0);
const Colour POSITION_INDICATOR_COLOUR = Colour(255, 255, 255);
const Colour LOOP_LINE_COLOUR = Colour(255, 0, 0);
const Colour ZERO_LINE_COLOUR = Colour((uint8) 0, 0, 0, 0.10f);

const Colour NOTE_FILL_COLOUR = Colour((uint8) 117, 169, 255, 0.7f);
const Colour NOTE_ACTIVE_FILL_COLOUR = Colour(191, 215, 255);
const Colour NOTE_SELECTED_FILL_COLOUR = Colour(244, 152, 66);
const Colour NOTE_SELECTED_ACTIVE_FILL_COLOUR = Colour(255, 199, 147);
const Colour NOTE_BORDER_COLOUR = Colour((uint8) 0, 0, 0, 0.5f);

const Colour CURSOR_TIME_COLOUR = Colour((uint8) 255, 255, 255, 0.7f);
const Colour CURSOR_NOTE_COLOUR = Colour((uint8) 255, 255, 255, 0.05f);

const Colour SELECTION_BORDER_COLOUR = Colour(255, 0, 0);

const int NOTE_RESIZE_TOLERANCE = 6;
const int LOOP_RESIZE_TOLERANCE = 3;


PatternEditor::PatternEditor(LibreArp &p, EditorState &e, PatternEditorView *ec)
        : processor(p), state(e), view(ec)
{
    setSize(1, 1); // We have to set this, otherwise it won't render at all

    cursorPulse = 0;
    dragAction = nullptr;
    if (state.lastNoteLength < 1) {
        state.lastNoteLength = processor.getPattern().getTimebase() / state.divisor;
    }
    snapEnabled = true;
    selection = Rectangle<int>(0, 0, 0, 0);

    setWantsKeyboardFocus(true);
}

PatternEditor::~PatternEditor() {
    delete dragAction;
}

void PatternEditor::paint(Graphics &g) {
    ArpPattern &pattern = processor.getPattern();
    auto pixelsPerBeat = state.pixelsPerBeat;
    auto pixelsPerNote = state.pixelsPerNote;

    // Set size
    setSize(
            jmax(view->getRenderWidth(), getParentWidth()),
            jmax(view->getRenderHeight(), getParentHeight()));

    // Draw note 0
    int noteZeroY = noteToY(0);
    g.setColour(ZERO_LINE_COLOUR);
    g.fillRect(0, noteZeroY, getWidth(), pixelsPerNote);

    // Draw gridlines
    g.setColour(GRIDLINES_COLOUR);
    for (int i = (getHeight() / 2) % pixelsPerNote - pixelsPerNote / 2; i < getHeight(); i += pixelsPerNote) {
        g.drawLine(0, i, getWidth(), i, 0.5);
    }

    float beatDiv = (pixelsPerBeat / static_cast<float>(state.divisor));
    int n = 1;
    for (float i = beatDiv; i < getWidth(); i += beatDiv, n++) {
        if (n % state.divisor == 0) {
            g.drawLine(i, 0, i, getHeight(), 1.5);
        } else {
            g.drawLine(i, 0, i, getHeight(), 0.5);
        }
    }

    // Draw notes
    auto &notes = pattern.getNotes();
    for (int i = 0; i < notes.size(); i++) {
        auto &note = notes[i];
        Rectangle<int> noteRect = getRectangleForNote(note);

        if (selectedNotes.find(i) == selectedNotes.end()) {
            g.setColour((note.data.lastNote == -1) ? NOTE_FILL_COLOUR : NOTE_ACTIVE_FILL_COLOUR);
        } else {
            g.setColour((note.data.lastNote == -1) ? NOTE_SELECTED_FILL_COLOUR : NOTE_SELECTED_ACTIVE_FILL_COLOUR);
        }
        g.fillRect(noteRect);
        g.setColour(NOTE_BORDER_COLOUR);
        g.drawRect(noteRect);
    }

    // Draw loop line
    g.setColour(LOOP_LINE_COLOUR);
    auto loopLine = pulseToX(pattern.loopLength);
    g.drawLine(loopLine, 0, loopLine, getHeight(), 1);

    // Draw position indicator
    g.setColour(POSITION_INDICATOR_COLOUR);
    auto position = processor.getLastPosition();
    if (processor.getLoopReset() > 0.0) {
        position %= static_cast<int64>(processor.getLoopReset() * pattern.getTimebase());
    }
    position %= pattern.loopLength;
    auto positionX = pulseToX(position);
    g.drawLine(positionX, 0, positionX, getHeight());

    // Draw cursor indicator
    g.setColour(CURSOR_TIME_COLOUR);
    auto cursorPulseX = pulseToX(cursorPulse);
    g.drawLine(cursorPulseX, 0, cursorPulseX, getHeight());

    // Draw selection
    if (selection.getWidth() != 0 && selection.getHeight() != 0) {
        g.setColour(SELECTION_BORDER_COLOUR);
        g.drawRect(selection, 3);
    }

    g.setColour(CURSOR_NOTE_COLOUR);
    auto cursorNoteY = noteToY(cursorNote);
    g.fillRect(0, cursorNoteY, getWidth(), pixelsPerNote);
}


void PatternEditor::setDragAction(DragAction *newDragAction) {
    delete this->dragAction;
    this->dragAction = newDragAction;
}


void PatternEditor::mouseWheelMove(const MouseEvent &event, const MouseWheelDetails &wheel) {
    if (event.mods.isCtrlDown()) {
        if (event.mods.isShiftDown()) {
            view->zoomPattern(0, wheel.deltaY);
        } else {
            view->zoomPattern(wheel.deltaY, 0);
        }
    } else {
        Component::mouseWheelMove(event, wheel);
    }
}

void PatternEditor::mouseMove(const MouseEvent &event) {
    auto &pattern = processor.getPattern();

    mouseAnyMove(event);

    auto &notes = pattern.getNotes();
    for (uint64 i = 0; i < notes.size(); i++) {
        auto &note = notes[i];
        auto noteRect = getRectangleForNote(note);
        if (noteRect.contains(event.x, event.y)) {
            if (event.x <= (noteRect.getX() + NOTE_RESIZE_TOLERANCE)) {
                setMouseCursor(MouseCursor::LeftEdgeResizeCursor);
                if (selectedNotes.find(i) == selectedNotes.end()) {
                    setDragAction(new NoteDragAction(this, DragAction::TYPE_NOTE_START_RESIZE, i, notes, event));
                } else {
                    setDragAction(new NoteDragAction(this, DragAction::TYPE_NOTE_START_RESIZE, selectedNotes, notes, event));
                }
                return;
            } else if (event.x >= (noteRect.getX() + noteRect.getWidth() - NOTE_RESIZE_TOLERANCE)) {
                setMouseCursor(MouseCursor::RightEdgeResizeCursor);
                if (selectedNotes.find(i) == selectedNotes.end()) {
                    setDragAction(new NoteDragAction(this, DragAction::TYPE_NOTE_END_RESIZE, i, notes, event));
                } else {
                    setDragAction(new NoteDragAction(this, DragAction::TYPE_NOTE_END_RESIZE, selectedNotes, notes, event));
                }
                return;
            } else {
                setMouseCursor(MouseCursor::DraggingHandCursor);
                if (selectedNotes.find(i) == selectedNotes.end()) {
                    setDragAction(new NoteDragAction(this, DragAction::TYPE_NOTE_MOVE, i, notes, event));
                } else {
                    setDragAction(new NoteDragAction(this, DragAction::TYPE_NOTE_MOVE, selectedNotes, notes, event));
                }
                return;
            }
        }
    }

    auto loopRect = getRectangleForLoop();
    if (loopRect.contains(event.x, event.y)) {
        setMouseCursor(MouseCursor::LeftRightResizeCursor);
        setDragAction(new DragAction(DragAction::TYPE_LOOP_RESIZE));
        return;
    }

    setDragAction(nullptr);
}

void PatternEditor::mouseDrag(const MouseEvent &event) {
    mouseAnyMove(event);

    if (event.mods.isLeftButtonDown() && !event.mods.isRightButtonDown() && !event.mods.isMiddleButtonDown()) {
        if (this->dragAction != nullptr) {
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
    cursorPulse = xToPulse(event.x);
    cursorNote = yToNote(event.y);

    snapEnabled = !(event.mods.isAltDown() || (event.mods.isCtrlDown() && event.mods.isShiftDown()));

    setMouseCursor(MouseCursor::NormalCursor);
    repaint();
}

void PatternEditor::mouseDown(const MouseEvent &event) {
    if (event.mods.isLeftButtonDown() && !event.mods.isRightButtonDown() && !event.mods.isMiddleButtonDown()) {
        if (this->dragAction == nullptr) {
            if (event.mods.isCtrlDown()) {
                selectedNotes.clear();
                setDragAction(new SelectionDragAction(event.x, event.y));
                repaint();
            } else {
                selectedNotes.clear();
                noteCreate(event);
                repaint();
            }
        } else {
            switch(this->dragAction->type) {
                case DragAction::TYPE_NOTE_MOVE: {
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
        repaint();
        Component::mouseDown(event);
        return;
    }

    repaint();
    Component::mouseDown(event);
}

void PatternEditor::mouseUp(const MouseEvent &event) {
    setDragAction(nullptr);
    selection = Rectangle<int>(0, 0, 0, 0);
    setMouseCursor(MouseCursor::NormalCursor);
    repaint();
    Component::mouseUp(event);
}


bool PatternEditor::keyPressed(const KeyPress &key) {
    if (key == KeyPress::deleteKey || key == KeyPress::numberPadDelete) {
        deleteSelected();
        return false;
    }

    if (key.isKeyCode(KeyPress::upKey)) {
        moveSelectedUp();
        return false;
    }

    if (key.isKeyCode(KeyPress::downKey)) {
        moveSelectedDown();
        return false;
    }

    if (key == KeyPress::createFromDescription("CTRL+A")) {
        selectAll();
        return false;
    }

    if (key == KeyPress::createFromDescription("CTRL+D")) {
        deselectAll();
        return false;
    }

    return true;
}


void PatternEditor::loopResize(const MouseEvent &event) {
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
    auto timebase = processor.getPattern().getTimebase();
    auto &notes = processor.getPattern().getNotes();

    for (auto &noteOffset : dragAction->noteOffsets) {
        auto &note = notes[noteOffset.noteIndex];
        int64 minSize = (snapEnabled) ? (timebase / state.divisor) : 1;
        note.startPoint = jmax((int64) 0, jmin(xToPulse(event.x) + noteOffset.startOffset, note.endPoint - minSize));

        state.lastNoteLength = note.endPoint - note.startPoint;
    }

    processor.buildPattern();
    repaint();
    setMouseCursor(MouseCursor::LeftEdgeResizeCursor);
}

void PatternEditor::noteEndResize(const MouseEvent &event, NoteDragAction *dragAction) {
    auto timebase = processor.getPattern().getTimebase();
    auto &notes = processor.getPattern().getNotes();

    for (auto &noteOffset : dragAction->noteOffsets) {
        auto &note = notes[noteOffset.noteIndex];
        int64 minSize = (snapEnabled) ? (timebase / state.divisor) : 1;
        note.endPoint =
                jmin(jmax(xToPulse(event.x) + noteOffset.endOffset, note.startPoint + minSize),
                     processor.getPattern().loopLength);

        state.lastNoteLength = note.endPoint - note.startPoint;
    }

    processor.buildPattern();
    repaint();
    setMouseCursor(MouseCursor::RightEdgeResizeCursor);
}

void PatternEditor::noteMove(const MouseEvent &event, PatternEditor::NoteDragAction *dragAction) {
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
    repaint();

    setMouseCursor(MouseCursor::DraggingHandCursor);
}

void PatternEditor::noteDuplicate(PatternEditor::NoteDragAction *dragAction) {
    auto &notes = processor.getPattern().getNotes();
    for (auto &noteOffset : dragAction->noteOffsets) {
        processor.getPattern().getNotes().push_back(notes[noteOffset.noteIndex]);
    }
    processor.buildPattern();
}

void PatternEditor::noteCreate(const MouseEvent &event) {
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
    repaint();

    if (event.mods.isShiftDown()) {
        setDragAction(new NoteDragAction(this, DragAction::TYPE_NOTE_END_RESIZE, index, notes, event, false));
    } else {
        setDragAction(new NoteDragAction(this, DragAction::TYPE_NOTE_MOVE, index, notes, event));
    }
}

void PatternEditor::noteDelete(const MouseEvent &event) {
    auto &pattern = processor.getPattern();
    auto &notes = pattern.getNotes();
    bool erased = false;

    for (auto it = notes.begin(); it != notes.end(); it++) {
        auto &note = *it;
        auto noteRect = getRectangleForNote(note);

        if (noteRect.contains(event.x, event.y)) {
            notes.erase(it);
            erased = true;
            setDragAction(nullptr);
            break;
        }
    }

    if (erased) {
        processor.buildPattern();
        repaint();
    }
}


void PatternEditor::selectAll() {
    auto &notes = processor.getPattern().getNotes();
    for (int i = 0; i < notes.size(); i++) {
        selectedNotes.insert(i);
    }
    repaint();
}

void PatternEditor::deselectAll() {
    selectedNotes.clear();
    repaint();
}

void PatternEditor::deleteSelected() {
    auto &notes = processor.getPattern().getNotes();
    for (auto it = selectedNotes.rbegin(); it != selectedNotes.rend(); it++) {
        auto index = *it;
        notes[index] = notes.back();
        notes.pop_back();
    }
    selectedNotes.clear();
    setDragAction(nullptr);
    processor.buildPattern();
    repaint();
}

void PatternEditor::moveSelectedUp() {
    auto &notes = processor.getPattern().getNotes();
    for (auto index : selectedNotes) {
        notes[index].data.noteNumber++;
    }
    processor.buildPattern();
    repaint();
}

void PatternEditor::moveSelectedDown() {
    auto &notes = processor.getPattern().getNotes();
    for (auto index : selectedNotes) {
        notes[index].data.noteNumber--;
    }
    processor.buildPattern();
    repaint();
}


void PatternEditor::select(const MouseEvent &event, PatternEditor::SelectionDragAction *dragAction) {
    selection = Rectangle<int>(Point<int>(event.x, event.y), Point<int>(dragAction->startX, dragAction->startY));

    selectedNotes.clear();
    auto &notes = processor.getPattern().getNotes();
    for(int i = 0; i < notes.size(); i++) {
        auto &note = notes[i];
        auto noteRect = getRectangleForNote(note);
        if (selection.intersects(noteRect)) {
            selectedNotes.insert(i);
        }
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

    return (snap) ? snapPulse(pulse, floor) : pulse;
}

int PatternEditor::yToNote(int y) {
    double pixelsPerNote = state.pixelsPerNote;
    return static_cast<int>(std::ceil(((getHeight() / 2.0) - y) / pixelsPerNote - 0.5));
}

int PatternEditor::pulseToX(int64 pulse) {
    auto &pattern = processor.getPattern();
    auto pixelsPerBeat = state.pixelsPerBeat;

    return static_cast<int>((pulse / static_cast<float>(pattern.getTimebase())) * pixelsPerBeat);
}

int PatternEditor::noteToY(int note) {
    double pixelsPerNote = state.pixelsPerNote;
    return static_cast<int>(std::round((getHeight() / 2.0) - (note + 0.5) * pixelsPerNote));
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
        : DragAction(type) {

    noteOffsets.push_back(
            (offset) ? createOffset(editor, allNotes, index, event) : NoteOffset(index));
}

PatternEditor::NoteDragAction::NoteDragAction(
        PatternEditor *editor,
        uint8 type,
        std::set<uint64> &indices,
        std::vector<ArpNote> &allNotes,
        const MouseEvent &event,
        bool offset)
        : DragAction(type) {

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
