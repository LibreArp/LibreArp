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
