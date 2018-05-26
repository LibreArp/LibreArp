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


