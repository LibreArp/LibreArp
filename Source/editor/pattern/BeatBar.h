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

class PatternEditorView;

class BeatBar : public Component {
public:

    explicit BeatBar(LibreArp &p, EditorState &e, PatternEditorView *ec);

    void paint(Graphics &g) override;

    void mouseWheelMove(const MouseEvent &event, const MouseWheelDetails &wheel) override;

    void mouseDown(const MouseEvent& event) override;

private:

    LibreArp &processor;
    EditorState &state;
    PatternEditorView *view;
};


