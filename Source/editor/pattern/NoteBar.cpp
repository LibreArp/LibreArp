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

#include <algorithm>

#include "PatternEditorView.h"
#include "../style/Colours.h"
#include "../../util/MathConsts.h"

#include "NoteBar.h"

NoteBar::NoteBar(LibreArp &p, EditorState &e, PatternEditorView &ec)
        : processor(p), state(e), view(ec) {
    setOpaque(true);
}

void NoteBar::paint(juce::Graphics &g) {
    g.setColour(Style::BEATBAR_BACKGROUND_COLOUR);
    g.fillRect(getLocalBounds());
    g.setColour(Style::BEATBAR_BORDER_COLOUR);
    g.fillRect(getWidth() - 1, 0, 1, getHeight());

    // Draw note numbers
    static const auto NOTE_NUMBER_WIDTH = 14;
    int inputs = (processor.getNumInputNotes() > 0) ? processor.getNumInputNotes() : 1;
    int startingNote = yToNote(getHeight());
    int endingNote = yToNote(0) + 1;
    g.setFont(std::min(state.displayPixelsPerNote, 14.0f));
    for (int i = startingNote; i < endingNote; i++) {
        int onote = i % inputs;
        if (onote < 0)
            onote += inputs;
        int y = noteToY(i);

        if (processor.getNumInputNotes() > 0) {
            g.setColour(Style::BEATBAR_NUMBER_COLOUR);
            g.drawText(
                    juce::String(1 + onote),
                    getWidth() - NOTE_NUMBER_WIDTH, y, NOTE_NUMBER_WIDTH, state.displayPixelsPerNote,
                    juce::Justification::centred);
        }

    }

    // Draw octaves
    startingNote = (yToNote(getHeight()) / inputs) * inputs - inputs - 1;
    endingNote = (yToNote(0) / inputs + 1) * inputs;
    g.setFont(22);
    for (int i = startingNote; i < endingNote; i += inputs) {
        int octave = std::abs(i / inputs);
        if (i < 0)
            octave++;
        juce::String sign = (octave == 0) ? "" : (i < 0) ? "-" : "+";
        int y = noteToY(i);

        g.setColour(Style::BEATBAR_NUMBER_COLOUR);
        g.drawText(
                sign + juce::String(octave),
                0, y, getWidth() - NOTE_NUMBER_WIDTH, state.displayPixelsPerNote * inputs,
                juce::Justification::centred);

        g.setColour(Style::BEATBAR_LINE_COLOUR);
        g.drawRect(0, y - 1, getWidth(), 2);
    }
}

void NoteBar::audioUpdate() {
    auto procNum = this->processor.getNumInputNotes();
    if (procNum != this->lastNumInputNotes) {
        this->lastNumInputNotes = procNum;
        this->repaint();
    }
}

void NoteBar::mouseWheelMove(const juce::MouseEvent &event, const juce::MouseWheelDetails &wheel) {
    if (event.mods.isShiftDown()) {
        view.zoomPattern(wheel.deltaY, 0);
    } else {
        view.zoomPattern(0, wheel.deltaY);
    }
}

void NoteBar::mouseDown(const juce::MouseEvent& event) {
    if (!event.mods.isLeftButtonDown() && !event.mods.isRightButtonDown() && event.mods.isMiddleButtonDown()) {
        view.resetPatternOffset();
        return;
    }

    Component::mouseDown(event);
}
