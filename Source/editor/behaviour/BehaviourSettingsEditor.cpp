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

#include "BehaviourSettingsEditor.h"

BehaviourSettingsEditor::BehaviourSettingsEditor(LibreArp &p) : processor(p) {
    midiInChannelSlider.setSliderStyle(juce::Slider::SliderStyle::IncDecButtons);
    midiInChannelSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxLeft, false, 32, 24);
    midiInChannelSlider.setRange(0, 16, 1);
    midiInChannelSlider.textFromValueFunction = [](auto value) {
        return (value == 0) ? juce::String("Any") : juce::String(value);
    };
    midiInChannelSlider.onValueChange = [this] {
        processor.setInputMidiChannel(static_cast<int>(midiInChannelSlider.getValue()));
    };
    midiInChannelLabel.setText("MIDI Input Channel", juce::NotificationType::dontSendNotification);

    midiOutChannelSlider.setSliderStyle(juce::Slider::SliderStyle::IncDecButtons);
    midiOutChannelSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxLeft, false, 32, 24);
    midiOutChannelSlider.setRange(1, 16, 1);
    midiOutChannelSlider.onValueChange = [this] {
        processor.setOutputMidiChannel(static_cast<int>(midiOutChannelSlider.getValue()));
    };
    midiOutChannelLabel.setText("MIDI Output Channel", juce::NotificationType::dontSendNotification);

    octavesToggle.setButtonText("Octave transposition");
    octavesToggle.setTooltip("Enables transposition by octaves when hitting notes that are out of bounds");
    octavesToggle.onStateChange = [this] {
        processor.setTransposingOctaves(octavesToggle.getToggleState());
        smartOctavesToggle.setEnabled(octavesToggle.getToggleState());
    };

    smartOctavesToggle.setButtonText("Smart octaves");
    smartOctavesToggle.setTooltip("Enables transposition by the number of octaves spanned by the input notes");
    smartOctavesToggle.onStateChange = [this] {
        processor.setUsingSmartOctaves(smartOctavesToggle.getToggleState());
    };

    usingInputVelocityToggle.setButtonText("Use input note velocity");
    usingInputVelocityToggle.setTooltip("Enables using the velocity of input notes to calculate output velocity.");
    usingInputVelocityToggle.onStateChange = [this] {
        processor.setUsingInputVelocity(usingInputVelocityToggle.getToggleState());
    };

    const juce::String nonPlayingModeTooltip = "Affects how the plugin behaves when the host is not playing.";
    {
        using namespace NonPlayingMode;
        nonPlayingModeComboBox.addItem(
                "Default (Global)", static_cast<int>(Value::NONE));
        nonPlayingModeComboBox.addItem(
                NonPlayingMode::getDisplayName(Value::SILENCE), static_cast<int>(Value::SILENCE));
        nonPlayingModeComboBox.addItem(
                NonPlayingMode::getDisplayName(Value::PASSTHROUGH), static_cast<int>(Value::PASSTHROUGH));
        nonPlayingModeComboBox.addItem(
                NonPlayingMode::getDisplayName(Value::PATTERN), static_cast<int>(Value::PATTERN));
    }
    nonPlayingModeComboBox.setEditableText(false);
    nonPlayingModeComboBox.setTooltip(nonPlayingModeTooltip);
    nonPlayingModeComboBox.onChange = [this] {
        auto index = nonPlayingModeComboBox.getSelectedItemIndex();
        auto value = static_cast<NonPlayingMode::Value>(nonPlayingModeComboBox.getItemId(index));
        processor.setNonPlayingModeOverride(value);
    };

    nonPlayingModeLabel.setText("Non-playing mode", juce::NotificationType::dontSendNotification);
    nonPlayingModeLabel.setTooltip(nonPlayingModeTooltip);

    const juce::String maxChordSizeTooltip = "Sets the number of input notes taken into account by the arpeggiator. "
        "When set to 'Auto', the number of notes is derived from the actual number of input notes.";
    maxChordSizeSlider.setSliderStyle(juce::Slider::SliderStyle::IncDecButtons);
    maxChordSizeSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxLeft, false, 32, 24);
    maxChordSizeSlider.setTooltip(maxChordSizeTooltip);
    maxChordSizeSlider.setRange(0, 128, 1);
    maxChordSizeSlider.textFromValueFunction = [](auto value) {
        return (value == 0) ? juce::String("Auto") : juce::String(value);
    };
    // Force-updates the slider to say 'Auto' if initialized to zero
    maxChordSizeSlider.setValue(0.555, juce::NotificationType::dontSendNotification);
    maxChordSizeSlider.onValueChange = [this] {
        processor.setMaxChordSize(static_cast<int>(maxChordSizeSlider.getValue()));
    };

    maxChordSizeLabel.setText("Chord size", juce::NotificationType::dontSendNotification);
    maxChordSizeLabel.setTooltip(maxChordSizeTooltip);

    const juce::String extraNotesSelectionModeTooltip = "Sets the way notes should be selected when the Chord size "
        "is smaller than the actual number of input notes.";
    extraNotesSelectionModeComboBox.addItem("From bottom", static_cast<int>(LibreArp::ExtraNotesSelectionMode::FROM_BOTTOM) + 1);
    extraNotesSelectionModeComboBox.addItem("From top", static_cast<int>(LibreArp::ExtraNotesSelectionMode::FROM_TOP) + 1);
    extraNotesSelectionModeComboBox.setEditableText(false);
    extraNotesSelectionModeComboBox.setTooltip(extraNotesSelectionModeTooltip);
    extraNotesSelectionModeComboBox.onChange = [this] {
        auto index = extraNotesSelectionModeComboBox.getSelectedItemIndex();
        auto value = static_cast<LibreArp::ExtraNotesSelectionMode>(extraNotesSelectionModeComboBox.getItemId(index) - 1);
        processor.setExtraNotesSelectionMode(value);
    };

    extraNotesSelectionModeLabel.setText("Note selection mode", juce::NotificationType::dontSendNotification);
    extraNotesSelectionModeLabel.setTooltip(extraNotesSelectionModeTooltip);

    patternOffsetLabel.setText("Pattern offset", juce::NotificationType::dontSendNotification);

    recordingOffsetToggle.setButtonText("Record offset");
    recordingOffsetToggle.setTooltip("When selected, the next time playback "
            "starts, the offset of the pattern is set to the current playback "
            "position.");
    recordingOffsetToggle.setClickingTogglesState(true);
    recordingOffsetToggle.onStateChange = [this] {
        processor.setRecordingPatternOffset(recordingOffsetToggle.getToggleState());
    };
    recordingOffsetToggle.setColour(juce::TextButton::ColourIds::textColourOnId,
            juce::Colour(255, 0, 0));

    resetOffsetButton.setButtonText("Reset offset");
    resetOffsetButton.onClick = [this] {
        processor.resetPatternOffset();
    };

    addAndMakeVisible(midiInChannelLabel);
    addAndMakeVisible(midiInChannelSlider);
    addAndMakeVisible(midiOutChannelLabel);
    addAndMakeVisible(midiOutChannelSlider);
    addAndMakeVisible(octavesToggle);
    addAndMakeVisible(smartOctavesToggle);
    addAndMakeVisible(usingInputVelocityToggle);
    addAndMakeVisible(nonPlayingModeComboBox);
    addAndMakeVisible(nonPlayingModeLabel);
    addAndMakeVisible(maxChordSizeSlider);
    addAndMakeVisible(maxChordSizeLabel);
    addAndMakeVisible(extraNotesSelectionModeComboBox);
    addAndMakeVisible(extraNotesSelectionModeLabel);
    addAndMakeVisible(patternOffsetLabel);
    addAndMakeVisible(recordingOffsetToggle);
    addAndMakeVisible(resetOffsetButton);
}

void BehaviourSettingsEditor::resized() {
    updateLayout();
}

void BehaviourSettingsEditor::visibilityChanged() {
    Component::visibilityChanged();
    updateLayout();
}

void BehaviourSettingsEditor::audioUpdate() {
    if (isVisible()) {
        updateSettingsValues();
    }
}

void BehaviourSettingsEditor::updateSettingsValues() {
    midiInChannelSlider.setValue(processor.getInputMidiChannel(), juce::NotificationType::dontSendNotification);
    midiOutChannelSlider.setValue(processor.getOutputMidiChannel(), juce::NotificationType::dontSendNotification);
    octavesToggle.setToggleState(processor.isTransposingOctaves(), juce::NotificationType::dontSendNotification);
    smartOctavesToggle.setToggleState(processor.isUsingSmartOctaves(), juce::NotificationType::dontSendNotification);
    smartOctavesToggle.setEnabled(processor.isTransposingOctaves());
    usingInputVelocityToggle.setToggleState(processor.isUsingInputVelocity(), juce::NotificationType::dontSendNotification);
    nonPlayingModeComboBox.setSelectedId(static_cast<int>(processor.getNonPlayingModeOverride()));
    maxChordSizeSlider.setValue(processor.getMaxChordSize(), juce::NotificationType::dontSendNotification);
    extraNotesSelectionModeComboBox.setSelectedId(static_cast<int>(processor.getExtraNotesSelectionMode() + 1));
    recordingOffsetToggle.setToggleState(processor.getRecordingPatternOffset(), juce::NotificationType::dontSendNotification);
}

void BehaviourSettingsEditor::updateLayout() {
    if (!isVisible()) {
        return;
    }

    updateSettingsValues();

    auto area = getLocalBounds().reduced(8);

    auto midiInChannelArea = area.removeFromTop(24);
    midiInChannelSlider.updateText();
    midiInChannelSlider.setBounds(midiInChannelArea.removeFromLeft(96));
    midiInChannelLabel.setBounds(midiInChannelArea);

    area.removeFromTop(4);

    auto midiOutChannelArea = area.removeFromTop(24);
    midiOutChannelSlider.updateText();
    midiOutChannelSlider.setBounds(midiOutChannelArea.removeFromLeft(96));
    midiOutChannelLabel.setBounds(midiOutChannelArea);

    area.removeFromTop(8);

    octavesToggle.setBounds(area.removeFromTop(24));
    smartOctavesToggle.setBounds(area.removeFromTop(24));
    usingInputVelocityToggle.setBounds(area.removeFromTop(24));

    area.removeFromTop(4);

    auto nonPlayingModeArea = area.removeFromTop(24);
    nonPlayingModeComboBox.setBounds(nonPlayingModeArea.removeFromLeft(128));
    nonPlayingModeLabel.setBounds(nonPlayingModeArea);

    area.removeFromTop(8);

    auto maxChordSizeArea = area.removeFromTop(24);
    maxChordSizeSlider.setBounds(maxChordSizeArea.removeFromLeft(96));
    maxChordSizeLabel.setBounds(maxChordSizeArea);

    area.removeFromTop(4);

    auto extraNotesSelectionModeArea = area.removeFromTop(24);
    extraNotesSelectionModeComboBox.setBounds(extraNotesSelectionModeArea.removeFromLeft(128));
    extraNotesSelectionModeLabel.setBounds(extraNotesSelectionModeArea);

    area.removeFromTop(8);

    auto patternOffsetArea = area.removeFromTop(24);
    recordingOffsetToggle.setBounds(patternOffsetArea.removeFromLeft(100));
    resetOffsetButton.setBounds(patternOffsetArea.removeFromLeft(100));
    patternOffsetLabel.setBounds(patternOffsetArea);
}
