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
    nameAndVersionLabel.setText(JucePlugin_Name " (debug version)", NotificationType::dontSendNotification);
#else
    nameAndVersionLabel.setText(JucePlugin_Name " " JucePlugin_VersionString, NotificationType::dontSendNotification);
#endif

    nameAndVersionLabel.setFont(Font(40));
    nameAndVersionLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(nameAndVersionLabel);

    auto gplFont = Font(16);
    licenseNotice.setText(LICENSE_NOTICE);
    licenseNotice.setFont(gplFont);

    gplLabel.setFont(gplFont);
    gplLabel.setText(licenseNotice.getText(), NotificationType::dontSendNotification);
    gplLabel.setJustificationType(Justification::topLeft);
    gplViewport.setViewedComponent(&gplLabel, false);
    gplViewport.setScrollBarsShown(true, false);
    addAndMakeVisible(gplViewport);

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

    nameAndVersionLabel.setBounds(area.removeFromTop(64));

    juceButton.setBounds(area.removeFromBottom(22));
    sourceButton.setBounds(area.removeFromBottom(22));
    websiteButton.setBounds(area.removeFromBottom(22));
    gplButton.setBounds(area.removeFromBottom(22));

    gplViewport.setBounds(area);
    TextLayout layout;
    layout.createLayout(licenseNotice, gplLabel.getParentWidth());
    gplLabel.setSize(
            static_cast<int>(std::ceil(layout.getWidth())),
            static_cast<int>(std::ceil(layout.getHeight()) + LICENSE_NOTICE_HEIGHT_ADDITION));
}
