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
#include "../../LibreArp.h"
#include "PatternEditor.h"
#include "BeatBar.h"
#include "../../AudioUpdatable.h"


class PatternEditorView : public Component, public AudioUpdatable {
public:

    explicit PatternEditorView(LibreArp &p, EditorState &editorState);

    void paint(Graphics &g) override;

    void resized() override;

    void zoomPattern(float deltaX, float deltaY);

    int getRenderWidth();
    int getRenderHeight();

    void audioUpdate(uint32 type) override;

private:

    LibreArp &processor;
    EditorState &state;

    Slider snapSlider;
    Label snapSliderLabel;

    Slider loopResetSlider;
    Label loopResetSliderLabel;

    Viewport editorViewport;
    PatternEditor editor;

    Viewport beatBarViewport;
    BeatBar beatBar;
};


