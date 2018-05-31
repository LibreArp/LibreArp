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
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//

#pragma once

#include "JuceHeader.h"
#include "../../LibreArp.h"
#include "PatternEditor.h"
#include "BeatBar.h"


class PatternEditorView : public Component {
public:

    explicit PatternEditorView(LibreArp &p);

    void paint(Graphics &g) override;

    void resized() override;

    int getPixelsPerBeat();
    int getPixelsPerNote();
    void zoomPattern(float deltaX, float deltaY);

    int getRenderWidth();
    int getRenderHeight();

private:

    LibreArp &processor;

    Viewport mainComponentViewport;
    PatternEditor mainComponent;

    Viewport topBarViewport;
    BeatBar topBar;

    int pixelsPerBeat;
    int pixelsPerNote;
};


