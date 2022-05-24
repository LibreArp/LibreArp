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

#include <cstdint>
#include <cmath>
#include <type_traits>
#include <juce_core/juce_core.h>

/**
 * This class provides methods for converting mouse position to pulses and notes.
 *
 * Processor and state are retrieved using a template because we don't want to slow the plugin down by using virtual
 * methods when we can resolve everything compile-time.
 */
template <typename T>
class PulseConvertor {
protected:

    /**
     * Snaps the specified pulse to the grid.
     *
     * @param pulse the pulse
     * @param floor whether floor should be used instead of round
     *
     * @return the rounded pulse
     */
    int64_t snapPulse(int64_t pulse, bool floor = false) {
        if constexpr (std::is_same<decltype(((T*) this)->snapEnabled), bool>()) {
            if (!((T*) this)->snapEnabled) {
                return pulse;
            }
        }

        auto &pattern = ((T*) this)->processor.getPattern();
        auto timebase = pattern.getTimebase();
        double doubleDivisor = ((T*) this)->state.divisor;

        double base = (static_cast<double>(pulse) * doubleDivisor) / timebase;
        auto roundedBase = static_cast<int64_t>((floor) ? std::floor(base) : std::round(base));

        return roundedBase * (timebase / ((T*) this)->state.divisor);
    }

    /**
     * Converts a view-space X coordinate to a pulse position.
     *
     * @param x the view-space X coordinate
     * @param snap whether snap should be used
     * @param floor whether floor should be used instead of round for snapping
     *
     * @return the pulse position
     */
    int64_t xToPulse(int x, bool snap = true, bool floor = false) {
        auto &pattern = ((T*) this)->processor.getPattern();
        auto timebase = pattern.getTimebase();
        double pixelsPerBeat = ((T*) this)->state.displayPixelsPerBeat;

        auto pulse = static_cast<int64_t>(
                std::round(((x + ((T*) this)->state.displayOffsetX) / pixelsPerBeat) * timebase));

        return juce::jmax(static_cast<int64_t>(0), (snap) ? snapPulse(pulse, floor) : pulse);
    }

    /**
     * Converts a view-space Y coordinate to a note number.
     */
    int yToNote(int y) {
        double pixelsPerNote = ((T*) this)->state.displayPixelsPerNote;
        return static_cast<int>(std::ceil(((((T*) this)->getHeight() / 2.0) - (y + ((T*) this)->state.displayOffsetY)) / pixelsPerNote - 0.5));
    }

    /**
     * Converts a pulse position to a view-space X coordinate.
     */
    int pulseToX(int64_t pulse) {
        return pulseToAbsX(pulse) - static_cast<int>(((T*) this)->state.displayOffsetX);
    }

    /**
     * Converts a pulse position to absolute X coordinate (not offset by view offsets).
     */
    int pulseToAbsX(int64_t pulse) {
        auto &pattern = ((T*) this)->processor.getPattern();
        auto pixelsPerBeat = ((T*) this)->state.displayPixelsPerBeat;

        return juce::jmax(0, juce::roundToInt((static_cast<double>(pulse) / static_cast<double>(pattern.getTimebase())) * pixelsPerBeat) + 1);
    }

    /**
     * Converts a note number to a view-space Y coordinate.
     */
    int noteToY(int note) {
        return noteToAbsY(note) - static_cast<int>(((T*) this)->state.displayOffsetY);
    }

    /**
     * Converts a note number to absolute Y coordinate (not offset by view offsets).
     */
    int noteToAbsY(int note) {
        double pixelsPerNote = ((T*) this)->state.displayPixelsPerNote;
        return juce::roundToInt(std::floor((((T*) this)->getHeight() / 2.0) - (note + 0.5) * pixelsPerNote)) + 1;
    }

};
