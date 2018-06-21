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


class LArpLookAndFeel : public LookAndFeel_V4 {
public:

    static const Colour MAIN_BACKGROUND_COLOUR;
    static const Colour HIGHLIGHT_BACKGROUND_COLOUR;

    static const Colour MAIN_FOREGROUND_COLOUR;
    static const Colour HIGHLIGHT_FOREGROUND_COLOUR;

    explicit LArpLookAndFeel();

    void drawTabButton(TabBarButton &button, Graphics &graphics, bool isMouseOver, bool isMouseDown) override;

    void drawTabAreaBehindFrontButton(TabbedButtonBar &bar, Graphics &g, int w, int h) override;

    int getTabButtonBestWidth(TabBarButton &button, int tabDepth) override;

    void
    drawButtonBackground(Graphics &graphics, Button &button, const Colour &backgroundColour, bool isMouseOverButton,
                         bool isButtonDown) override;

    void
    drawScrollbar(Graphics &g, ScrollBar &bar, int x, int y, int width, int height, bool isScrollbarVertical,
                  int thumbStartPosition, int thumbSize, bool isMouseOver, bool isMouseDown) override;

private:

    Typeface::Ptr mainTypeface;

};


