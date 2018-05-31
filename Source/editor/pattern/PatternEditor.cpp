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
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//

#include "PatternEditor.h"
#include "PatternEditorView.h"

const Colour GRIDLINES_COLOUR = Colour(0, 0, 0);
const Colour POSITION_INDICATOR_COLOUR = Colour(255, 255, 255);
const Colour LOOP_LINE_COLOUR = Colour(255, 0, 0);
const Colour ZERO_LINE_COLOUR = Colour((uint8) 0, 0, 0, 0.10f);
const Colour NOTE_FILL_COLOUR = Colour(104, 134, 183);

const Colour NOTE_ACTIVE_FILL_COLOUR = Colour(171, 187, 214);
const Colour NOTE_BORDER_COLOUR = Colour(0, 0, 0);

const Colour CURSOR_TIME_COLOUR = Colour((uint8) 255, 255, 255, 0.7f);
const Colour CURSOR_NOTE_COLOUR = Colour((uint8) 255, 255, 255, 0.05f);

const int NOTE_RESIZE_TOLERANCE = 6;
const int LOOP_RESIZE_TOLERANCE = 3;


PatternEditor::PatternEditor(LibreArp &p, PatternEditorView *ec)
        : processor(p), view(ec)
{
    setSize(1, 1); // We have to set this, otherwise it won't render at all

    divisor = 4;
    cursorPulse = 0;
    dragAction = nullptr;
}

void PatternEditor::paint(Graphics &g) {
    ArpPattern &pattern = processor.getPattern();
    auto pixelsPerBeat = view->getPixelsPerBeat();
    auto pixelsPerNote = view->getPixelsPerNote();

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
    for (int i = (getHeight() / 2) % pixelsPerNote; i < getHeight(); i += pixelsPerNote) {
        g.drawLine(0, i, getWidth(), i, 0.5);
    }

    float beatDiv = (pixelsPerBeat / static_cast<float>(divisor));
    int n = 1;
    for (float i = beatDiv; i < getWidth(); i += beatDiv, n++) {
        if (n % divisor == 0) {
            g.drawLine(i, 0, i, getHeight(), 1.5);
        } else {
            g.drawLine(i, 0, i, getHeight(), 0.5);
        }
    }

    // Draw notes
    for (auto &note : pattern.getNotes()) {
        Rectangle noteRect = getRectangleForNote(note);

        g.setColour((note.data.lastNote == -1) ? NOTE_FILL_COLOUR : NOTE_ACTIVE_FILL_COLOUR);
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
    auto pos = pulseToX((processor.getLastPosition() % pattern.loopLength));
    g.drawLine(pos, 0, pos, getHeight());

    // Draw cursor indicator
    g.setColour(CURSOR_TIME_COLOUR);
    auto cursorPulseX = pulseToX(cursorPulse);
    g.drawLine(cursorPulseX, 0, cursorPulseX, getHeight());

    g.setColour(CURSOR_NOTE_COLOUR);
    auto cursorNoteY = noteToY(cursorNote);
    g.fillRect(0, cursorNoteY, getWidth(), pixelsPerNote);

    if (isVisible()) {
        repaint();
    }
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

    for (auto &note : pattern.getNotes()) {
        auto noteRect = getRectangleForNote(note);
        if (noteRect.contains(event.x, event.y)) {
            if (event.x <= (noteRect.getX() + NOTE_RESIZE_TOLERANCE)) {
                setMouseCursor(MouseCursor::LeftRightResizeCursor);
                setDragAction(new NoteDragAction(DragAction::TYPE_NOTE_START_RESIZE, note));
                return;
            } else if (event.x >= (noteRect.getX() + noteRect.getWidth() - NOTE_RESIZE_TOLERANCE)) {
                setMouseCursor(MouseCursor::LeftRightResizeCursor);
                setDragAction(new NoteDragAction(DragAction::TYPE_NOTE_END_RESIZE, note));
                return;
            } else {
                setMouseCursor(MouseCursor::DraggingHandCursor);
                int64 endOffset = note.endPoint - xToPulse(event.x);
                setDragAction(new NoteDragAction(DragAction::TYPE_NOTE_MOVE, note, endOffset));
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
                    break;
                case DragAction::TYPE_NOTE_START_RESIZE:
                    noteStartResize(event, (NoteDragAction *) (this->dragAction));
                    break;
                case DragAction::TYPE_NOTE_END_RESIZE:
                    noteEndResize(event, (NoteDragAction *) (this->dragAction));
                    break;
                case DragAction::TYPE_NOTE_MOVE:
                    noteMove(event, (NoteDragAction *) (this->dragAction));
                    break;
                default:
                    break;
            }
        }
    }
}

void PatternEditor::mouseAnyMove(const MouseEvent &event) {
    cursorPulse = xToPulse(event.x);
    cursorNote = yToNote(event.y);

    setMouseCursor(MouseCursor::NormalCursor);
}


void PatternEditor::loopResize(const MouseEvent &event) {
    int64 lastNoteEnd = 0;
    for (auto note : processor.getPattern().getNotes()) {
        if (note.endPoint > lastNoteEnd) {
            lastNoteEnd = note.endPoint;
        }
    }

    processor.getPattern().loopLength = jmax(lastNoteEnd, xToPulse(event.x));
    processor.buildPattern();
    view->repaint();
    setMouseCursor(MouseCursor::LeftRightResizeCursor);
}

void PatternEditor::noteStartResize(const MouseEvent &event, NoteDragAction *dragAction) {
    dragAction->note.startPoint = jmin(xToPulse(event.x), dragAction->note.endPoint - 1);
    processor.buildPattern();
    setMouseCursor(MouseCursor::LeftRightResizeCursor);
}

void PatternEditor::noteEndResize(const MouseEvent &event, NoteDragAction *dragAction) {
    dragAction->note.endPoint =
            jmin(jmax(xToPulse(event.x), dragAction->note.startPoint + 1), processor.getPattern().loopLength);
    processor.buildPattern();
    setMouseCursor(MouseCursor::LeftRightResizeCursor);
}

void PatternEditor::noteMove(const MouseEvent &event, PatternEditor::NoteDragAction *dragAction) {
    auto &note = dragAction->note;
    auto noteLength = note.endPoint - note.startPoint;
    auto wantedEnd = xToPulse(event.x) + dragAction->offset;

    note.endPoint = jmin(
            jmax(wantedEnd, noteLength),
            processor.getPattern().loopLength);
    note.startPoint = note.endPoint - noteLength;

    note.data.noteNumber = yToNote(event.y);

    processor.buildPattern();

    setMouseCursor(MouseCursor::DraggingHandCursor);
}


PatternEditorView* PatternEditor::getView() {
    return view;
}

int PatternEditor::getDivisor() {
    return divisor;
}

void PatternEditor::setDivisor(int divisor) {
    this->divisor = divisor;
}


Rectangle<int> PatternEditor::getRectangleForNote(ArpNote &note) {
    ArpPattern &pattern = processor.getPattern();
    auto pixelsPerNote = view->getPixelsPerNote();

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


int64 PatternEditor::snapPulse(int64 pulse) {
    auto &pattern = processor.getPattern();
    auto timebase = pattern.getTimebase();
    double doubleDivisor = this->divisor;

    return static_cast<int64>(std::round((pulse * doubleDivisor) / timebase)) * (timebase / divisor);
}


int64 PatternEditor::xToPulse(int x, bool snap) {
    auto &pattern = processor.getPattern();
    auto timebase = pattern.getTimebase();
    double pixelsPerBeat = view->getPixelsPerBeat();

    auto pulse = static_cast<int64>(
            std::round((x / pixelsPerBeat) * timebase));

    return (snap) ? snapPulse(pulse) : pulse;
}

int PatternEditor::yToNote(int y) {
    double pixelsPerNote = view->getPixelsPerNote();
    return static_cast<int>(std::ceil(1 - (y - (getHeight() / 2)) / pixelsPerNote));
}

int PatternEditor::pulseToX(int64 pulse) {
    auto &pattern = processor.getPattern();
    auto pixelsPerBeat = view->getPixelsPerBeat();

    return static_cast<int>((pulse / static_cast<float>(pattern.getTimebase())) * pixelsPerBeat);
}

int PatternEditor::noteToY(int note) {
    auto pixelsPerNote = view->getPixelsPerNote();
    return (getHeight() / 2) + (1 - note) * pixelsPerNote;
}



PatternEditor::DragAction::DragAction(uint8 type)
        : type(type) {
}

PatternEditor::NoteDragAction::NoteDragAction(uint8 type, ArpNote &note, int64 offset)
        : DragAction(type), note(note), offset(offset) {
}
