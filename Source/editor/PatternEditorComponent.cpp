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

#include "PatternEditorComponent.h"

const Colour BLACK = Colour(0, 0, 0);
const Colour WHITE = Colour(255, 255, 255);
const Colour TRANSPARENT_BLACK = Colour((uint8) 0, 0, 0, 0.10f);
const Colour RED = Colour(255, 0, 0);
const Colour LIGHT_RED = Colour(255, 127, 127);

const int X_ZOOM_RATE = 80;
const int Y_ZOOM_RATE = 30;

PatternEditorComponent::PatternEditorComponent(LibreArp &p)
        : processor(p)
{
    setSize(100, 100);

    this->pixelsPerBeat = 100;
    this->pixelsPerNote = 12;
}

void PatternEditorComponent::paint(Graphics &g) {
    ArpPattern &pattern = processor.getPattern();

    // Determine size
    int dist = INT32_MIN;
    for (auto &note : pattern.getNotes()) {
        if (std::abs(note.data.noteNumber) > dist) {
            dist = std::abs(note.data.noteNumber);
        }
    }
    dist += 3;
    dist *= 2;

    auto width = static_cast<int>((3 + pattern.loopLength / static_cast<double>(pattern.getTimebase())) * pixelsPerBeat);
    auto height = dist * pixelsPerNote;
    setSize(jmax(width, getParentWidth()), jmax(height, getParentHeight()));

    // Draw note 0
    int top = getHeight() / 2;
    g.setColour(TRANSPARENT_BLACK);
    g.fillRect(0, top, getWidth(), pixelsPerNote);

    // Draw gridlines
    g.setColour(BLACK);
    float beatDiv = (pixelsPerBeat / 4.0f);
    int n = 1;
    for (float i = beatDiv; i < getWidth(); i += beatDiv, n++) {
        if (n % 4 == 0) {
            g.drawLine(i, 0, i, getHeight(), 1.5);
        } else {
            g.drawLine(i, 0, i, getHeight(), 0.5);
        }

    }

    g.setColour(BLACK);
    for (int i = (getHeight() / 2) % pixelsPerNote; i < getHeight(); i += pixelsPerNote) {
        g.drawLine(0, i, getWidth(), i, 0.5);
    }


    // Draw notes
    for (auto &note : pattern.getNotes()) {
        Rectangle noteRect = Rectangle<float>(
                (note.startPoint / static_cast<float>(pattern.getTimebase())) * pixelsPerBeat,
                (getHeight() / 2) + (1 - note.data.noteNumber) * pixelsPerNote,
                ((note.endPoint - note.startPoint) / static_cast<float>(pattern.getTimebase())) * pixelsPerBeat,
                pixelsPerNote);

        g.setColour((note.data.lastNote == -1) ? RED : LIGHT_RED);
        g.fillRect(noteRect);
        g.setColour(BLACK);
        g.drawRect(noteRect);
    }


    // Draw position indicator
    g.setColour(WHITE);
    auto pos = static_cast<int>(((processor.getLastPosition() % pattern.loopLength) / static_cast<double>(pattern.getTimebase())) * (pixelsPerBeat));
    g.drawLine(pos, 0, pos, getHeight());

    if (isVisible()) {
        repaint();
    }
}

void PatternEditorComponent::mouseWheelMove(const MouseEvent &event, const MouseWheelDetails &wheel) {
    if (event.mods.isCtrlDown()) {
        if (event.mods.isShiftDown()) {
            pixelsPerNote = jmax(8, pixelsPerNote + static_cast<int>(wheel.deltaY * Y_ZOOM_RATE));
        } else {
            pixelsPerBeat = jmax(32, pixelsPerBeat + static_cast<int>(wheel.deltaY * X_ZOOM_RATE));
        }
    } else {
        Component::mouseWheelMove(event, wheel);
    }
}
