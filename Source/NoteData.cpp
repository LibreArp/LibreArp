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

#include "NoteData.h"

const Identifier NoteData::TREEID_NOTE_DATA = Identifier("noteData"); // NOLINT
const Identifier NoteData::TREEID_NOTE_NUMBER = Identifier("noteNumber"); // NOLINT
const Identifier NoteData::TREEID_VELOCITY = Identifier("velocity"); // NOLINT
const Identifier NoteData::TREEID_PAN = Identifier("pan"); // NOLINT

NoteData::NoteData() {
    noteNumber = 0;
    velocity = 0.8;
    pan = 0;
}


ValueTree NoteData::toValueTree() {
    ValueTree result = ValueTree(TREEID_NOTE_DATA);
    result.setProperty(TREEID_NOTE_NUMBER, this->noteNumber, nullptr);
    result.setProperty(TREEID_VELOCITY, this->velocity, nullptr);
    result.setProperty(TREEID_PAN, this->pan, nullptr);
    return result;
}


NoteData NoteData::fromValueTree(ValueTree &tree) {
    if (!tree.isValid() || !tree.hasType(TREEID_NOTE_DATA)) {
        throw std::invalid_argument("Input tree must be valid and of the correct type!");
    }

    NoteData noteData = NoteData();
    if (tree.hasProperty(TREEID_NOTE_NUMBER)) {
        noteData.noteNumber = tree.getProperty(TREEID_NOTE_NUMBER);
    }
    if (tree.hasProperty(TREEID_VELOCITY)) {
        noteData.velocity = tree.getProperty(TREEID_VELOCITY);
    }
    if (tree.hasProperty(TREEID_PAN)) {
        noteData.pan = tree.getProperty(TREEID_PAN);
    }

    return noteData;
}
