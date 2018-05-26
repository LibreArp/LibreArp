#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "ArpEvent.h"
#include "ArpNote.h"

class ArpPattern {
public:

    static const Identifier TREEID_PATTERN;
    static const Identifier TREEID_TIMEBASE;
    static const Identifier TREEID_LOOP_LENGTH;
    static const Identifier TREEID_NOTES;

    static constexpr int DEFAULT_TIMEBASE = 96;


    int64 loopLength;

    /**
     * Constructs a new pattern with the specified timebase.
     *
     * @param timebase the timebase in PPQ
     */
    explicit ArpPattern(int timebase = DEFAULT_TIMEBASE);

    ~ArpPattern();


    /**
     * Gets the timebase of the pattern.
     *
     * @return the timebase of the pattern in PPQ
     */
    int getTimebase();

    /**
     * Gets a pointer to the vector of notes in this pattern.
     *
     * @return
     */
    std::vector<ArpNote> &getNotes();


    /**
     * Builds a vector of ArpEvents, sorted by time, from this pattern.
     *
     * @return a vector of ArpEvents
     */
    std::vector<ArpEvent> build();

    /**
     * Gets the pattern as a ValueTree.
     *
     * @return the value tree representing this pattern
     */
    ValueTree toValueTree();


    static ArpPattern fromValueTree(ValueTree &tree);

private:
    int timebase;
    std::vector<ArpNote> notes;
};
