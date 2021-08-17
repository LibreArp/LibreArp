#pragma once

namespace Style
{
    const juce::Colour BAR_BACKGROUND_COLOUR = juce::Colour(42, 40, 34);
    const juce::Colour BOTTOM_LINE_COLOUR = juce::Colour(0, 0, 0);
    const juce::Colour BEAT_LINE_COLOUR = juce::Colour(107, 104, 94);
    const juce::Colour BEAT_NUMBER_COLOUR = BEAT_LINE_COLOUR;
    const juce::Colour LOOP_LINE_COLOUR = juce::Colour(155, 36, 36);
    const juce::Colour LOOP_TEXT_COLOUR = juce::Colour((uint8_t) 155, 36, 36);

    const juce::Colour EDITOR_BACKGROUND_COLOUR = juce::Colour(82, 78, 67);
    const juce::Colour GRIDLINES_COLOUR = BAR_BACKGROUND_COLOUR;
    const juce::Colour POSITION_INDICATOR_COLOUR = juce::Colour(255, 255, 255);

    const juce::Colour ZERO_LINE_COLOUR = juce::Colour((uint8_t) 0, 0, 0, 0.1f);
    const juce::Colour ZERO_OCTAVE_COLOUR = juce::Colour((uint8_t) 171, 204, 41, 0.1f);
    const juce::Colour OCTAVE_LINE_COLOUR = juce::Colour((uint8_t) 0, 0, 0, 1.0f);

    const juce::Colour BAR_SHADE_COLOUR = ZERO_LINE_COLOUR;

    const juce::Colour NOTE_FILL_COLOUR = juce::Colour(171, 204, 41);
    const juce::Colour NOTE_ACTIVE_FILL_COLOUR = juce::Colour(228, 255, 122);
    const juce::Colour NOTE_SELECTED_FILL_COLOUR = juce::Colour(245, 255, 209);
    const juce::Colour NOTE_SELECTED_ACTIVE_FILL_COLOUR = juce::Colour(255, 255, 255);
    const juce::Colour NOTE_BORDER_COLOUR = juce::Colour((uint8_t) 0, 0, 0, 0.7f);
    const juce::Colour NOTE_VELOCITY_COLOUR = juce::Colour((uint8_t) 0, 0, 0, 0.2f);

    const juce::Colour CURSOR_TIME_COLOUR = juce::Colour((uint8_t) 255, 255, 255, 0.7f);
    const juce::Colour CURSOR_NOTE_COLOUR = juce::Colour((uint8_t) 255, 255, 255, 0.05f);

    const juce::Colour SELECTION_BORDER_COLOUR = juce::Colour(255, 0, 0);

    const juce::Colour MAIN_BACKGROUND_COLOUR = juce::Colour(42, 40, 34);
    const juce::Colour HIGHLIGHT_BACKGROUND_COLOUR = juce::Colour(59, 56, 48);
    const juce::Colour MAIN_FOREGROUND_COLOUR = juce::Colour(166, 164, 155);
    const juce::Colour HIGHLIGHT_FOREGROUND_COLOUR = juce::Colour(171, 204, 41);
}