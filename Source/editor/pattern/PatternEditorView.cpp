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

#include "PatternEditorView.h"

static const int X_ZOOM_RATE = 80;
static const int Y_ZOOM_RATE = 30;
static const int X_SCROLL_RATE = 250;
static const int Y_SCROLL_RATE = 250;

PatternEditorView::PatternEditorView(LibreArp &p, EditorState &e)
        : processor(p),
          state(e),
          presetChooser(
                  "Pattern preset",
                  processor.getGlobals().getPatternPresetsDir(),
                  "*.lapreset"),
          editor(p, state, this),
          beatBar(p, state, this)
{

    loadButton.setButtonText("Load pattern...");
    loadButton.onClick = [this] {
        auto opened = presetChooser.browseForFileToOpen();
        if (opened) {
            processor.loadPatternFromFile(presetChooser.getResult());
            repaint();
        }
    };
    addAndMakeVisible(loadButton);

    saveButton.setButtonText("Save pattern...");
    saveButton.onClick = [this] {
        auto saved = presetChooser.browseForFileToSave(true);
        if (saved) {
            processor.getPattern().toFile(presetChooser.getResult());
        }
    };
    addAndMakeVisible(saveButton);

    addAndMakeVisible(beatBar);
    addAndMakeVisible(editor);

    loopResetSlider.setSliderStyle(juce::Slider::SliderStyle::IncDecButtons);
    loopResetSlider.setRange(0, 65535, 1);
    loopResetSlider.setNumDecimalPlacesToDisplay(0);
    loopResetSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxLeft, false, 32, 24);
    loopResetSlider.setValue(processor.getLoopReset());
    loopResetSlider.onValueChange = [this] {
        processor.setLoopReset(loopResetSlider.getValue());
        processor.stopAll();
    };
    addAndMakeVisible(loopResetSlider);

    loopResetSliderLabel.setText("Reset every (beats):", juce::NotificationType::dontSendNotification);
    loopResetSliderLabel.setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(loopResetSliderLabel);

    snapSlider.setSliderStyle(juce::Slider::SliderStyle::IncDecButtons);
    snapSlider.setRange(1, 16, 1);
    snapSlider.setValue(state.divisor, juce::NotificationType::dontSendNotification);
    snapSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxLeft, false, 32, 24);
    snapSlider.onValueChange = [this] {
        state.divisor = static_cast<int>(snapSlider.getValue());
        editor.repaint();
    };
    addAndMakeVisible(snapSlider);

    snapSliderLabel.setText("Snap:", juce::NotificationType::dontSendNotification);
    snapSliderLabel.setJustificationType(juce::Justification::centredRight);
    addAndMakeVisible(snapSliderLabel);
}

void PatternEditorView::resized() {
    updateLayout();
}

void PatternEditorView::visibilityChanged() {
    Component::visibilityChanged();
    updateLayout();
}

void PatternEditorView::zoomPattern(float deltaX, float deltaY) {
    state.pixelsPerBeat = juce::jmax(32, state.pixelsPerBeat + static_cast<int>(deltaX * X_ZOOM_RATE));
    state.pixelsPerNote = juce::jmax(8, state.pixelsPerNote + static_cast<int>(deltaY * Y_ZOOM_RATE));

    editor.repaint();
    beatBar.repaint();
}

void PatternEditorView::scrollPattern(float deltaX, float deltaY) {
    state.offsetX = juce::jmax(0, state.offsetX - static_cast<int>(deltaX * X_SCROLL_RATE));
    state.offsetY = state.offsetY - static_cast<int>(deltaY * Y_SCROLL_RATE);

    editor.repaint();
    beatBar.repaint();
}

void PatternEditorView::resetPatternOffset() {
    state.offsetX = 0;
    state.offsetY = 0;

    editor.repaint();
    beatBar.repaint();
}


int PatternEditorView::getRenderWidth() {
    auto &pattern = processor.getPattern();
    return static_cast<int>(
            (3 + pattern.loopLength / static_cast<double>(pattern.getTimebase())) * state.pixelsPerBeat);
}

int PatternEditorView::getRenderHeight() {
    auto &pattern = processor.getPattern();

    int dist = 0;
    for (auto &note : pattern.getNotes()) {
        if (std::abs(note.data.noteNumber) > dist) {
            dist = std::abs(note.data.noteNumber);
        }
    }
    dist = 1 + (dist + 3) * 2;

    return dist * state.pixelsPerNote;
}

void PatternEditorView::audioUpdate(uint32_t type) {
    editor.audioUpdate(type);
}

void PatternEditorView::updateLayout() {
    if (!isVisible()) {
        return;
    }

    auto area = getLocalBounds().reduced(8);

    auto toolBarArea = area.removeFromTop(24);
    loopResetSliderLabel.setBounds(
            toolBarArea.removeFromLeft(8 + loopResetSliderLabel.getFont().getStringWidth(loopResetSliderLabel.getText())));
    loopResetSlider.setBounds(toolBarArea.removeFromLeft(96));
    snapSlider.setBounds(toolBarArea.removeFromRight(96));
    snapSliderLabel.setBounds(toolBarArea.removeFromRight(64));

    area.removeFromTop(8);

    auto bottomButtonArea = area.removeFromBottom(24);
    loadButton.setBounds(bottomButtonArea.removeFromLeft(100));
    saveButton.setBounds(bottomButtonArea.removeFromLeft(100));

    area.removeFromBottom(8);

    beatBar.setBounds(area.removeFromTop(20));
    editor.setBounds(area);
}
