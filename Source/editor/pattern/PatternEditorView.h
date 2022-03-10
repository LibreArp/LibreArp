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
#include "PatternEditor.h"
#include "BeatBar.h"
#include "../../AudioUpdatable.h"


class PatternEditorView : public juce::Component, public AudioUpdatable {
public:

    explicit PatternEditorView(LibreArp &p, EditorState &editorState);

    void resized() override;
    void visibilityChanged() override;

    void zoomPattern(float deltaX, float deltaY);
    void scrollPattern(float deltaX, float deltaY);
    void resetPatternOffset();

    void audioUpdate() override;

private:

    LibreArp &processor;
    EditorState &state;

    juce::FileChooser presetChooser;

    juce::TextButton saveButton;
    juce::TextButton loadButton;
    juce::ToggleButton bypassToggle;

    juce::Slider snapSlider;
    juce::Label snapSliderLabel;

    juce::Slider loopResetSlider;
    juce::Label loopResetSliderLabel;

    juce::Slider swingSlider;
    juce::Label swingSliderLabel;

    PatternEditor editor;
    BeatBar beatBar;

    void updateParameterValues();
    void updateLayout();
};


