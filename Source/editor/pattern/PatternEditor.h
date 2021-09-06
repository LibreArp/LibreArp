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
#include <juce_gui_basics/juce_gui_basics.h>

#include "../../LibreArp.h"
#include "../../AudioUpdatable.h"

class PatternEditorView;

/**
 * The pattern editor component class.
 */
class PatternEditor : public juce::Component, public AudioUpdatable {

    /**
     * The data class of a dragging action.
     */
    struct DragAction {

        /**
         * The data class of offset of a note relative to the cursor.
         */
        struct NoteOffset {
            /**
             * Index of the note in the pattern.
             */
            uint64_t noteIndex = 0;

            /**
             * The distance between the end of the note and the cursor.
             */
            int64_t endOffset = 0;

            /**
             * The distance between the start of the note and the cursor.
             */
            int64_t startOffset = 0;

            /**
             * The distance between the number of the note and the cursor.
             */
            int noteOffset = 0;
        };

        struct SelectedNote {
            /**
             * Index of the note in the pattern.
             */
            uint64_t noteIndex = 0;

            /**
             * Start of the note relative to selection.
             */
            double relativeStart = 0.0;

            /**
             * End of the note relative to selection.
             */
             double relativeEnd = 0.0;
        };

        static const uint8_t TYPE_MASK = 0xF0;

        static const uint8_t TYPE_NONE = 0x00;

        static const uint8_t TYPE_LOOP = 0x10;
        static const uint8_t TYPE_LOOP_START_RESIZE = 0x10;
        static const uint8_t TYPE_LOOP_END_RESIZE = 0x11;

        static const uint8_t TYPE_NOTE = 0x20;
        static const uint8_t TYPE_NOTE_MOVE = 0x20;
        static const uint8_t TYPE_NOTE_START_RESIZE = 0x21;
        static const uint8_t TYPE_NOTE_END_RESIZE = 0x22;

        static const uint8_t TYPE_SELECTION = 0x30;
        static const uint8_t TYPE_SELECTION_DRAG = 0x30;

        static const uint8_t TYPE_STRETCH = 0x40;
        static const uint8_t TYPE_STRETCH_START = 0x40;
        static const uint8_t TYPE_STRETCH_END = 0x41;


        /**
         * The type of the dragging action.
         */
        uint8_t type = TYPE_NONE;

        /**
         * The offsets of notes relative to the cursor.
         */
        std::vector<NoteOffset> noteOffsets;

        /**
         * Positions of notes relative to the selection.
         */
        std::vector<SelectedNote> selectedNotes;

        /**
         * The index of the initiator note.
         */
        uint64_t initiatorIndex;

        /**
         * The starting X coordinate of the cursor
         */
        int startX;

        /**
         * The starting Y coordinate of the cursor
         */
        int startY;

        void basicDragAction(uint8_t type = TYPE_NONE);

        void noteDragAction(PatternEditor *editor,
                            uint8_t type,
                            uint64_t index,
                            std::vector<ArpNote> &allNotes,
                            const juce::MouseEvent &event,
                            bool offset = true);

        void noteDragAction(PatternEditor *editor,
                            uint8_t type,
                            uint64_t initiatorIndex,
                            std::set<uint64_t> &indices,
                            std::vector<ArpNote> &allNotes,
                            const juce::MouseEvent &event,
                            bool offset = true);

        void selectionDragAction(uint8_t type, int startX, int startY);

        void stretchDragAction(uint8_t type,
                               std::set<uint64_t>& indices,
                               std::vector<ArpNote>& allNotes,
                               int64_t timeSelectionStart,
                               int64_t timeSelectionEnd);

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
        static NoteOffset createOffset(PatternEditor *editor, std::vector<ArpNote> &allNotes, uint64_t noteIndex, const juce::MouseEvent &event);

        /**
         * Creates a basic note offset.
         */
        static NoteOffset createOffset(uint64_t noteIndex);
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

    void paint(juce::Graphics &g) override;
    void mouseWheelMove(const juce::MouseEvent &event, const juce::MouseWheelDetails &wheel) override;
    void mouseMove(const juce::MouseEvent &event) override;
    void mouseDrag(const juce::MouseEvent &event) override;
    void mouseDown(const juce::MouseEvent &event) override;
    void mouseUp(const juce::MouseEvent &event) override;

    void mouseEnter(const juce::MouseEvent& event) override;

    void mouseExit(const juce::MouseEvent& event) override;
    bool keyPressed(const juce::KeyPress &key) override;

    void audioUpdate() override;

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
    int64_t cursorPulse;

    /**
     * The note number that the mouse cursor is hovering.
     */
    int cursorNote;

    /**
     * Whether the mouse cursor is inside the pattern editor.
     */
    bool cursorActive = false;



    /**
     * Whether cursor snapping to the grid is enabled.
     */
    bool snapEnabled;



    /**
     * The selection rectangle.
     */
    juce::Rectangle<int> selection;

    /**
     * The set of currently selected notes.
     */
    std::set<uint64_t> selectedNotes;

    /**
     * The left border of the time selection.
     */
    int64_t timeSelectionStart;

    /**
     * The right border of the time selection.
     */
    int64_t timeSelectionEnd;

    /**
     * Current drag action pointer. Points to the <code>dragActionBuffer</code>.
     */
    DragAction dragAction;

    /**
     * Last position of the playhead in the X coordinates of the editor since the last audioUpdate.
     */
    int lastPlayPositionX;

    /**
     * The last number of input notes (used to trigger a full repaint if the number changes).
     */
    int lastNumInputNotes;

    /**
     * The desired mouse cursor that will actually be changed
     */
    juce::MouseCursor mouseCursor;


    void updateMouseCursor();

    /**
     * Fired on any cursor movement (dragging or non-dragging).
     *
     * @param event the mouse event
     */
    void mouseAnyMove(const juce::MouseEvent &event);

    /**
     * Sets the editor's current drag action according to the mouse position.
     */
    void mouseDetermineDragAction(const juce::MouseEvent &event);

    /**
     * Mouse loop end resize.
     *
     * @param event the mouse event
     */
    void loopStartResize(const juce::MouseEvent &event);

    /**
     * Mouse loop end resize.
     *
     * @param event the mouse event
     */
    void loopEndResize(const juce::MouseEvent &event);

    /**
     * Mouse note resize from left.
     *
     * @param event the mouse event
     * @param dragAction the drag action
     */
    void noteStartResize(const juce::MouseEvent& event);

    /**
     * Mouse note resize from right.
     *
     * @param event the mouse event
     * @param dragAction the drag action
     */
    void noteEndResize(const juce::MouseEvent& event);

    /**
     * Mouse note position move.
     *
     * @param event the mouse event
     * @param dragAction the drag action
     */
    void noteMove(const juce::MouseEvent& event);

    /**
     * Mouse note duplication.
     *
     * @param dragAction the drag action
     */
    void noteDuplicate();

    /**
     * Mouse note velocity reset.
     */
    void noteResetVelocity();

    /**
     * Mouse note creation.
     *
     * @param event the mouse event
     */
    void noteCreate(const juce::MouseEvent &event);

    /**
     * Mouse note deletion.
     *
     * @param event the mouse event
     */
    void noteDelete(const juce::MouseEvent &event);

    /**
     * Mouse notes selection.
     */
    void select(const juce::MouseEvent& event);

    /**
     * Mouse selection stretching, from the selection start.
     */
    void selectionStartStretch(const juce::MouseEvent& event);

    /**
     * Mouse selection stretching, from the selection end.
     */
    void selectionEndStretch(const juce::MouseEvent& event);

    /**
     * Selection stretching, with the specified pulses.
     */
    void selectionStretch(int64_t selectionStart, int64_t selectionEnd);



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
    juce::Rectangle<int> getRectangleForNote(ArpNote &note);

    /**
     * Gets the pulse border of selected notes and writes the result into `outStart` and `outEnd`. The border consists
     * of the lowest `startPoint` and the highest `endPoint` of the selected notes.
     *
     * @return `true` if any notes are selected and the result variables have been written; otherwise `false`
     */
    static bool getNoteSelectionBorder(std::set<uint64_t>& indices,
                                       std::vector<ArpNote>& allNotes,
                                       int64_t& out_start,
                                       int64_t& out_end);

    /**
     * Gets the pulse border of selected notes and writes the result into `outStart` and `outEnd`. The border consists
     * of the lowest `startPoint` and the highest `endPoint` of the selected notes.
     *
     * @return `true` if any notes are selected and the result variables have been written; otherwise `false`
     */
    bool getNoteSelectionBorder(int64_t& out_start, int64_t& out_end);

    /**
     * Snaps the specified pulse to the grid.
     *
     * @param pulse the pulse
     * @param floor whether floor should be used instead of round
     *
     * @return the rounded pulse
     */
    int64_t snapPulse(int64_t pulse, bool floor = false);

    /**
     * Converts a view-space X coordinate to a pulse position.
     *
     * @param x the view-space X coordinate
     * @param snap whether snap should be used
     * @param floor whether floor should be used instad of round for snapping
     *
     * @return the pulse position
     */
    int64_t xToPulse(int x, bool snap = true, bool floor = false);

    /**
     * Converts a view-space Y coordinate to a note number.
     */
    int yToNote(int y);

    /**
     * Converts a pulse position to a view-space X coordinate.
     */
    int pulseToX(int64_t pulse);

    /**
     * Converts a pulse position to absolute X coordinate (not offset by view offsets).
     */
    int pulseToAbsX(int64_t pulse);

    /**
     * Converts a note number to a view-space Y coordinate.
     */
    int noteToY(int note);

    /**
     * Converts a note number to absolute Y coordinate (not offset by view offsets).
     */
    int noteToAbsY(int note);

    /**
     * Tells the renderer to repaint the bounding box of all notes.
     */
    void repaintNotes();

    /**
     * Tells the renderer to repaint the bounding box of selected notes, as well as the selection border.
     */
    void repaintSelectedNotes();
};


