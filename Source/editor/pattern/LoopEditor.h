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

#include <type_traits>
#include <mutex>
#include <juce_gui_basics/juce_gui_basics.h>

/**
 * This class provides methods for editing of the loop region.
 *
 * Processor and state are retrieved using a template because we don't want to slow the plugin down by using virtual
 * methods when we can resolve everything compile-time.
 */
template <typename T>
class LoopEditor {
protected:

    /**
     * Mouse loop end resize.
     */
    void loopStartResize(const juce::MouseEvent &event) {
        std::scoped_lock lock(((T*) this)->processor.getPattern().getMutex());

        auto &pattern = ((T*) this)->processor.getPattern();
        pattern.loopStart = juce::jmin(pattern.loopEnd, juce::jmax(int64_t(0), ((T*) this)->xToPulse(event.x)));
        ((T*) this)->processor.buildPattern();
        ((T*) this)->view.repaint();
        ((T*) this)->mouseCursor = juce::MouseCursor::LeftRightResizeCursor;
    }

    /**
     * Mouse loop end resize.
     */
    void loopEndResize(const juce::MouseEvent &event) {
        std::scoped_lock lock(((T*) this)->processor.getPattern().getMutex());

        auto &pattern = ((T*) this)->processor.getPattern();
        pattern.loopEnd = juce::jmax(pattern.loopStart, ((T*) this)->xToPulse(event.x));
        ((T*) this)->processor.buildPattern();
        ((T*) this)->view.repaint();
        ((T*) this)->mouseCursor = juce::MouseCursor::LeftRightResizeCursor;
    }

    /**
     * Mouse loop move.
     */
    void loopMove(const juce::MouseEvent &event) {
        std::scoped_lock lock(((T*) this)->processor.getPattern().getMutex());

        auto &pattern = ((T*) this)->processor.getPattern();
        pattern.loopStart = juce::jmax(((T*) this)->xToPulse(event.x) - ((T*) this)->dragAction.startOffset, int64_t(0));
        pattern.loopEnd = pattern.loopStart + ((T*) this)->dragAction.loopLength;

        ((T*) this)->processor.buildPattern();
        ((T*) this)->view.repaint();
        ((T*) this)->mouseCursor = juce::MouseCursor::DraggingHandCursor;
    }

};
