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
          editor(p, state, *this),
          beatBar(p, state, *this)
{

    loadButton.setButtonText("Load pattern...");
    loadButton.onClick = [this] {
        using Flags = juce::FileBrowserComponent::FileChooserFlags;
        presetChooser.launchAsync(
                Flags::openMode | Flags::canSelectFiles,
                [this](auto& chooser) {
                    auto results = chooser.getResults();
                    if (!results.isEmpty() && results[0].existsAsFile()) {
                        processor.loadPatternFromFile(results[0]);
                        repaint();
                    }
                });
    };
    addAndMakeVisible(loadButton);

    saveButton.setButtonText("Save pattern...");
    saveButton.onClick = [this] {
        using Flags = juce::FileBrowserComponent::FileChooserFlags;
        presetChooser.launchAsync(
                Flags::saveMode | Flags::canSelectFiles | Flags::warnAboutOverwriting,
                [this](auto& chooser) {
                    auto results = chooser.getResults();
                    if (!results.isEmpty()) {
                        processor.getPattern().toFile(results[0]);
                    }
                });
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

    swingSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    swingSlider.setRange(0.0, 1.0);
    swingSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxLeft, true, 32, 24);
    swingSlider.textFromValueFunction = [] (double value) {
        std::stringstream sstream;
        sstream.setf(std::ios::fixed);
        sstream.precision(2);
        sstream << value;
        return sstream.str();
    };
    swingSlider.setValue(processor.getSwing());
    swingSlider.onValueChange = [this] {
        processor.setSwing(static_cast<float>(swingSlider.getValue()));
    };
    addAndMakeVisible(swingSlider);

    swingSliderLabel.setText("Swing:", juce::NotificationType::dontSendNotification);
    swingSliderLabel.setJustificationType(juce::Justification::centredRight);
    addAndMakeVisible(swingSliderLabel);
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

void PatternEditorView::audioUpdate() {
    editor.audioUpdate();
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
    swingSliderLabel.setBounds(toolBarArea.removeFromLeft(24 + swingSliderLabel.getFont().getStringWidth(swingSliderLabel.getText())));
    swingSlider.setBounds(toolBarArea.removeFromLeft(128));
    snapSlider.setBounds(toolBarArea.removeFromRight(96));
    snapSliderLabel.setBounds(toolBarArea.removeFromRight(64));

    area.removeFromTop(8);

    auto bottomButtonArea = area.removeFromBottom(24);
    loadButton.setBounds(bottomButtonArea.removeFromLeft(100));
    saveButton.setBounds(bottomButtonArea.removeFromLeft(100));

    area.removeFromBottom(8);

    beatBar.setBounds(area.removeFromTop(20));
    editor.setBounds(area);

    swingSlider.setValue(processor.getSwing());
}
