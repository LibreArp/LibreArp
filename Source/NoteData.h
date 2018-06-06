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

#include "../JuceLibraryCode/JuceHeader.h"

class NoteData {
public:
    static const Identifier TREEID_NOTE_DATA;
    static const Identifier TREEID_NOTE_NUMBER;
    static const Identifier TREEID_VELOCITY;
    static const Identifier TREEID_PAN;

    int noteNumber;
    double velocity;
    double pan;

    int lastNote = -1;

    NoteData();

    ValueTree toValueTree();

    static NoteData fromValueTree(ValueTree &tree);
};


