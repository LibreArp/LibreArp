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

#pragma once

#include <string>

/**
 * A class for handling update checks.
 */
namespace Updater {

    /**
     * Data structure containing information about an available update.
     */
    struct UpdateInfo {
        bool hasUpdate = false;
        int code = 0;
        std::string name = "";
        std::string websiteUrl = "";
    };

    /**
     * Retrieves info about LibreArp versions and returns information about a new version if found.
     *
     * @return information about an update
     */
    UpdateInfo checkForUpdates();

};


