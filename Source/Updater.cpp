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

#include <juce_core/juce_core.h>

#include "Updater.h"
#include "BuildConfig.h"

Updater::UpdateInfo Updater::checkForUpdates() {
    auto updateUrl = juce::URL(BuildConfig::UPDATE_CHECK_URL);
    auto updateData = juce::JSON::parse(updateUrl.readEntireTextStream());
    if (!updateData.isArray()) {
        return UpdateInfo();
    }

    auto &updateArray = *updateData.getArray();

    auto result = UpdateInfo();

    for (const auto &updateVar : updateArray) {
        if (!updateVar.isObject()) {
            continue;
        }

        auto update = updateVar.getDynamicObject();
        auto codeVar = update->getProperty("code");
        auto nameVar = update->getProperty("name");
        auto urlVar = update->getProperty("url");

        if (!codeVar.isString() || !nameVar.isString() || !urlVar.isString()) {
            continue;
        }

        auto code = codeVar.toString().getHexValue32();
        if (code <= JucePlugin_VersionCode) {
            continue;
        }

        if (!result.hasUpdate || code > result.code) {
            result.hasUpdate = true;
            result.code = code;
            result.name = nameVar.toString().toStdString();
            result.websiteUrl = urlVar.toString().toStdString();
        }
    }

    return result;
}
