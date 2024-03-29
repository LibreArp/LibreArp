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
          beatBar(p, state, *this),
          noteBar(p, state, *this)
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

    bypassToggle.setButtonText("Bypass");
    bypassToggle.onStateChange = [this] {
        processor.setBypass(bypassToggle.getToggleState());
    };
    addAndMakeVisible(bypassToggle);

    addAndMakeVisible(editor);
    addAndMakeVisible(beatBar);
    addAndMakeVisible(noteBar);

    recentreButton.setButtonText("");
    recentreButton.onClick = [this] {
        resetPatternOffset();
    };
    addAndMakeVisible(recentreButton);

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

    {
        snapMenu.addItem("1/32 beat", 32);
        snapMenu.addItem("1/16 beat", 16);
        snapMenu.addItem("1/12 beat", 12);
        snapMenu.addItem("1/8 beat", 8);
        snapMenu.addItem("1/6 beat", 6);
        snapMenu.addItem("1/4 beat", 4);
        snapMenu.addItem("1/3 beat", 3);
        snapMenu.addItem("1/2 beat", 2);
        snapMenu.addItem("Beat", 1);
    }
    snapMenu.setEditableText(false);
    snapMenu.setScrollWheelEnabled(true);
    snapMenu.onChange = [this] {
        state.divisor = snapMenu.getSelectedId();
        editor.repaint();
    };
    addAndMakeVisible(snapMenu);

    snapMenuLabel.setText("Snap:", juce::NotificationType::dontSendNotification);
    snapMenuLabel.setJustificationType(juce::Justification::centredRight);
    addAndMakeVisible(snapMenuLabel);

    swingSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    swingSlider.setRange(0.0, 1.0);
    swingSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxLeft, false, 42, 24);
    swingSlider.textFromValueFunction = [] (double value) {
        std::stringstream sstream;
        sstream << static_cast<int>(round(value * 100.0)) << " %";
        return sstream.str();
    };
    swingSlider.valueFromTextFunction = [] (const juce::String& text) {
        return text.getDoubleValue() / 100.0;
    };
    // Force-updates the slider to say '0 %' if initialized to zero
    swingSlider.setValue(0.555, juce::NotificationType::dontSendNotification);
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
    float oldBeat = state.targetPixelsPerBeat;
    float oldNote = state.targetPixelsPerNote;
    state.targetPixelsPerBeat = juce::jmax(32.f, state.targetPixelsPerBeat + deltaX * X_ZOOM_RATE);
    state.targetPixelsPerNote = juce::jmax(8.f, state.targetPixelsPerNote + deltaY * Y_ZOOM_RATE);

    float xPerc = state.targetPixelsPerBeat / oldBeat;
    float yPerc = state.targetPixelsPerNote / oldNote;

    state.targetOffsetX *= xPerc;
    state.targetOffsetY *= yPerc;

    if (!processor.getGlobals().isSmoothScrolling()) {
        state.displayOffsetX = state.targetOffsetX;
        state.displayOffsetY = state.targetOffsetY;
        state.displayPixelsPerBeat = state.targetPixelsPerBeat;
        state.displayPixelsPerNote = state.targetPixelsPerNote;
    }

    editor.repaint();
    beatBar.repaint();
    noteBar.repaint();
}

void PatternEditorView::scrollPattern(float deltaX, float deltaY) {
    state.targetOffsetX = juce::jmax(0.f, state.targetOffsetX - static_cast<int>(deltaX * X_SCROLL_RATE));
    state.targetOffsetY = state.targetOffsetY - static_cast<int>(deltaY * Y_SCROLL_RATE);
    if (!processor.getGlobals().isSmoothScrolling()) {
        state.displayOffsetX = state.targetOffsetX;
        state.displayOffsetY = state.targetOffsetY;
    }

    editor.repaint();
    beatBar.repaint();
    noteBar.repaint();
}

void PatternEditorView::updateDisplayDimensions() {
    if (!processor.getGlobals().isSmoothScrolling())
        return;

    const float EPSILON = 0.001;
    const float AGGR = 0.3;
    bool updated = false;

    if (std::abs(state.targetOffsetX - state.displayOffsetX) > EPSILON) {
        state.displayOffsetX = state.displayOffsetX + (state.targetOffsetX - state.displayOffsetX) * AGGR;
        updated = true;
    }

    if (std::abs(state.targetOffsetY - state.displayOffsetY) > EPSILON) {
        state.displayOffsetY = state.displayOffsetY + (state.targetOffsetY - state.displayOffsetY) * AGGR;
        updated = true;
    }

    if (std::abs(state.targetPixelsPerBeat - state.displayPixelsPerBeat) > EPSILON) {
        state.displayPixelsPerBeat = state.displayPixelsPerBeat + (state.targetPixelsPerBeat - state.displayPixelsPerBeat) * AGGR;
        updated = true;
    }

    if (std::abs(state.targetPixelsPerNote - state.displayPixelsPerNote) > EPSILON) {
        state.displayPixelsPerNote = state.displayPixelsPerNote + (state.targetPixelsPerNote - state.displayPixelsPerNote) * AGGR;
        updated = true;
    }

    if (updated) {
        editor.repaint();
        beatBar.repaint();
        noteBar.repaint();
    }
}

void PatternEditorView::resetPatternOffset() {
    state.targetOffsetX = 0;
    state.targetOffsetY = 0;
    if (!processor.getGlobals().isSmoothScrolling()) {
        state.displayOffsetX = state.targetOffsetX;
        state.displayOffsetY = state.targetOffsetY;
    }

    editor.repaint();
    beatBar.repaint();
    noteBar.repaint();
}

void PatternEditorView::audioUpdate() {
    noteBar.audioUpdate();
    editor.audioUpdate();

    if (isVisible()) {
        updateParameterValues();
    }
}

void PatternEditorView::updateParameterValues() {
    loopResetSlider.setValue(processor.getLoopReset(), juce::NotificationType::dontSendNotification);
    snapMenu.setSelectedId(state.divisor, juce::NotificationType::dontSendNotification);
    swingSlider.setValue(processor.getSwing(), juce::NotificationType::dontSendNotification);
    bypassToggle.setToggleState(processor.getBypass(), juce::NotificationType::dontSendNotification);
}

void PatternEditorView::updateLayout() {
    if (!isVisible()) {
        return;
    }

    updateParameterValues();

    auto area = getLocalBounds().reduced(8);

    auto toolBarArea = area.removeFromTop(24);

    loopResetSliderLabel.setBounds(
            toolBarArea.removeFromLeft(8 + loopResetSliderLabel.getFont().getStringWidth(loopResetSliderLabel.getText())));
    loopResetSlider.setBounds(toolBarArea.removeFromLeft(96));
    toolBarArea.removeFromLeft(16);
    swingSliderLabel.setBounds(toolBarArea.removeFromLeft(8 + swingSliderLabel.getFont().getStringWidth(swingSliderLabel.getText())));
    swingSlider.setBounds(toolBarArea.removeFromLeft(128));

    snapMenu.setBounds(toolBarArea.removeFromRight(96));
    snapMenuLabel.setBounds(toolBarArea.removeFromRight(64));

    area.removeFromTop(8);

    auto bottomButtonArea = area.removeFromBottom(24);
    loadButton.setBounds(bottomButtonArea.removeFromLeft(100));
    saveButton.setBounds(bottomButtonArea.removeFromLeft(100));
    bottomButtonArea.removeFromLeft(24);
    bypassToggle.setBounds(bottomButtonArea.removeFromRight(80));

    area.removeFromBottom(8);

    static const auto NOTE_BAR_WIDTH = 45;
    auto beatBarArea = area.removeFromTop(20);
    recentreButton.setBounds(beatBarArea.removeFromLeft(NOTE_BAR_WIDTH));
    beatBar.setBounds(beatBarArea);
    noteBar.setBounds(area.removeFromLeft(NOTE_BAR_WIDTH));
    editor.setBounds(area);
}
