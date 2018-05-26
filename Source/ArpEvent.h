#pragma once

#include <vector>
#include "NoteData.h"

class ArpEvent {
public:
    int64 time;
    std::vector<NoteData*> ons;
    std::vector<NoteData*> offs;

    bool operator<(ArpEvent &other);
    bool operator<=(ArpEvent &other);
    bool operator>(ArpEvent &other);
    bool operator>=(ArpEvent &other);
    bool operator==(ArpEvent &other);
};
