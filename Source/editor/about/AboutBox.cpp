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

AboutBox::AboutBox() {
    pluginNameLabel.setText(JucePlugin_Name, NotificationType::dontSendNotification);
    pluginNameLabel.setFont(Font(32));
    pluginNameLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(pluginNameLabel);

    pluginVersionLabel.setText(JucePlugin_VersionString, NotificationType::dontSendNotification);
    pluginVersionLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(pluginVersionLabel);

    auto gplFont = gplLabel.getFont();
    gplLabel.setText(LICENSE_NOTICE, NotificationType::dontSendNotification);
    gplLabel.setJustificationType(Justification::topLeft);
    addAndMakeVisible(gplLabel);

    websiteButton.setButtonText("Official website");
    websiteButton.setURL(URL(WEBSITE_URL));
    addAndMakeVisible(websiteButton);

    sourceButton.setButtonText("Source code repository");
    sourceButton.setURL(URL(SOURCE_URL));
    addAndMakeVisible(sourceButton);

    juceButton.setButtonText("JUCE 5 website");
    juceButton.setURL(URL(JUCE_WEBSITE_URL));
    addAndMakeVisible(juceButton);

    gplButton.setButtonText(LICENSE_NAME);
    gplButton.setURL(URL(LICENSE_URL));
    addAndMakeVisible(gplButton);
}

void AboutBox::resized() {
    auto area = getLocalBounds();

    pluginNameLabel.setBounds(area.removeFromTop(48));
    pluginVersionLabel.setBounds(area.removeFromTop(16));

    juceButton.setBounds(area.removeFromBottom(18));
    sourceButton.setBounds(area.removeFromBottom(18));
    websiteButton.setBounds(area.removeFromBottom(18));
    gplButton.setBounds(area.removeFromBottom(18));

    gplLabel.setBounds(area);
}
