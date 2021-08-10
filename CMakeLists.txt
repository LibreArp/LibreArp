#
# This file is part of LibreArp
#
# LibreArp is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# LibreArp is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see https://librearp.gitlab.io/license/.
#

set(LIBREARP_VERSION "2.0")
set(LIBREARP_VERSION_CODE "020000")

cmake_minimum_required(VERSION 3.16)
project(LibreArp VERSION ${LIBREARP_VERSION})

add_definitions(
        -DLIBREARP_VERSION=\"${LIBREARP_VERSION}\"
        -DLIBREARP_VERSION_CODE=\"${LIBREARP_VERSION_CODE}\")

set(CMAKE_CXX_STANDARD 17)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC" )
endif()

add_subdirectory(Vendor/juce)

juce_add_binary_data(LibreArpBinaries
        HEADER_NAME LibreArpBinaryData.h
        NAMESPACE LibreArpBin
        SOURCES Fonts/overpass-regular.otf)

juce_add_plugin(LibreArp
        COMPANY_NAME "The LibreArp contributors"
        IS_SYNTH TRUE
        NEEDS_MIDI_INPUT TRUE
        NEEDS_MIDI_OUTPUT TRUE
        IS_MIDI_EFFECT TRUE
        VST_NUM_MIDI_INS 1
        VST_NUM_MIDI_OUTS 1
        VST3_CATEGORIES "Fx Instrument Tools"
        AU_MAIN_TYPE "kAudioUnitType_MIDIProcessor"
        EDITOR_WANTS_KEYBOARD_FOCUS TRUE
        COPY_PLUGIN_AFTER_BUILD FALSE
        PLUGIN_MANUFACTURER_CODE Larx
        PLUGIN_CODE Larx
        FORMATS AU VST3 Standalone
        NEEDS_CURL TRUE
        PRODUCT_NAME "LibreArp")

if(MINGW)
    target_compile_options(LibreArp PRIVATE "-Wa,-mbig-obj")
endif()

target_sources(LibreArp
        PRIVATE

        Source/editor/about/AboutBox.cpp Source/editor/about/AboutBox.h Source/editor/about/AboutBoxConfig.h

        Source/editor/behaviour/BehaviourSettingsEditor.cpp Source/editor/behaviour/BehaviourSettingsEditor.h

        Source/editor/pattern/BeatBar.cpp Source/editor/pattern/BeatBar.h
        Source/editor/pattern/PatternEditor.cpp Source/editor/pattern/PatternEditor.h
        Source/editor/pattern/PatternEditorView.cpp Source/editor/pattern/PatternEditorView.h

        Source/editor/settings/SettingsEditor.cpp Source/editor/settings/SettingsEditor.h

        Source/editor/EditorState.cpp Source/editor/EditorState.h
        Source/editor/LArpLookAndFeel.cpp Source/editor/LArpLookAndFeel.h
        Source/editor/MainEditor.cpp Source/editor/MainEditor.h

        Source/util/Defer.h

        Source/ArpBuiltEvents.cpp Source/ArpBuiltEvents.h
        Source/ArpNote.cpp Source/ArpNote.h
        Source/ArpPattern.cpp Source/ArpPattern.h
        Source/AudioUpdatable.h
        Source/BuildConfig.h
        Source/Globals.cpp Source/Globals.h
        Source/LibreArp.cpp Source/LibreArp.h
        Source/NoteData.cpp Source/NoteData.h
        Source/Updater.cpp Source/Updater.h
        )

target_compile_definitions(LibreArp
        PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=1
        JUCE_USE_FLAC=0
        JUCE_USE_OGGVORBIS=0
        JUCE_USE_WINDOWS_MEDIA_FORMAT=0
        JUCE_VST3_CAN_REPLACE_VST2=0
        JUCE_DISPLAY_SPLASH_SCREEN=0 # we are GPL so we are allowed
        )

target_link_libraries(LibreArp
        PRIVATE
        LibreArpBinaries
        juce::juce_audio_utils
        juce::juce_audio_plugin_client
        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)

