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

#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "../../LibreArp.h"

class BehaviourSettingsEditor : public juce::Component, public AudioUpdatable {
public:

    explicit BehaviourSettingsEditor(LibreArp &p);

    void resized() override;
    void visibilityChanged() override;

    void audioUpdate() override;

private:

    LibreArp &processor;

    juce::ToggleButton octavesToggle;
    juce::ToggleButton smartOctavesToggle;
    juce::ToggleButton usingInputVelocityToggle;

    juce::Slider midiInChannelSlider;
    juce::Label midiInChannelLabel;

    juce::Slider midiOutChannelSlider;
    juce::Label midiOutChannelLabel;

    juce::ComboBox nonPlayingModeComboBox;
    juce::Label nonPlayingModeLabel;

    juce::Slider maxChordSizeSlider;
    juce::Label maxChordSizeLabel;

    juce::ComboBox extraNotesSelectionModeComboBox;
    juce::Label extraNotesSelectionModeLabel;

    void updateSettingsValues();
    void updateLayout();

};


