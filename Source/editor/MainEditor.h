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

#include "../LibreArp.h"
#include "xml/XmlEditor.h"
#include "pattern/PatternEditor.h"
#include "pattern/PatternEditorView.h"
#include "settings/SettingsEditor.h"
#include "about/AboutBox.h"
#include "LArpLookAndFeel.h"
#include "../AudioUpdatable.h"
#include "behaviour/BehaviourSettingsEditor.h"

/**
 * Main LibreArp editor component.
 */
class MainEditor : public juce::AudioProcessorEditor, public AudioUpdatable {
public:

    explicit MainEditor(LibreArp &, EditorState &);

    ~MainEditor() override;


    void paint(juce::Graphics &) override;
    void resized() override;
    void audioUpdate(uint32_t type) override;
    void visibilityChanged() override;

private:
    LibreArp &processor;
    EditorState &state;

    juce::TooltipWindow tooltipWindow;

    juce::TabbedComponent tabs;

    juce::Label placeholderLabel;

    PatternEditorView patternEditor;
    BehaviourSettingsEditor behaviourSettingsEditor;
    SettingsEditor settingsEditor;
    XmlEditor xmlEditor;
    AboutBox aboutBox;

    juce::HyperlinkButton updateButton;

    void handleUpdateCheck();
    void updateUpdateButton();
    void updateLayout();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainEditor)
};
