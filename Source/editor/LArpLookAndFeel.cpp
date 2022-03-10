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
#include "style/Colours.h"

const int MAIN_FONT_SIZE = 18;

LArpLookAndFeel::LArpLookAndFeel() {
    mainTypeface =
            juce::Typeface::createSystemTypefaceFor(LibreArpBin::overpassregular_otf, LibreArpBin::overpassregular_otfSize);

    setDefaultSansSerifTypeface(mainTypeface);

    setColour(juce::ResizableWindow::backgroundColourId, Style::MAIN_BACKGROUND_COLOUR);

    setColour(juce::TooltipWindow::backgroundColourId, Style::MAIN_BACKGROUND_COLOUR);
    setColour(juce::TooltipWindow::outlineColourId, Style::MAIN_FOREGROUND_COLOUR);
    setColour(juce::TooltipWindow::textColourId, Style::MAIN_FOREGROUND_COLOUR);

    setColour(juce::AlertWindow::outlineColourId, Style::MAIN_FOREGROUND_COLOUR);
    setColour(juce::AlertWindow::backgroundColourId, Style::MAIN_BACKGROUND_COLOUR);
    setColour(juce::AlertWindow::textColourId, Style::MAIN_FOREGROUND_COLOUR);

    setColour(juce::TextEditor::backgroundColourId, Style::HIGHLIGHT_BACKGROUND_COLOUR);
    setColour(juce::TextEditor::textColourId, Style::MAIN_FOREGROUND_COLOUR);
    setColour(juce::TextEditor::highlightColourId, Style::HIGHLIGHT_FOREGROUND_COLOUR);
    setColour(juce::TextEditor::highlightedTextColourId, Style::HIGHLIGHT_TEXT_COLOUR);

    setColour(juce::ResizableWindow::backgroundColourId, Style::HIGHLIGHT_BACKGROUND_COLOUR);

    setColour(juce::TabbedComponent::backgroundColourId, Style::MAIN_BACKGROUND_COLOUR);
    setColour(juce::TabbedComponent::outlineColourId, Style::HIGHLIGHT_BACKGROUND_COLOUR);

    setColour(juce::Label::textColourId, Style::MAIN_FOREGROUND_COLOUR);
    setColour(juce::ToggleButton::textColourId, Style::MAIN_FOREGROUND_COLOUR);

    setColour(juce::TextButton::textColourOnId, Style::MAIN_FOREGROUND_COLOUR);
    setColour(juce::TextButton::textColourOffId, Style::MAIN_FOREGROUND_COLOUR);
    setColour(juce::TextButton::buttonColourId, Style::MAIN_BACKGROUND_COLOUR);
    setColour(juce::ComboBox::outlineColourId, Style::MAIN_FOREGROUND_COLOUR);

    setColour(juce::HyperlinkButton::textColourId, Style::HIGHLIGHT_FOREGROUND_COLOUR);

    setColour(juce::Slider::backgroundColourId, Style::MAIN_BACKGROUND_COLOUR);
    setColour(juce::Slider::textBoxTextColourId, Style::MAIN_FOREGROUND_COLOUR);
    setColour(juce::Slider::textBoxOutlineColourId, Style::MAIN_FOREGROUND_COLOUR);
    setColour(juce::Slider::textBoxBackgroundColourId, Style::MAIN_BACKGROUND_COLOUR);
    setColour(juce::Slider::trackColourId, Style::MAIN_FOREGROUND_COLOUR);
    setColour(juce::Slider::thumbColourId, Style::HIGHLIGHT_FOREGROUND_COLOUR);

    setColour(juce::ComboBox::textColourId, Style::MAIN_FOREGROUND_COLOUR);
    setColour(juce::ComboBox::outlineColourId, Style::MAIN_FOREGROUND_COLOUR);
    setColour(juce::ComboBox::focusedOutlineColourId, Style::MAIN_FOREGROUND_COLOUR);
    setColour(juce::ComboBox::arrowColourId, Style::MAIN_FOREGROUND_COLOUR);
    setColour(juce::ComboBox::buttonColourId, Style::MAIN_BACKGROUND_COLOUR);
    setColour(juce::ComboBox::backgroundColourId, Style::MAIN_BACKGROUND_COLOUR);

    setColour(juce::PopupMenu::headerTextColourId, Style::MAIN_FOREGROUND_COLOUR);
    setColour(juce::PopupMenu::textColourId, Style::MAIN_FOREGROUND_COLOUR);
    setColour(juce::PopupMenu::highlightedTextColourId, Style::HIGHLIGHT_TEXT_COLOUR);
    setColour(juce::PopupMenu::backgroundColourId, Style::MAIN_BACKGROUND_COLOUR);
    setColour(juce::PopupMenu::highlightedBackgroundColourId, Style::HIGHLIGHT_BACKGROUND_COLOUR);

    setColour(juce::ScrollBar::thumbColourId, Style::HIGHLIGHT_FOREGROUND_COLOUR);
    setColour(juce::ScrollBar::trackColourId, Style::MAIN_BACKGROUND_COLOUR);
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
                 ((isMouseOver || isMouseDown) ?  Style::MAIN_FOREGROUND_COLOUR.brighter() : Style::MAIN_FOREGROUND_COLOUR) :
                 Style::MAIN_FOREGROUND_COLOUR.withAlpha(0.3f);

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



void LArpLookAndFeel::drawTabAreaBehindFrontButton(juce::TabbedButtonBar &bar, juce::Graphics &g, int w, int h) {
    juce::ignoreUnused(bar, g, w, h);
}

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
    juce::ignoreUnused(isMouseDown);

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
