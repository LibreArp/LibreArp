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

#include "JuceHeader.h"
#include "../LibreArp.h"
#include "xml/XmlEditor.h"
#include "pattern/PatternEditor.h"
#include "pattern/PatternEditorView.h"
#include "about/AboutBox.h"
#include "LArpLookAndFeel.h"

/**
 * Main LibreArp editor component.
 */
class MainEditor : public AudioProcessorEditor {
public:

    explicit MainEditor(LibreArp &, EditorState &);

    ~MainEditor() override;


    void paint(Graphics &) override;

    void resized() override;

private:
    LArpLookAndFeel lookAndFeel;

    LibreArp &processor;
    EditorState &state;

    ResizableCornerComponent resizer;
    ComponentBoundsConstrainer boundsConstrainer;
    TabbedComponent tabs;

    PatternEditorView patternEditor;
    XmlEditor xmlEditor;
    AboutBox aboutBox;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainEditor);
};
