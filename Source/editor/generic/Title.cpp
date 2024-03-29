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

#include "Title.h"

Title::Title(const juce::String &componentName, const juce::String &labelText)
    : juce::Label(componentName, labelText) {
    setFont(juce::Font(18));
}

void Title::paint(juce::Graphics &g) {
    juce::Label::paint(g);
    g.setColour(findColour(juce::Label::textColourId));
    g.fillRect(getLocalBounds().removeFromBottom(1));
}
