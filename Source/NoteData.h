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


