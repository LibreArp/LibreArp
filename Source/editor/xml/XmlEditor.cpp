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

#include "XmlEditor.h"
#include "../../exception/ArpIntegrityException.h"

const Colour RED = Colour(255, 0, 0);

XmlEditor::XmlEditor(LibreArp &p) : processor(p) {
    xmlEditor.setMultiLine(true, false);
    xmlEditor.setReturnKeyStartsNewLine(true);
    xmlEditor.setEnabled(false);
    audioUpdate(AudioUpdatable::PATTERN_UPDATE);

    addAndMakeVisible(xmlEditor);
}

void XmlEditor::resized() {
    xmlEditor.setBounds(getLocalBounds());
}

void XmlEditor::audioUpdate(uint32 type) {
    if (type == AudioUpdatable::PATTERN_UPDATE) {
        xmlEditor.setText(processor.getStateXml(), false);
    }
}
