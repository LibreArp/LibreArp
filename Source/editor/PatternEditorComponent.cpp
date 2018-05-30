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

const int X_ZOOM_RATE = 80;
const int Y_ZOOM_RATE = 30;

PatternEditorComponent::PatternEditorComponent(LibreArp &p)
        : processor(p),
          topBar(p, this),
          mainComponent(p, this) {

    this->pixelsPerBeat = 100;
    this->pixelsPerNote = 12;

    mainComponentViewport.setViewedComponent(&mainComponent);
    addAndMakeVisible(mainComponentViewport);

    topBarViewport.setViewedComponent(&topBar);
    topBarViewport.setScrollBarsShown(false, false, false, false);
    addAndMakeVisible(topBarViewport);
}

void PatternEditorComponent::paint(Graphics &g) {
    topBarViewport.setViewPosition(mainComponentViewport.getViewPositionX(), topBarViewport.getViewPositionY());
}

void PatternEditorComponent::resized() {
    auto area = getLocalBounds();
    topBarViewport.setBounds(area.removeFromTop(16));
    mainComponentViewport.setBounds(area);
}


int PatternEditorComponent::getPixelsPerBeat() {
    return this->pixelsPerBeat;
}

int PatternEditorComponent::getPixelsPerNote() {
    return this->pixelsPerNote;
}

void PatternEditorComponent::zoomPattern(float deltaX, float deltaY) {
    pixelsPerBeat = jmax(32, pixelsPerBeat + static_cast<int>(deltaX * X_ZOOM_RATE));
    pixelsPerNote = jmax(8, pixelsPerNote + static_cast<int>(deltaY * Y_ZOOM_RATE));

    mainComponent.repaint();
    topBar.repaint();
}


int PatternEditorComponent::getRenderWidth() {
    auto pattern = processor.getPattern();
    return static_cast<int>((3 + pattern.loopLength / static_cast<double>(pattern.getTimebase())) * pixelsPerBeat);
}

int PatternEditorComponent::getRenderHeight() {
    auto pattern = processor.getPattern();

    int dist = INT32_MIN;
    for (auto &note : pattern.getNotes()) {
        if (std::abs(note.data.noteNumber) > dist) {
            dist = std::abs(note.data.noteNumber);
        }
    }
    dist += 3;
    dist *= 2;

    return dist * pixelsPerNote;
}
