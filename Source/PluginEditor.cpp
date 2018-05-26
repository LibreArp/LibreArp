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
