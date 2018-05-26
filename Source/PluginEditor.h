#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

/**
 * Main LibreArp editor component.
 */
class LibreArpAudioProcessorEditor : public AudioProcessorEditor {
public:

    explicit LibreArpAudioProcessorEditor(LibreArpAudioProcessor &);

    ~LibreArpAudioProcessorEditor() override;


    void paint(Graphics &) override;

    void resized() override;

private:
    /**
     * The underlying audio processor instance.
     */
    LibreArpAudioProcessor &processor;

    Font font;

    TextEditor xmlEditor;
    TextButton applyXmlButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LibreArpAudioProcessorEditor)
};
