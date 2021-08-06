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
    midiInChannelLabel.setText("MIDI Input Channel (do not change while playing)", juce::NotificationType::dontSendNotification);

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

    addAndMakeVisible(midiInChannelLabel);
    addAndMakeVisible(midiInChannelSlider);
    addAndMakeVisible(midiOutChannelLabel);
    addAndMakeVisible(midiOutChannelSlider);
    addAndMakeVisible(octavesToggle);
    addAndMakeVisible(usingInputVelocityToggle);
}

void BehaviourSettingsEditor::resized() {
    auto area = getLocalBounds().reduced(8);

    auto midiInChannelArea = area.removeFromTop(24);
    midiInChannelSlider.setValue(processor.getInputMidiChannel(), juce::NotificationType::dontSendNotification);
    midiInChannelSlider.updateText();
    midiInChannelSlider.setBounds(midiInChannelArea.removeFromLeft(96));
    midiInChannelLabel.setBounds(midiInChannelArea);

    area.removeFromTop(4);

    auto midiOutChannelArea = area.removeFromTop(24);
    midiOutChannelSlider.setValue(processor.getOutputMidiChannel(), juce::NotificationType::dontSendNotification);
    midiOutChannelSlider.updateText();
    midiOutChannelSlider.setBounds(midiOutChannelArea.removeFromLeft(96));
    midiOutChannelLabel.setBounds(midiOutChannelArea);

    area.removeFromTop(8);

    octavesToggle.setToggleState(processor.isTransposingOctaves(), juce::NotificationType::dontSendNotification);
    octavesToggle.setBounds(area.removeFromTop(24));

    usingInputVelocityToggle.setToggleState(processor.isUsingInputVelocity(), juce::NotificationType::dontSendNotification);
    usingInputVelocityToggle.setBounds(area.removeFromTop(24));

}

BehaviourSettingsEditor::~BehaviourSettingsEditor() = default;
