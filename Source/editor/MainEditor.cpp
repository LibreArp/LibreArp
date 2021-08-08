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

#include <sstream>
#include "../LibreArp.h"
#include "MainEditor.h"


MainEditor::MainEditor(LibreArp &p, EditorState &e)
        : AudioProcessorEditor(&p),
          processor(p),
          state(e),
          tabs(juce::TabbedButtonBar::Orientation::TabsAtTop),
          patternEditor(p, e),
          behaviourSettingsEditor(p),
          settingsEditor(p) {

    juce::LookAndFeel::setDefaultLookAndFeel(&LArpLookAndFeel::getInstance());

    setSize(state.width, state.height);
    setResizable(true, false);

    placeholderLabel.setText("Unimplemented component", juce::NotificationType::dontSendNotification);
    placeholderLabel.setJustificationType(juce::Justification::centred);
    placeholderLabel.setFont(juce::Font(32.0f));
    placeholderLabel.setColour(juce::Label::textColourId, juce::Colour(255, 0, 0));

    tabs.setOutline(0);
    tabs.addTab("Pattern Editor",
            getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId), &patternEditor, false);
    tabs.addTab("Behaviour",
            getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId), &behaviourSettingsEditor, false);
    tabs.addTab("Global settings",
            getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId), &settingsEditor, false);
    tabs.addTab("About",
            getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId), &aboutBox, false);

    updateButton.setJustificationType(juce::Justification::centredRight);

    addAndMakeVisible(tabs);
    addChildComponent(updateButton, 9999);
}

MainEditor::~MainEditor() = default;

//==============================================================================
void MainEditor::paint(juce::Graphics &g) {
    g.setColour(LArpLookAndFeel::MAIN_BACKGROUND_COLOUR);
    g.fillRect(getLocalBounds());
}

void MainEditor::visibilityChanged() {
    Component::visibilityChanged();

    if (!isVisible()) {
        processor.getGlobals().save();
        return;
    }

    processor.getGlobals().load();
    handleUpdateCheck();
    updateUpdateButton();
    updateLayout();
}

void MainEditor::resized() {
    updateLayout();
}

void MainEditor::handleAsyncUpdate() {
    patternEditor.audioUpdate();
}

void MainEditor::handleUpdateCheck() {
    auto &globals = processor.getGlobals();

    if (globals.isCheckForUpdatesEnabled()) {
        auto minMsBeforeUpdateCheck = globals.getMinSecsBeforeUpdateCheck() * 1000L;
        auto lastUpdateCheckTime = globals.getLastUpdateCheckTime();
        auto currentTime = juce::Time::currentTimeMillis();

        if ((currentTime - lastUpdateCheckTime) >= minMsBeforeUpdateCheck || globals.isFoundUpdateOnLastCheck()) {
            globals.setLastUpdateCheckTime(currentTime);
            auto info = Updater::checkForUpdates();

            if (info.hasUpdate) {
                globals.setFoundUpdateOnLastCheck(true);
                processor.setLastUpdateInfo(info);
            } else {
                globals.setFoundUpdateOnLastCheck(false);
            }
        }
    }
}

void MainEditor::updateUpdateButton() {
    auto &info = processor.getLastUpdateInfo();

    if (!info.hasUpdate) {
        updateButton.setVisible(false);
        return;
    }

    std::stringstream infostr;
    infostr << "An update to " << info.name << " is available!";
    updateButton.setButtonText(infostr.str());
    updateButton.setURL(juce::URL(info.websiteUrl));
    updateButton.setVisible(true);
}

void MainEditor::updateLayout() {
    if (!isVisible()) {
        return;
    }

    state.width = getWidth();
    state.height = getHeight();

    tabs.setBounds(getLocalBounds().reduced(8));

    updateUpdateButton();
    auto updateButtonArea = getLocalBounds().reduced(8);
    updateButton.setBounds(updateButtonArea
    .removeFromTop(24)
    .removeFromRight(256));
}
