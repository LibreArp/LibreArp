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

    addAndMakeVisible(midiInChannelLabel);
    addAndMakeVisible(midiInChannelSlider);
    addAndMakeVisible(midiOutChannelLabel);
    addAndMakeVisible(midiOutChannelSlider);
    addAndMakeVisible(octavesToggle);
    addAndMakeVisible(usingInputVelocityToggle);
    addAndMakeVisible(nonPlayingModeComboBox);
    addAndMakeVisible(nonPlayingModeLabel);
}

void BehaviourSettingsEditor::resized() {
    updateLayout();
}

void BehaviourSettingsEditor::visibilityChanged() {
    Component::visibilityChanged();
    updateLayout();
}

void BehaviourSettingsEditor::updateSettingsValues() {
    midiInChannelSlider.setValue(processor.getInputMidiChannel(), juce::NotificationType::dontSendNotification);
    midiOutChannelSlider.setValue(processor.getOutputMidiChannel(), juce::NotificationType::dontSendNotification);
    octavesToggle.setToggleState(processor.isTransposingOctaves(), juce::NotificationType::dontSendNotification);
    usingInputVelocityToggle.setToggleState(processor.isUsingInputVelocity(), juce::NotificationType::dontSendNotification);
    nonPlayingModeComboBox.setSelectedId(static_cast<int>(processor.getNonPlayingModeOverride()));
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

    usingInputVelocityToggle.setBounds(area.removeFromTop(24));

    area.removeFromTop(4);

    auto nonPlayingModeArea = area.removeFromTop(24);
    nonPlayingModeComboBox.setBounds(nonPlayingModeArea.removeFromLeft(128));
    nonPlayingModeLabel.setBounds(nonPlayingModeArea);
}
