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

#include "../../LibreArp.h"
#include "../../AudioUpdatable.h"

class XmlEditor : public juce::Component, public AudioUpdatable {
public:

    explicit XmlEditor(LibreArp &p);

    void resized() override;

    void audioUpdate(uint32_t type) override;

private:
    LibreArp &processor;

    juce::TextEditor xmlEditor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (XmlEditor)
};


