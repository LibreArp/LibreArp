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

#include "JuceHeader.h"
#include "NoteData.h"

class ArpBuiltEvents {
public:

    class Event {
    public:
        int64 time;
        std::vector<unsigned long> ons;
        std::vector<unsigned long> offs;
    };

    std::vector<Event> events;
    std::vector<NoteData> data;

    int timebase;
    int64 loopLength;
};


