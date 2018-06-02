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
          beatBar(p, this),
          editor(p, this) {

    this->pixelsPerBeat = 100;
    this->pixelsPerNote = 12;

    editorViewport.setViewedComponent(&editor);
    addAndMakeVisible(editorViewport);

    beatBarViewport.setViewedComponent(&beatBar);
    beatBarViewport.setScrollBarsShown(false, false, false, false);
    addAndMakeVisible(beatBarViewport);

    snapSlider.setSliderStyle(Slider::SliderStyle::IncDecButtons);
    snapSlider.setRange(1, 16, 1);
    snapSlider.setValue(editor.getDivisor(), NotificationType::dontSendNotification);
    snapSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxLeft, false, 32, 24);
    snapSlider.onValueChange = [this] {
        editor.setDivisor(static_cast<int>(snapSlider.getValue()));
        editor.repaint();
    };
    addAndMakeVisible(snapSlider);

    snapSliderLabel.setText("Snap:", NotificationType::dontSendNotification);
    snapSliderLabel.setJustificationType(Justification::centredRight);
    addAndMakeVisible(snapSliderLabel);
}

void PatternEditorView::paint(Graphics &g) {
    beatBarViewport.setViewPosition(editorViewport.getViewPositionX(), beatBarViewport.getViewPositionY());
}

void PatternEditorView::resized() {
    auto area = getLocalBounds();

    auto toolBarArea = area.removeFromTop(32);
    toolBarArea.removeFromBottom(4);
    toolBarArea.removeFromTop(4);
    snapSlider.setBounds(toolBarArea.removeFromRight(96));
    snapSliderLabel.setBounds(toolBarArea.removeFromRight(64));

    beatBarViewport.setBounds(area.removeFromTop(16));
    editorViewport.setBounds(area);
}


int PatternEditorView::getPixelsPerBeat() {
    return this->pixelsPerBeat;
}

int PatternEditorView::getPixelsPerNote() {
    return this->pixelsPerNote;
}

void PatternEditorView::zoomPattern(float deltaX, float deltaY) {
    double xPercent = editorViewport.getViewPositionX() / static_cast<double>(editor.getWidth());
    double yPercent = editorViewport.getViewPositionY() / static_cast<double>(editor.getHeight());
    pixelsPerBeat = jmax(32, pixelsPerBeat + static_cast<int>(deltaX * X_ZOOM_RATE));
    pixelsPerNote = jmax(8, pixelsPerNote + static_cast<int>(deltaY * Y_ZOOM_RATE));

    editorViewport.setViewPosition(
            static_cast<int>(xPercent * getRenderWidth()),
            static_cast<int>(yPercent * getRenderHeight()));

    editor.repaint();
    beatBar.repaint();
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
