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

#include "PatternEditorView.h"

const int X_ZOOM_RATE = 80;
const int Y_ZOOM_RATE = 30;

PatternEditorView::PatternEditorView(LibreArp &p)
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

void PatternEditorView::paint(Graphics &g) {
    topBarViewport.setViewPosition(mainComponentViewport.getViewPositionX(), topBarViewport.getViewPositionY());
}

void PatternEditorView::resized() {
    auto area = getLocalBounds();
    topBarViewport.setBounds(area.removeFromTop(16));
    mainComponentViewport.setBounds(area);
}


int PatternEditorView::getPixelsPerBeat() {
    return this->pixelsPerBeat;
}

int PatternEditorView::getPixelsPerNote() {
    return this->pixelsPerNote;
}

void PatternEditorView::zoomPattern(float deltaX, float deltaY) {
    double xPercent = mainComponentViewport.getViewPositionX() / static_cast<double>(mainComponent.getWidth());
    double yPercent = mainComponentViewport.getViewPositionY() / static_cast<double>(mainComponent.getHeight());
    pixelsPerBeat = jmax(32, pixelsPerBeat + static_cast<int>(deltaX * X_ZOOM_RATE));
    pixelsPerNote = jmax(8, pixelsPerNote + static_cast<int>(deltaY * Y_ZOOM_RATE));

    mainComponentViewport.setViewPosition(
            static_cast<int>(xPercent * getRenderWidth()),
            static_cast<int>(yPercent * getRenderHeight()));

    mainComponent.repaint();
    topBar.repaint();
}


int PatternEditorView::getRenderWidth() {
    auto pattern = processor.getPattern();
    return static_cast<int>((3 + pattern.loopLength / static_cast<double>(pattern.getTimebase())) * pixelsPerBeat);
}

int PatternEditorView::getRenderHeight() {
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
