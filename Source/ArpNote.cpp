#include "ArpNote.h"

const Identifier ArpNote::TREEID_NOTE = Identifier("note"); // NOLINT
const Identifier ArpNote::TREEID_START_POINT = Identifier("start"); // NOLINT
const Identifier ArpNote::TREEID_END_POINT = Identifier("end"); // NOLINT


ArpNote::ArpNote(NoteData data) {
    this->data = data;
    this->startPoint = 0;
    this->endPoint = 1;
}


ValueTree ArpNote::toValueTree() {
    ValueTree result = ValueTree(TREEID_NOTE);
    result.appendChild(this->data.toValueTree(), nullptr);
    result.setProperty(TREEID_START_POINT, this->startPoint, nullptr);
    result.setProperty(TREEID_END_POINT, this->endPoint, nullptr);
    return result;
}


ArpNote ArpNote::fromValueTree(ValueTree &tree) {
    if (!tree.isValid() || !tree.hasType(TREEID_NOTE)) {
        throw std::invalid_argument("Input tree must be valid and of the correct type!");
    }

    ArpNote result = ArpNote();

    ValueTree dataTree = tree.getChildWithName(NoteData::TREEID_NOTE_DATA);
    if (dataTree.isValid()) {
        result.data = NoteData::fromValueTree(dataTree);
    }

    if (tree.hasProperty(TREEID_START_POINT)) {
        result.startPoint = tree.getProperty(TREEID_START_POINT);
    }

    if (tree.hasProperty(TREEID_END_POINT)) {
        result.endPoint = tree.getProperty(TREEID_END_POINT);
    }

    return result;
}
