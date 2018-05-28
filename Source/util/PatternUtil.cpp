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

#include "PatternUtil.h"

ArpPattern PatternUtil::createBasicPattern() {
    ArpPattern pattern;

    ArpNote note;
    auto &notes = pattern.getNotes();

    note.data.noteNumber = 0;
    note.startPoint = 0;
    note.endPoint = 23;
    notes.push_back(note);

    note.data.noteNumber = 1;
    note.startPoint = 24;
    note.endPoint = 47;
    notes.push_back(note);

    note.data.noteNumber = 2;
    note.startPoint = 48;
    note.endPoint = 71;
    notes.push_back(note);

    pattern.loopLength = 72;

    return pattern;
}
