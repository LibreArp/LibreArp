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

#include "EditorState.h"

const juce::Identifier EditorState::TREEID_EDITOR_STATE = juce::Identifier("editorState"); // NOLINT
const juce::Identifier EditorState::TREEID_WIDTH = juce::Identifier("width"); // NOLINT
const juce::Identifier EditorState::TREEID_HEIGHT = juce::Identifier("height"); // NOLINT
const juce::Identifier EditorState::TREEID_DIVISOR = juce::Identifier("divisor"); // NOLINT
const juce::Identifier EditorState::TREEID_LAST_NOTE_LENGTH = juce::Identifier("lastNoteLength"); // NOLINT
const juce::Identifier EditorState::TREEID_PIXELS_PER_BEAT = juce::Identifier("pixelsPerBeat"); // NOLINT
const juce::Identifier EditorState::TREEID_PIXELS_PER_NOTE = juce::Identifier("pixelsPerNote"); // NOLINT
const juce::Identifier EditorState::TREEID_OFFSET_X = juce::Identifier("editorOffsetX"); // NOLINT
const juce::Identifier EditorState::TREEID_OFFSET_Y = juce::Identifier("editorOffsetY"); // NOLINT


juce::ValueTree EditorState::toValueTree() const {
    juce::ValueTree tree = juce::ValueTree(TREEID_EDITOR_STATE);
    tree.setProperty(TREEID_WIDTH, this->width, nullptr);
    tree.setProperty(TREEID_HEIGHT, this->height, nullptr);
    tree.setProperty(TREEID_DIVISOR, this->divisor, nullptr);
    tree.setProperty(TREEID_LAST_NOTE_LENGTH, juce::int64(this->lastNoteLength), nullptr);
    tree.setProperty(TREEID_PIXELS_PER_BEAT, this->pixelsPerBeat, nullptr);
    tree.setProperty(TREEID_PIXELS_PER_NOTE, this->pixelsPerNote, nullptr);
    tree.setProperty(TREEID_OFFSET_X, this->offsetX, nullptr);
    tree.setProperty(TREEID_OFFSET_Y, this->offsetY, nullptr);
    return tree;
}

EditorState EditorState::fromValueTree(juce::ValueTree &tree) {
    if (!tree.isValid() || !tree.hasType(TREEID_EDITOR_STATE)) {
        throw std::invalid_argument("Input tree must be valid and of the correct type!");
    }

    EditorState result;
    if (tree.hasProperty(TREEID_WIDTH)) {
        result.width = tree.getProperty(TREEID_WIDTH);
    }
    if (tree.hasProperty(TREEID_HEIGHT)) {
        result.height = tree.getProperty(TREEID_HEIGHT);
    }
    if (tree.hasProperty(TREEID_DIVISOR)) {
        result.divisor = tree.getProperty(TREEID_DIVISOR);
    }
    if (tree.hasProperty(TREEID_LAST_NOTE_LENGTH)) {
        result.lastNoteLength = (juce::int64) tree.getProperty(TREEID_LAST_NOTE_LENGTH);
    }
    if (tree.hasProperty(TREEID_PIXELS_PER_BEAT)) {
        result.pixelsPerBeat = tree.getProperty(TREEID_PIXELS_PER_BEAT);
    }
    if (tree.hasProperty(TREEID_PIXELS_PER_NOTE)) {
        result.pixelsPerNote = tree.getProperty(TREEID_PIXELS_PER_NOTE);
    }
    if (tree.hasProperty(TREEID_OFFSET_X)) {
        result.offsetX = tree.getProperty(TREEID_OFFSET_X);
    }
    if (tree.hasProperty(TREEID_OFFSET_Y)) {
        result.offsetY = tree.getProperty(TREEID_OFFSET_Y);
    }
    return result;
}
