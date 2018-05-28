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

#include <sstream>
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "ArpIntegrityException.h"

const Colour RED = Colour(255, 0, 0);

LibreArpAudioProcessorEditor::LibreArpAudioProcessorEditor(LibreArpAudioProcessor &p)
        : AudioProcessorEditor(&p), processor(p) {
    setSize(800, 600);

    font = Font("Noto Mono", 15.0f, Font::plain);

    xmlEditor.setFont(font);
    xmlEditor.setMultiLine(true, false);
    xmlEditor.setReturnKeyStartsNewLine(true);
    xmlEditor.setText(processor.getPatternXml(), false);

    applyXmlButton.setButtonText("Apply");

    addAndMakeVisible(xmlEditor, -1);
    addAndMakeVisible(applyXmlButton, -1);

    applyXmlButton.onClick = [this] {
        try {
            processor.parsePattern(xmlEditor.getText());
            xmlEditor.removeColour(TextEditor::outlineColourId);
        } catch (ArpIntegrityException &e) {
            xmlEditor.setColour(TextEditor::outlineColourId, RED);
        }
    };
}

LibreArpAudioProcessorEditor::~LibreArpAudioProcessorEditor() = default;

//==============================================================================
void LibreArpAudioProcessorEditor::paint(Graphics &g) {
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));

    g.setColour(Colours::white);
    g.setFont(font);
}

void LibreArpAudioProcessorEditor::resized() {
    xmlEditor.setBounds(0, 0, getWidth(), getHeight() - 30);
    applyXmlButton.setBounds(0, getHeight() - 30, getWidth(), 30);
}
