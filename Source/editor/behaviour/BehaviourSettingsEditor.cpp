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

#include "../LArpLookAndFeel.h"
#include "BehaviourSettingsEditor.h"

BehaviourSettingsEditor::BehaviourSettingsEditor(LibreArp &p) : processor(p) {
    userTimeSigTitle.setText("Manual time signature", juce::NotificationType::dontSendNotification);

    userTimeSigToggle.setButtonText("Enable");
    userTimeSigToggle.setTooltip("Enables manual time signature setting instead of automatic fetch from the host");
    userTimeSigToggle.onStateChange = [this] {
        bool enabled = userTimeSigToggle.getToggleState();
        processor.setUserTimeSig(enabled);

        userTimeSigNumeratorSlider.setEnabled(enabled);
        userTimeSigSlashLabel.setEnabled(enabled);
        userTimeSigDenominatorSlider.setEnabled(enabled);

        this->updateLayout();
        this->repaint();
    };

    userTimeSigNumeratorSlider.setSliderStyle(juce::Slider::SliderStyle::IncDecButtons);
    userTimeSigNumeratorSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxRight, false, 24, 24);
    userTimeSigNumeratorSlider.setRange(1, 64, 1);
    userTimeSigNumeratorSlider.onValueChange = [this] {
        processor.setUserTimeSigNumerator(static_cast<int>(userTimeSigNumeratorSlider.getValue()));
    };

    userTimeSigSlashLabel.setText("/", juce::NotificationType::dontSendNotification);
    userTimeSigSlashLabel.setJustificationType(juce::Justification::centred);

    userTimeSigDenominatorSlider.setSliderStyle(juce::Slider::SliderStyle::IncDecButtons);
    userTimeSigDenominatorSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxLeft, false, 24, 24);
    userTimeSigDenominatorSlider.setRange(1, 64, 1);
    userTimeSigDenominatorSlider.onValueChange = [this] {
        processor.setUserTimeSigDenominator(static_cast<int>(userTimeSigDenominatorSlider.getValue()));
    };

    midiTitle.setText("MIDI", juce::NotificationType::dontSendNotification);

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

    noteBehaviourTitle.setText("Note behaviour", juce::NotificationType::dontSendNotification);

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

    chordTitle.setText("Chord", juce::NotificationType::dontSendNotification);

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

    patternOffsetTitle.setText("Pattern offset", juce::NotificationType::dontSendNotification);

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

    addAndMakeVisible(userTimeSigTitle);
    addAndMakeVisible(userTimeSigToggle);
    addAndMakeVisible(userTimeSigNumeratorSlider);
    addAndMakeVisible(userTimeSigSlashLabel);
    addAndMakeVisible(userTimeSigDenominatorSlider);
    addAndMakeVisible(midiTitle);
    addAndMakeVisible(midiInChannelLabel);
    addAndMakeVisible(midiInChannelSlider);
    addAndMakeVisible(midiOutChannelLabel);
    addAndMakeVisible(midiOutChannelSlider);
    addAndMakeVisible(noteBehaviourTitle);
    addAndMakeVisible(octavesToggle);
    addAndMakeVisible(smartOctavesToggle);
    addAndMakeVisible(usingInputVelocityToggle);
    addAndMakeVisible(nonPlayingModeComboBox);
    addAndMakeVisible(nonPlayingModeLabel);
    addAndMakeVisible(chordTitle);
    addAndMakeVisible(maxChordSizeSlider);
    addAndMakeVisible(maxChordSizeLabel);
    addAndMakeVisible(extraNotesSelectionModeComboBox);
    addAndMakeVisible(extraNotesSelectionModeLabel);
    addAndMakeVisible(patternOffsetTitle);
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
    userTimeSigToggle.setToggleState(processor.isUserTimeSig(), juce::NotificationType::dontSendNotification);
    userTimeSigNumeratorSlider.setValue(processor.getUserTimeSigNumerator());
    userTimeSigDenominatorSlider.setValue(processor.getUserTimeSigDenominator());
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

    bool userTimeSig = userTimeSigToggle.getToggleState();
    userTimeSigNumeratorSlider.setEnabled(userTimeSig);
    userTimeSigSlashLabel.setEnabled(userTimeSig);
    userTimeSigDenominatorSlider.setEnabled(userTimeSig);
}

void BehaviourSettingsEditor::updateLayout() {
    if (!isVisible()) {
        return;
    }

    updateSettingsValues();

    auto area = getLocalBounds().reduced(LArpLookAndFeel::MARGIN);


    //
    midiTitle.setBounds(area.removeFromTop(LArpLookAndFeel::COMPONENT_HEIGHT));
    area.removeFromTop(LArpLookAndFeel::COMPONENT_SEP);

    auto midiInChannelArea = area.removeFromTop(LArpLookAndFeel::COMPONENT_HEIGHT);
    midiInChannelSlider.updateText();
    midiInChannelSlider.setBounds(midiInChannelArea.removeFromLeft(96));
    midiInChannelLabel.setBounds(midiInChannelArea);

    area.removeFromTop(LArpLookAndFeel::COMPONENT_SEP);

    auto midiOutChannelArea = area.removeFromTop(LArpLookAndFeel::COMPONENT_HEIGHT);
    midiOutChannelSlider.updateText();
    midiOutChannelSlider.setBounds(midiOutChannelArea.removeFromLeft(96));
    midiOutChannelLabel.setBounds(midiOutChannelArea);


    //
    area.removeFromTop(LArpLookAndFeel::SECTION_SEP);
    noteBehaviourTitle.setBounds(area.removeFromTop(LArpLookAndFeel::COMPONENT_HEIGHT));
    area.removeFromTop(LArpLookAndFeel::COMPONENT_SEP);

    octavesToggle.setBounds(area.removeFromTop(LArpLookAndFeel::COMPONENT_HEIGHT));
    smartOctavesToggle.setBounds(area.removeFromTop(LArpLookAndFeel::COMPONENT_HEIGHT));
    usingInputVelocityToggle.setBounds(area.removeFromTop(LArpLookAndFeel::COMPONENT_HEIGHT));

    area.removeFromTop(LArpLookAndFeel::COMPONENT_SEP);

    auto nonPlayingModeArea = area.removeFromTop(LArpLookAndFeel::COMPONENT_HEIGHT);
    nonPlayingModeComboBox.setBounds(nonPlayingModeArea.removeFromLeft(128));
    nonPlayingModeLabel.setBounds(nonPlayingModeArea);


    //
    area.removeFromTop(LArpLookAndFeel::SECTION_SEP);
    chordTitle.setBounds(area.removeFromTop(LArpLookAndFeel::COMPONENT_HEIGHT));
    area.removeFromTop(LArpLookAndFeel::COMPONENT_SEP);

    auto maxChordSizeArea = area.removeFromTop(LArpLookAndFeel::COMPONENT_HEIGHT);
    maxChordSizeSlider.setBounds(maxChordSizeArea.removeFromLeft(96));
    maxChordSizeLabel.setBounds(maxChordSizeArea);

    area.removeFromTop(LArpLookAndFeel::COMPONENT_SEP);

    auto extraNotesSelectionModeArea = area.removeFromTop(LArpLookAndFeel::COMPONENT_HEIGHT);
    extraNotesSelectionModeComboBox.setBounds(extraNotesSelectionModeArea.removeFromLeft(128));
    extraNotesSelectionModeLabel.setBounds(extraNotesSelectionModeArea);


    //
    area.removeFromTop(LArpLookAndFeel::SECTION_SEP);
    patternOffsetTitle.setBounds(area.removeFromTop(LArpLookAndFeel::COMPONENT_HEIGHT));
    area.removeFromTop(LArpLookAndFeel::COMPONENT_SEP);

    auto patternOffsetArea = area.removeFromTop(LArpLookAndFeel::COMPONENT_HEIGHT);
    recordingOffsetToggle.setBounds(patternOffsetArea.removeFromLeft(100));
    resetOffsetButton.setBounds(patternOffsetArea.removeFromLeft(100));


    //
    area.removeFromTop(LArpLookAndFeel::SECTION_SEP);
    userTimeSigTitle.setBounds(area.removeFromTop(LArpLookAndFeel::COMPONENT_HEIGHT));
    area.removeFromTop(LArpLookAndFeel::COMPONENT_SEP);

    userTimeSigToggle.setBounds(area.removeFromTop(LArpLookAndFeel::COMPONENT_HEIGHT));

    area.removeFromTop(LArpLookAndFeel::COMPONENT_SEP);

    auto timeSigArea = area.removeFromTop(LArpLookAndFeel::COMPONENT_HEIGHT);
    userTimeSigNumeratorSlider.setBounds(timeSigArea.removeFromLeft(64));
    userTimeSigSlashLabel.setBounds(timeSigArea.removeFromLeft(18));
    userTimeSigDenominatorSlider.setBounds(timeSigArea.removeFromLeft(64));

}
