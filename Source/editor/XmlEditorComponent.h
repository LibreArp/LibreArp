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
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//

#pragma once

#include "../LibreArp.h"
#include "JuceHeader.h"

class XmlEditorComponent : public Component {
public:

    explicit XmlEditorComponent(LibreArp &p);

    void resized() override;

private:
    LibreArp &processor;

    TextEditor xmlEditor;
    TextButton applyXmlButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (XmlEditorComponent);
};


