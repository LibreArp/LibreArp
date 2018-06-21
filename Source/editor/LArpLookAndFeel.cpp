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

#include "LArpLookAndFeel.h"
#include "BinaryData.h"

const Colour LArpLookAndFeel::MAIN_BACKGROUND_COLOUR = Colour(42, 40, 34); // NOLINT
const Colour LArpLookAndFeel::HIGHLIGHT_BACKGROUND_COLOUR = Colour(59, 56, 48); // NOLINT
const Colour LArpLookAndFeel::MAIN_FOREGROUND_COLOUR = Colour(166, 164, 155); // NOLINT
const Colour LArpLookAndFeel::HIGHLIGHT_FOREGROUND_COLOUR = Colour(171, 204, 41); // NOLINT

const int MAIN_FONT_SIZE = 18;

LArpLookAndFeel::LArpLookAndFeel() {
    mainTypeface =
            Typeface::createSystemTypefaceFor(LArpBin::overpassregular_otf, LArpBin::overpassregular_otfSize);

    setDefaultSansSerifTypeface(mainTypeface);

    setColour(ResizableWindow::backgroundColourId, HIGHLIGHT_BACKGROUND_COLOUR);

    setColour(TabbedComponent::backgroundColourId, MAIN_BACKGROUND_COLOUR);
    setColour(TabbedComponent::outlineColourId, HIGHLIGHT_BACKGROUND_COLOUR);

    setColour(Label::textColourId, MAIN_FOREGROUND_COLOUR);

    setColour(TextButton::textColourOnId, MAIN_FOREGROUND_COLOUR);
    setColour(TextButton::textColourOffId, MAIN_FOREGROUND_COLOUR);
    setColour(TextButton::buttonColourId, MAIN_BACKGROUND_COLOUR);
    setColour(ComboBox::outlineColourId, MAIN_FOREGROUND_COLOUR);

    setColour(HyperlinkButton::textColourId, HIGHLIGHT_FOREGROUND_COLOUR);

    setColour(Slider::textBoxTextColourId, MAIN_FOREGROUND_COLOUR);
    setColour(Slider::textBoxOutlineColourId, MAIN_FOREGROUND_COLOUR);
    setColour(Slider::textBoxBackgroundColourId, MAIN_BACKGROUND_COLOUR);

    setColour(ScrollBar::thumbColourId, HIGHLIGHT_FOREGROUND_COLOUR);
    setColour(ScrollBar::trackColourId, MAIN_BACKGROUND_COLOUR);
}





void LArpLookAndFeel::drawTabButton(TabBarButton &button, Graphics &g, bool isMouseOver, bool isMouseDown) {
    const Rectangle<int> activeArea (button.getActiveArea());

    const TabbedButtonBar::Orientation o = button.getTabbedButtonBar().getOrientation();

    const Colour bkg (button.getTabBackgroundColour());

    if (button.getToggleState()) {
        g.setColour (bkg);
        g.fillRect (activeArea);
    }

    Colour col = button.isEnabled() ?
                 ((isMouseOver || isMouseDown) ?  MAIN_FOREGROUND_COLOUR.brighter() : MAIN_FOREGROUND_COLOUR) :
                 MAIN_FOREGROUND_COLOUR.withAlpha(0.3f);

    const Rectangle<float> area (button.getTextArea().toFloat());
    float length = area.getWidth();
    float depth  = area.getHeight();

    if (button.getTabbedButtonBar().isVertical())
        std::swap (length, depth);

    Font font (MAIN_FONT_SIZE);
    font.setUnderline (button.hasKeyboardFocus (false));

    AttributedString s;
    s.setJustification (Justification::centred);
    s.append (button.getButtonText().trim(), font, col);

    TextLayout textLayout;
    textLayout.createLayout (s, length);


    AffineTransform t;

    switch (o) {
        case TabbedButtonBar::TabsAtLeft:   t = t.rotated (MathConstants<float>::pi * -0.5f).translated (area.getX(), area.getBottom()); break;
        case TabbedButtonBar::TabsAtRight:  t = t.rotated (MathConstants<float>::pi *  0.5f).translated (area.getRight(), area.getY()); break;
        case TabbedButtonBar::TabsAtTop:
        case TabbedButtonBar::TabsAtBottom: t = t.translated (area.getX(), area.getY()); break;
        default:                            jassertfalse; break;
    }

    g.addTransform (t);

    textLayout.draw (g, Rectangle<float> (length, depth));
}



void LArpLookAndFeel::drawTabAreaBehindFrontButton(TabbedButtonBar &bar, Graphics &g, int w, int h) {}

void LArpLookAndFeel::drawButtonBackground(Graphics &g, Button &button, const Colour &backgroundColour,
                                           bool isMouseOverButton, bool isButtonDown) {
    auto cornerSize = 2.0f;
    auto bounds = button.getLocalBounds().toFloat().expanded(0.5f, 0.5f);

    auto baseColour = backgroundColour.withMultipliedSaturation (button.hasKeyboardFocus (true) ? 1.3f : 0.9f)
            .withMultipliedAlpha (button.isEnabled() ? 1.0f : 0.5f);

    if (isButtonDown || isMouseOverButton)
        baseColour = baseColour.contrasting (isButtonDown ? 0.2f : 0.05f);

    g.setColour (baseColour);

    auto margin = 3.0f;
    if (!button.isConnectedOnLeft()) {
        bounds.removeFromLeft(margin);
    }
    if (!button.isConnectedOnTop()) {
        bounds.removeFromTop(margin);
    }
    if (!button.isConnectedOnRight()) {
        bounds.removeFromRight(margin);
    }
    if (!button.isConnectedOnBottom()) {
        bounds.removeFromBottom(margin);
    }

    if (button.isConnectedOnLeft() || button.isConnectedOnRight()) {
        Path path;
        path.addRoundedRectangle (bounds.getX(), bounds.getY(),
                                  bounds.getWidth(), bounds.getHeight(),
                                  cornerSize, cornerSize,
                                  ! button.isConnectedOnLeft(),
                                  ! button.isConnectedOnRight(),
                                  ! button.isConnectedOnLeft(),
                                  ! button.isConnectedOnRight());

        g.fillPath (path);

        g.setColour (button.findColour (ComboBox::outlineColourId));
        g.strokePath (path, PathStrokeType (1.0f));

        if (button.isConnectedOnLeft()) {
            g.drawLine(bounds.getX() + 1, bounds.getY(), bounds.getX() + 1, bounds.getBottom());
        }
    }
    else {
        g.fillRoundedRectangle (bounds, cornerSize);

        g.setColour (button.findColour (ComboBox::outlineColourId));
        g.drawRoundedRectangle (bounds, cornerSize, 1.0f);
    }
}

int LArpLookAndFeel::getTabButtonBestWidth(TabBarButton &button, int tabDepth) {
    int width = Font (MAIN_FONT_SIZE + 4).getStringWidth (button.getButtonText().trim())
                + getTabButtonOverlap (MAIN_FONT_SIZE * 2) * 2;

    if (auto* extraComponent = button.getExtraComponent())
        width += button.getTabbedButtonBar().isVertical() ? extraComponent->getHeight()
                                                          : extraComponent->getWidth();

    return jlimit (tabDepth * 2, tabDepth * 8, width);
}

void LArpLookAndFeel::drawScrollbar(Graphics &g, ScrollBar &bar, int x, int y, int width, int height,
                                    bool isScrollbarVertical, int thumbStartPosition, int thumbSize, bool isMouseOver,
                                    bool isMouseDown) {
    g.setColour(findColour(ScrollBar::trackColourId));
    g.fillRect(bar.getLocalBounds());

    Rectangle<int> thumbBounds;

    if (isScrollbarVertical)
        thumbBounds = { x, thumbStartPosition, width, thumbSize };
    else
        thumbBounds = { thumbStartPosition, y, thumbSize, height };

    auto c = bar.findColour (ScrollBar::ColourIds::thumbColourId);
    g.setColour(isMouseOver ? c.brighter (0.25f) : c);
    g.fillRect(thumbBounds.reduced (1).toFloat());
}
