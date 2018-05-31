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

#pragma once

#include "JuceHeader.h"
#include "../../LibreArp.h"

class PatternEditorView;

class PatternEditor : public Component {

    class DragAction {
    public:
        static const uint8 TYPE_NONE = 0x00;
        static const uint8 TYPE_LOOP_RESIZE = 0x10;
        static const uint8 TYPE_NOTE_MOVE = 0x20;
        static const uint8 TYPE_NOTE_START_RESIZE = 0x21;
        static const uint8 TYPE_NOTE_END_RESIZE = 0x22;

        uint8 type;

        explicit DragAction(uint8 type = TYPE_NONE);
    };

    class NoteDragAction : public DragAction {
    public:
        explicit NoteDragAction(uint8 type, ArpNote &note, int64 offset = 0);

        ArpNote &note;
        int64 offset;
    };

public:

    explicit PatternEditor(LibreArp &p, PatternEditorView *ec);

    void paint(Graphics &g) override;

    void mouseWheelMove(const MouseEvent &event, const MouseWheelDetails &wheel) override;

    void mouseMove(const MouseEvent &event) override;
    void mouseDrag(const MouseEvent &event) override;
    void mouseDown(const MouseEvent &event) override;

    PatternEditorView *getView();

    int getDivisor();
    void setDivisor(int divisor);

private:
    LibreArp &processor;
    PatternEditorView *view;

    int divisor;

    int64 cursorPulse;
    int cursorNote;

    int64 lastNoteLength;

    bool snapEnabled;

    DragAction *dragAction;

    void setDragAction(DragAction *newDragAction);

    void mouseAnyMove(const MouseEvent &event);

    void loopResize(const MouseEvent &event);

    void noteStartResize(const MouseEvent &event, NoteDragAction *dragAction);
    void noteEndResize(const MouseEvent &event, NoteDragAction *dragAction);
    void noteMove(const MouseEvent &event, NoteDragAction *dragAction);
    void noteCreate(const MouseEvent &event);
    void noteDelete(const MouseEvent &event);

    Rectangle<int> getRectangleForNote(ArpNote &note);
    Rectangle<int> getRectangleForLoop();

    int64 snapPulse(int64 pulse, bool floor = false);
    int64 xToPulse(int x, bool snap = true, bool floor = false);
    int yToNote(int y);

    int pulseToX(int64 pulse);
    int noteToY(int note);
};


