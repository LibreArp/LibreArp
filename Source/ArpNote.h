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


#include "../JuceLibraryCode/JuceHeader.h"
#include "NoteData.h"

class ArpNote {
public:
    static const Identifier TREEID_NOTE;
    static const Identifier TREEID_START_POINT;
    static const Identifier TREEID_END_POINT;

    explicit ArpNote(NoteData data = NoteData());

    NoteData data;
    int64 startPoint;
    int64 endPoint;

    ValueTree toValueTree();

    static ArpNote fromValueTree(ValueTree &tree);
};


