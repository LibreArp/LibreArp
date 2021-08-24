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

#include "AboutBox.h"
#include "AboutBoxConfig.h"

const int LICENSE_NOTICE_HEIGHT_ADDITION = 32;

AboutBox::AboutBox() {

#if JUCE_DEBUG == 1
    nameAndVersionLabel.setText("LibreArp (debug)", juce::NotificationType::dontSendNotification);
#else
    nameAndVersionLabel.setText("LibreArp", juce::NotificationType::dontSendNotification);
#endif

    nameAndVersionLabel.setFont(juce::Font(48));
    nameAndVersionLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(nameAndVersionLabel);

    auto gplFont = juce::Font(16);
    licenseNotice.setText(LICENSE_NOTICE);
    licenseNotice.setFont(gplFont);

    gplLabel.setFont(gplFont);
    gplLabel.setText(licenseNotice.getText(), juce::NotificationType::dontSendNotification);
    gplLabel.setJustificationType(juce::Justification::topLeft);
    gplViewport.setViewedComponent(&gplLabel, false);
    gplViewport.setScrollBarsShown(true, false);
    addAndMakeVisible(gplViewport);

    addBottomLink(JucePlugin_Name " website", juce::URL(WEBSITE_URL));
    addBottomLink(JucePlugin_Name " source repository", juce::URL(SOURCE_URL));
    addBottomLink(JucePlugin_Name "'s chat room on Matrix", juce::URL(MATRIX_URL));
    addBottomLink(JucePlugin_Name " on Twitter", juce::URL(TWITTER_URL));
    addBottomLinkSeparator();
    addBottomLink("JUCE website", juce::URL(JUCE_WEBSITE_URL));
    addBottomLink("Overpass font website", juce::URL(FONT_WEBSITE_URL));
    addBottomLinkSeparator();
    addBottomLink("GNU General Public License v3", juce::URL(GPL_URL));
    addBottomLink("SIL Open Font License v1.1", juce::URL(FONT_LICENSE_URL));
}

void AboutBox::resized() {
    updateLayout();
}

void AboutBox::visibilityChanged() {
    Component::visibilityChanged();
    updateLayout();
}

void AboutBox::addBottomLink(juce::String text, juce::URL url) {
    std::shared_ptr<juce::HyperlinkButton> button(new juce::HyperlinkButton(text, url));
    addAndMakeVisible(*button);
    bottomLinks.push_front(button);
}

void AboutBox::addBottomLinkSeparator() {
    bottomLinks.push_front(std::shared_ptr<juce::HyperlinkButton>(nullptr));
}

void AboutBox::updateLayout() {
    if (!isVisible()) {
        return;
    }

    auto area = getLocalBounds();

    area.removeFromTop(8);
    nameAndVersionLabel.setBounds(area.removeFromTop(64));
    area.removeFromTop(8);

    for (auto &link : bottomLinks) {
        if (link == nullptr) {
            area.removeFromBottom(10);
        } else {
            link->setBounds(area.removeFromBottom(22));
        }
    }

    gplViewport.setBounds(area);
    juce::TextLayout layout;
    layout.createLayout(licenseNotice, gplLabel.getParentWidth());
    gplLabel.setSize(
            static_cast<int>(std::ceil(layout.getWidth())),
            static_cast<int>(std::ceil(layout.getHeight()) + LICENSE_NOTICE_HEIGHT_ADDITION));
}
