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

#include "SettingsEditor.h"

SettingsEditor::SettingsEditor(LibreArp& p) : processor(p) {
    updateCheckToggle.setButtonText("Check for updates automatically");
    updateCheckToggle.setTooltip("When this is enabled, the plugin will automatically check for updates when loaded, at most once a day.");
    updateCheckToggle.onStateChange = [this] {
        processor.getGlobals().setCheckForUpdatesEnabled(updateCheckToggle.getToggleState());
    };
    addAndMakeVisible(updateCheckToggle);

    const juce::String guiScaleFactorTooltip = "The scaling factor of LibreArp's editor.";
    guiScaleFactorSlider.setSliderStyle(juce::Slider::SliderStyle::IncDecButtons);
    guiScaleFactorSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 32, 24);
    guiScaleFactorSlider.setRange(1.0f, 3.0f, 0.25f);
    guiScaleFactorSlider.setTooltip(guiScaleFactorTooltip);
    guiScaleFactorSlider.onValueChange = [this] {
        auto value = static_cast<float>(guiScaleFactorSlider.getValue());
        processor.getGlobals().setGuiScaleFactor(value);
        processor.getActiveEditor()->setScaleFactor(value);
    };
    addAndMakeVisible(guiScaleFactorSlider);

    guiScaleFactorLabel.setText("GUI Scale", juce::NotificationType::dontSendNotification);
    guiScaleFactorLabel.setTooltip(guiScaleFactorTooltip);
    addAndMakeVisible(guiScaleFactorLabel);

    const juce::String nonPlayingModeTooltip = "Affects how the plugin behaves when the host is not playing.";
    {
        using namespace NonPlayingMode;
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
        processor.getGlobals().setNonPlayingMode(value);
    };
    addAndMakeVisible(nonPlayingModeComboBox);

    nonPlayingModeLabel.setText("Global non-playing mode", juce::NotificationType::dontSendNotification);
    nonPlayingModeLabel.setTooltip(nonPlayingModeTooltip);
    addAndMakeVisible(nonPlayingModeLabel);
}

void SettingsEditor::resized() {
    updateLayout();
}

void SettingsEditor::updateSettingsValues() {
    updateCheckToggle.setToggleState(processor.getGlobals().isCheckForUpdatesEnabled(), juce::NotificationType::dontSendNotification);
    guiScaleFactorSlider.setValue(processor.getGlobals().getGuiScaleFactor());
    nonPlayingModeComboBox.setSelectedId(static_cast<int>(processor.getGlobals().getNonPlayingMode()));
}

void SettingsEditor::visibilityChanged() {
    Component::visibilityChanged();
    updateLayout();
}

void SettingsEditor::updateLayout() {
    if (!isVisible()) {
        return;
    }

    updateSettingsValues();

    auto area = getLocalBounds().reduced(8);
    updateCheckToggle.setBounds(area.removeFromTop(24));

    area.removeFromTop(4);

    auto scaleFactorArea = area.removeFromTop(24);
    guiScaleFactorSlider.setBounds(scaleFactorArea.removeFromLeft(96));
    guiScaleFactorLabel.setBounds(scaleFactorArea);

    area.removeFromTop(4);

    auto nonPlayingModeArea = area.removeFromTop(24);
    nonPlayingModeComboBox.setBounds(nonPlayingModeArea.removeFromLeft(128));
    nonPlayingModeLabel.setBounds(nonPlayingModeArea);
}
