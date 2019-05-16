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

#include <set>
#include "JuceHeader.h"
#include "../../LibreArp.h"
#include "../../AudioUpdatable.h"

class PatternEditorView;

/**
 * The pattern editor component class.
 */
class PatternEditor : public Component, public AudioUpdatable {

    /**
     * The data class of a dragging action.
     */
    class DragAction {
    public:
        static const uint8 TYPE_MASK = 0xF0;

        static const uint8 TYPE_NONE = 0x00;

        static const uint8 TYPE_LOOP = 0x10;
        static const uint8 TYPE_LOOP_RESIZE = 0x10;

        static const uint8 TYPE_NOTE = 0x20;
        static const uint8 TYPE_NOTE_MOVE = 0x20;
        static const uint8 TYPE_NOTE_START_RESIZE = 0x21;
        static const uint8 TYPE_NOTE_END_RESIZE = 0x22;

        static const uint8 TYPE_SELECTION = 0x30;
        static const uint8 TYPE_SELECTION_DRAG = 0x30;



        /**
         * The type of the dragging action.
         */
        uint8 type;



        /**
         * Constructs a new drag action with the specified type.
         *
         * @param type the type of the drag action
         */
        explicit DragAction(uint8 type = TYPE_NONE);
    };

    /**
     * The data class of a note dragging action.
     */
    class NoteDragAction : public DragAction {
    public:

        /**
         * The data class of offset of a note relative to the cursor.
         */
        class NoteOffset {
        public:
            /**
             * Index of the note in the pattern.
             */
            uint64 noteIndex;

            /**
             * The distance between the end of the note and the cursor.
             */
            int64 endOffset;

            /**
             * The distance between the start of the note and the cursor.
             */
            int64 startOffset;

            /**
             * The distance between the number of the note and the cursor.
             */
            int noteOffset;



            /**
             * Constructs a new note offset of the note with the specified index.
             *
             * @param i the index of the note
             */
            explicit NoteOffset(uint64 i);
        };



        /**
         * Constructs a new note drag action.
         *
         * @param editor a pointer to the editor
         * @param type the type of the note drag
         * @param index the index of the dragged note
         * @param allNotes the vector containing all notes in the pattern
         * @param event the mouse event
         * @param offset whether offsets should be calculated
         */
        explicit NoteDragAction(
                PatternEditor *editor,
                uint8 type,
                uint64 index,
                std::vector<ArpNote> &allNotes,
                const MouseEvent &event,
                bool offset = true);

        /**
         * Constructs a new note drag action.
         *
         * @param editor a pointer to the editor
         * @param type the type of the note drag
         * @param initiatorIndex the index of the initiator note
         * @param indices a vector containing the indices of the dragged notes
         * @param allNotes the vector containing all notes in the pattern
         * @param event the mouse event
         * @param offset whether offsets should be calculated
         */
        explicit NoteDragAction(
                PatternEditor *editor,
                uint8 type,
                uint64 initiatorIndex,
                std::set<uint64> &indices,
                std::vector<ArpNote> &allNotes,
                const MouseEvent &event,
                bool offset = true);

        /**
         * The offsets of notes relative to the cursor.
         */
        std::vector<NoteOffset> noteOffsets;

        /**
         * The index of the initiator note.
         */
        uint64 initiatorIndex;

    private:

        /**
         * Calculates an offset.
         *
         * @param editor a pointer to the editor
         * @param allNotes the vector containing all notes in the pattern
         * @param noteIndex the index of the dragged note
         * @param event the mouse event
         *
         * @return the calculated offset
         */
        static NoteOffset createOffset(PatternEditor *editor, std::vector<ArpNote> &allNotes, uint64 noteIndex, const MouseEvent &event);
    };

    /**
     * The data class of a selection rectangle drag.
     */
    class SelectionDragAction : public DragAction {
    public:

        /**
         * Constructs a new selection drag action.
         *
         * @param startX the starting X coordinate of the cursor
         * @param startY the starting Y coordinate of the cursor
         */
        explicit SelectionDragAction(int startX, int startY);

        /**
         * the starting X coordinate of the cursor
         */
        int startX;

        /**
         * the starting Y coordinate of the cursor
         */
        int startY;
    };

public:

    /**
     * Constructs a new pattern editor.
     *
     * @param p the processor
     * @param e the persistent editor state
     * @param ec the parent editor view
     */
    explicit PatternEditor(LibreArp &p, EditorState &e, PatternEditorView *ec);

    void paint(Graphics &g) override;

    void mouseWheelMove(const MouseEvent &event, const MouseWheelDetails &wheel) override;
    void mouseMove(const MouseEvent &event) override;
    void mouseDrag(const MouseEvent &event) override;
    void mouseDown(const MouseEvent &event) override;
    void mouseUp(const MouseEvent &event) override;

    bool keyPressed(const KeyPress &key) override;

    void audioUpdate() override;

    /**
     * Gets the pointer to the parent editor view.
     *
     * @return the pointer to the parent editor view
     */
    PatternEditorView *getView();

private:

    /**
     * The edited processor instance.
     */
    LibreArp &processor;

    /**
     * The persistent state of the editor.
     */
    EditorState &state;

    /**
     * The pointer to the parent editor view.
     */
    PatternEditorView *view;



    /**
     * The pulse that the mouse cursor is hovering.
     */
    int64 cursorPulse;

    /**
     * The note number that the mouse cursor is hovering.
     */
    int cursorNote;



    /**
     * Whether cursor snapping to the grid is enabled.
     */
    bool snapEnabled;



    /**
     * The selection rectangle.
     */
    Rectangle<int> selection;

    /**
     * The set of currently selected notes.
     */
    std::set<uint64> selectedNotes;


    /**
     * A memory buffer for drag action.
     */
    char dragActionBuffer[512];

    /**
     * Current drag action pointer. Points to the <code>dragActionBuffer</code>.
     */
    DragAction *dragAction = (DragAction *) dragActionBuffer;

    /**
     * Last position of the playhead in the X coordinates of the editor since the last audioUpdate.
     */
    int lastPlayPositionX;


    /**
     * Fired on any cursor movement (dragging or non-dragging).
     *
     * @param event the mouse event
     */
    void mouseAnyMove(const MouseEvent &event);

    /**
     * Mouse loop length resize.
     *
     * @param event the mouse event
     */
    void loopResize(const MouseEvent &event);

    /**
     * Mouse note resize from left.
     *
     * @param event the mouse event
     * @param dragAction the drag action
     */
    void noteStartResize(const MouseEvent &event, NoteDragAction *dragAction);

    /**
     * Mouse note resize from right.
     *
     * @param event the mouse event
     * @param dragAction the drag action
     */
    void noteEndResize(const MouseEvent &event, NoteDragAction *dragAction);

    /**
     * Mouse note position move.
     *
     * @param event the mouse event
     * @param dragAction the drag action
     */
    void noteMove(const MouseEvent &event, NoteDragAction *dragAction);

    /**
     * Mouse note duplication.
     *
     * @param dragAction the drag action
     */
    void noteDuplicate(NoteDragAction *dragAction);

    /**
     * Mouse note creation.
     *
     * @param event the mouse event
     */
    void noteCreate(const MouseEvent &event);

    /**
     * Mouse note deletion.
     *
     * @param event the mouse event
     */
    void noteDelete(const MouseEvent &event);

    /**
     * Mouse notes selection.
     *
     * @param event the mouse event
     * @param dragAction the drag action
     */
    void select(const MouseEvent &event, SelectionDragAction *dragAction);



    /**
     * Puts all notes into the selection.
     */
    void selectAll();

    /**
     * Removes all notes from the selection.
     */
    void deselectAll();

    /**
     * Deletes all the selected notes.
     */
    void deleteSelected();

    /**
     * Moves the selected notes up one position.
     */
    void moveSelectedUp(bool octave = false);

    /**
     * Moves the selected notes down one position.
     */
    void moveSelectedDown(bool octave = false);



    /**
     * Gets the rectangle in the canvas that of the specified note that reacts to mouse events.
     *
     * @param note the note
     * @return the rectangle in the canvas that the specified note is rendered in
     */
    Rectangle<int> getRectangleForNote(ArpNote &note);

    /**
     * Gets the active rectangle in the canvas of the loop that reacts to mouse events.
     * @return
     */
    Rectangle<int> getRectangleForLoop();



    /**
     * Snaps the specified pulse to the grid.
     *
     * @param pulse the pulse
     * @param floor whether floor should be used instead of round
     *
     * @return the rounded pulse
     */
    int64 snapPulse(int64 pulse, bool floor = false);

    /**
     * Converts an X coordinate to a pulse position.
     *
     * @param x the X coordinate
     * @param snap whether snap should be used
     * @param floor whether floor should be used instad of round for snapping
     *
     * @return the pulse position
     */
    int64 xToPulse(int x, bool snap = true, bool floor = false);

    /**
     * Converts a Y coordinate to a note number.
     *
     * @param y the Y coordinate
     *
     * @return the note number
     */
    int yToNote(int y);

    /**
     * Converts a pulse position to an X coordinate.
     *
     * @param pulse the pulse position
     *
     * @return the X coordinate
     */
    int pulseToX(int64 pulse);

    /**
     * Converts a note number to a Y coordinate.
     *
     * @param note the note number
     *
     * @return the Y coordinate
     */
    int noteToY(int note);

    void repaintNotes();
};


