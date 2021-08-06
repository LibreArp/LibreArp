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
#include <LibreArpBinaryData.h>

const juce::Colour LArpLookAndFeel::MAIN_BACKGROUND_COLOUR = juce::Colour(42, 40, 34); // NOLINT
const juce::Colour LArpLookAndFeel::HIGHLIGHT_BACKGROUND_COLOUR = juce::Colour(59, 56, 48); // NOLINT
const juce::Colour LArpLookAndFeel::MAIN_FOREGROUND_COLOUR = juce::Colour(166, 164, 155); // NOLINT
const juce::Colour LArpLookAndFeel::HIGHLIGHT_FOREGROUND_COLOUR = juce::Colour(171, 204, 41); // NOLINT

const int MAIN_FONT_SIZE = 18;

LArpLookAndFeel::LArpLookAndFeel() {
    mainTypeface =
            juce::Typeface::createSystemTypefaceFor(LibreArpBin::overpassregular_otf, LibreArpBin::overpassregular_otfSize);

    setDefaultSansSerifTypeface(mainTypeface);

    setColour(juce::TooltipWindow::backgroundColourId, MAIN_BACKGROUND_COLOUR);
    setColour(juce::TooltipWindow::outlineColourId, MAIN_FOREGROUND_COLOUR);
    setColour(juce::TooltipWindow::textColourId, MAIN_FOREGROUND_COLOUR);

    setColour(juce::AlertWindow::outlineColourId, MAIN_FOREGROUND_COLOUR);
    setColour(juce::AlertWindow::backgroundColourId, MAIN_BACKGROUND_COLOUR);
    setColour(juce::AlertWindow::textColourId, MAIN_FOREGROUND_COLOUR);

    setColour(juce::TextEditor::backgroundColourId, HIGHLIGHT_BACKGROUND_COLOUR);
    setColour(juce::TextEditor::textColourId, MAIN_FOREGROUND_COLOUR);
    setColour(juce::TextEditor::highlightColourId, HIGHLIGHT_FOREGROUND_COLOUR);
    setColour(juce::TextEditor::highlightedTextColourId, juce::Colour(255, 255, 255));

    setColour(juce::ResizableWindow::backgroundColourId, HIGHLIGHT_BACKGROUND_COLOUR);

    setColour(juce::TabbedComponent::backgroundColourId, MAIN_BACKGROUND_COLOUR);
    setColour(juce::TabbedComponent::outlineColourId, HIGHLIGHT_BACKGROUND_COLOUR);

    setColour(juce::Label::textColourId, MAIN_FOREGROUND_COLOUR);
    setColour(juce::ToggleButton::textColourId, MAIN_FOREGROUND_COLOUR);

    setColour(juce::TextButton::textColourOnId, MAIN_FOREGROUND_COLOUR);
    setColour(juce::TextButton::textColourOffId, MAIN_FOREGROUND_COLOUR);
    setColour(juce::TextButton::buttonColourId, MAIN_BACKGROUND_COLOUR);
    setColour(juce::ComboBox::outlineColourId, MAIN_FOREGROUND_COLOUR);

    setColour(juce::HyperlinkButton::textColourId, HIGHLIGHT_FOREGROUND_COLOUR);

    setColour(juce::Slider::textBoxTextColourId, MAIN_FOREGROUND_COLOUR);
    setColour(juce::Slider::textBoxOutlineColourId, MAIN_FOREGROUND_COLOUR);
    setColour(juce::Slider::textBoxBackgroundColourId, MAIN_BACKGROUND_COLOUR);

    setColour(juce::ScrollBar::thumbColourId, HIGHLIGHT_FOREGROUND_COLOUR);
    setColour(juce::ScrollBar::trackColourId, MAIN_BACKGROUND_COLOUR);
}





void LArpLookAndFeel::drawTabButton(juce::TabBarButton &button, juce::Graphics &g, bool isMouseOver, bool isMouseDown) {
    const juce::Rectangle<int> activeArea (button.getActiveArea());

    const juce::TabbedButtonBar::Orientation o = button.getTabbedButtonBar().getOrientation();

    const juce::Colour bkg (button.getTabBackgroundColour());

    if (button.getToggleState()) {
        g.setColour (bkg);
        g.fillRect (activeArea);
    }

    juce::Colour col = button.isEnabled() ?
                 ((isMouseOver || isMouseDown) ?  MAIN_FOREGROUND_COLOUR.brighter() : MAIN_FOREGROUND_COLOUR) :
                 MAIN_FOREGROUND_COLOUR.withAlpha(0.3f);

    const juce::Rectangle<float> area (button.getTextArea().toFloat());
    float length = area.getWidth();
    float depth  = area.getHeight();

    if (button.getTabbedButtonBar().isVertical())
        std::swap (length, depth);

    juce::Font font (MAIN_FONT_SIZE);
    font.setUnderline (button.hasKeyboardFocus (false));

    juce::AttributedString s;
    s.setJustification (juce::Justification::centred);
    s.append (button.getButtonText().trim(), font, col);

    juce::TextLayout textLayout;
    textLayout.createLayout (s, length);


    juce::AffineTransform t;

    switch (o) {
        case juce::TabbedButtonBar::TabsAtLeft:   t = t.rotated (juce::MathConstants<float>::pi * -0.5f).translated (area.getX(), area.getBottom()); break;
        case juce::TabbedButtonBar::TabsAtRight:  t = t.rotated (juce::MathConstants<float>::pi *  0.5f).translated (area.getRight(), area.getY()); break;
        case juce::TabbedButtonBar::TabsAtTop:
        case juce::TabbedButtonBar::TabsAtBottom: t = t.translated (area.getX(), area.getY()); break;
        default:                            jassertfalse; break;
    }

    g.addTransform (t);

    textLayout.draw (g, juce::Rectangle<float> (length, depth));
}



void LArpLookAndFeel::drawTabAreaBehindFrontButton(juce::TabbedButtonBar &bar, juce::Graphics &g, int w, int h) {}

void LArpLookAndFeel::drawButtonBackground(juce::Graphics &g, juce::Button &button, const juce::Colour &backgroundColour,
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
        juce::Path path;
        path.addRoundedRectangle (bounds.getX(), bounds.getY(),
                                  bounds.getWidth(), bounds.getHeight(),
                                  cornerSize, cornerSize,
                                  ! button.isConnectedOnLeft(),
                                  ! button.isConnectedOnRight(),
                                  ! button.isConnectedOnLeft(),
                                  ! button.isConnectedOnRight());

        g.fillPath (path);

        g.setColour (button.findColour (juce::ComboBox::outlineColourId));
        g.strokePath (path, juce::PathStrokeType (1.0f));

        if (button.isConnectedOnLeft()) {
            g.fillRect(juce::roundToInt(bounds.getX()), juce::roundToInt(bounds.getY()), 1, juce::roundToInt(bounds.getHeight()));
        }
    }
    else {
        g.fillRoundedRectangle (bounds, cornerSize);

        g.setColour (button.findColour (juce::ComboBox::outlineColourId));
        g.drawRoundedRectangle (bounds, cornerSize, 1.0f);
    }
}

int LArpLookAndFeel::getTabButtonBestWidth(juce::TabBarButton &button, int tabDepth) {
    int width = juce::Font (MAIN_FONT_SIZE + 4).getStringWidth (button.getButtonText().trim())
                + getTabButtonOverlap (MAIN_FONT_SIZE * 2) * 2;

    if (auto* extraComponent = button.getExtraComponent())
        width += button.getTabbedButtonBar().isVertical() ? extraComponent->getHeight()
                                                          : extraComponent->getWidth();

    return juce::jlimit (tabDepth * 2, tabDepth * 8, width);
}

void LArpLookAndFeel::drawScrollbar(juce::Graphics &g, juce::ScrollBar &bar, int x, int y, int width, int height,
                                    bool isScrollbarVertical, int thumbStartPosition, int thumbSize, bool isMouseOver,
                                    bool isMouseDown) {
    g.setColour(findColour(juce::ScrollBar::trackColourId));
    g.fillRect(bar.getLocalBounds());

    juce::Rectangle<int> thumbBounds;

    if (isScrollbarVertical)
        thumbBounds = { x, thumbStartPosition, width, thumbSize };
    else
        thumbBounds = { thumbStartPosition, y, thumbSize, height };

    auto c = bar.findColour (juce::ScrollBar::ColourIds::thumbColourId);
    g.setColour(isMouseOver ? c.brighter (0.25f) : c);
    g.fillRect(thumbBounds.reduced (1).toFloat());
}

LArpLookAndFeel &LArpLookAndFeel::getInstance() {
    static LArpLookAndFeel instance;
    return instance;
}
