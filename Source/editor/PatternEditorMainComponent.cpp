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

#include "PatternEditorMainComponent.h"
#include "PatternEditorComponent.h"

const Colour GRIDLINES_COLOUR = Colour(0, 0, 0);
const Colour POSITION_INDICATOR_COLOUR = Colour(255, 255, 255);
const Colour LOOP_LINE_COLOUR = Colour(255, 0, 0);
const Colour ZERO_LINE_COLOUR = Colour((uint8) 0, 0, 0, 0.10f);

const Colour NOTE_FILL_COLOUR = Colour(104, 134, 183);
const Colour NOTE_ACTIVE_FILL_COLOUR = Colour(171, 187, 214);
const Colour NOTE_BORDER_COLOUR = Colour(0, 0, 0);


PatternEditorMainComponent::PatternEditorMainComponent(LibreArp &p, PatternEditorComponent *ec)
        : processor(p), editorComponent(ec)
{
    setSize(1, 1); // We have to set this, otherwise it won't render at all
}

void PatternEditorMainComponent::paint(Graphics &g) {
    ArpPattern &pattern = processor.getPattern();
    auto pixelsPerBeat = editorComponent->getPixelsPerBeat();
    auto pixelsPerNote = editorComponent->getPixelsPerNote();

    // Set size
    setSize(
            jmax(editorComponent->getRenderWidth(), getParentWidth()),
            jmax(editorComponent->getRenderHeight(), getParentHeight()));

    // Draw note 0
    int top = getHeight() / 2;
    g.setColour(ZERO_LINE_COLOUR);
    g.fillRect(0, top, getWidth(), pixelsPerNote);

    // Draw gridlines
    g.setColour(GRIDLINES_COLOUR);
    for (int i = (getHeight() / 2) % pixelsPerNote; i < getHeight(); i += pixelsPerNote) {
        g.drawLine(0, i, getWidth(), i, 0.5);
    }

    float beatDiv = (pixelsPerBeat / 4.0f);
    int n = 1;
    for (float i = beatDiv; i < getWidth(); i += beatDiv, n++) {
        if (n % 4 == 0) {
            g.drawLine(i, 0, i, getHeight(), 1.5);
        } else {
            g.drawLine(i, 0, i, getHeight(), 0.5);
        }
    }

    // Draw notes
    for (auto &note : pattern.getNotes()) {
        Rectangle noteRect = Rectangle<float>(
                (note.startPoint / static_cast<float>(pattern.getTimebase())) * pixelsPerBeat,
                (getHeight() / 2) + (1 - note.data.noteNumber) * pixelsPerNote,
                ((note.endPoint - note.startPoint) / static_cast<float>(pattern.getTimebase())) * pixelsPerBeat,
                pixelsPerNote);

        g.setColour((note.data.lastNote == -1) ? NOTE_FILL_COLOUR : NOTE_ACTIVE_FILL_COLOUR);
        g.fillRect(noteRect);
        g.setColour(NOTE_BORDER_COLOUR);
        g.drawRect(noteRect);
    }

    // Draw loop line
    g.setColour(LOOP_LINE_COLOUR);
    auto loopLine = static_cast<int>((pattern.loopLength / static_cast<float>(pattern.getTimebase())) * pixelsPerBeat);
    g.drawLine(loopLine, 0, loopLine, getHeight(), 1);

    // Draw position indicator
    g.setColour(POSITION_INDICATOR_COLOUR);
    auto pos = static_cast<int>(((processor.getLastPosition() % pattern.loopLength) / static_cast<double>(pattern.getTimebase())) * (pixelsPerBeat));
    g.drawLine(pos, 0, pos, getHeight());

    if (isVisible()) {
        repaint();
    }
}

void PatternEditorMainComponent::mouseWheelMove(const MouseEvent &event, const MouseWheelDetails &wheel) {
    if (event.mods.isCtrlDown()) {
        if (event.mods.isShiftDown()) {
            editorComponent->zoomPattern(0, wheel.deltaY);
        } else {
            editorComponent->zoomPattern(wheel.deltaY, 0);
        }
    } else {
        Component::mouseWheelMove(event, wheel);
    }
}
