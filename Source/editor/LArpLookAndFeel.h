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


class LArpLookAndFeel : public juce::LookAndFeel_V4 {
public:

    static constexpr int MARGIN = 8;
    static constexpr int SECTION_SEP = 16;
    static constexpr int COMPONENT_HEIGHT = 24;
    static constexpr int COMPONENT_SEP = 4;

    void drawTabButton(juce::TabBarButton &button, juce::Graphics &graphics, bool isMouseOver, bool isMouseDown) override;

    void drawTabAreaBehindFrontButton(juce::TabbedButtonBar &bar, juce::Graphics &g, int w, int h) override;

    int getTabButtonBestWidth(juce::TabBarButton &button, int tabDepth) override;

    void
    drawButtonBackground(juce::Graphics &graphics, juce::Button &button, const juce::Colour &backgroundColour, bool isMouseOverButton,
                         bool isButtonDown) override;

    void
    drawScrollbar(juce::Graphics &g, juce::ScrollBar &bar, int x, int y, int width, int height, bool isScrollbarVertical,
                  int thumbStartPosition, int thumbSize, bool isMouseOver, bool isMouseDown) override;

    static LArpLookAndFeel &getInstance();

private:

    explicit LArpLookAndFeel();
    juce::Typeface::Ptr mainTypeface;

};


