# LibreArp Changelog

## Versioning pattern

Information on LibreArp's versioning pattern can be found
in the [wiki](https://gitlab.com/LibreArp/LibreArp/wikis/versioning-pattern).

## Changelog

### LibreArp 2.0

* **NEW** A new look-and-feel (based on a mock-up by [**Marek Jędrzejewski**](https://github.com/marekjedrzejewski))
* **NEW** Notes can now be added/removed from selection by `Ctrl + Shift + Left click`
* **NEW** Visualization of octaves
    * Notes can now be moved by the currently visualized octaves using `Ctrl + Up/Down`
* **NEW** Visualization of bars
* **NEW** Behaviour screen for local settings (MIDI in/out channels, octaves transposition, input velocity etc.)
* **NEW** Pattern preset saving/loading
* **NEW** Notes now have settable velocity using `Alt + Scroll Up/Down` when hovering over them (also works on selections)
* **NEW** The plugin is now able to automatically check for updates via its GitHub page (opt-in)
* **IMPROVE** Pattern editor optimized for performance
* **IMPROVE** Plugin is now marked as an instrument (aka. VSTi) for better compatibility with some hosts
* **IMPROVE** Non-note MIDI data now gets passed through the plugin
* **IMPROVE** Input velocity is now taken into account when playing the arpeggio
    * This may be changed in the Behaviour screen
* **FIX** About box text is now not mangled under Windows
* **FIX** Fix a crash that happens when editing patterns during playback
* **FIX** Fix a crash caused by invalid MIDI note data
* **FIX** Fix some potential race-conditions of the GUI and audio processing threads
* **FIX** Disable unused JUCE web browser module
    * This was causing some hosts to fail to scan the plugin
* **UNDER-THE-HOOD** Updated JUCE
* **UNDER-THE-HOOD** Now using FST instead of VST2 (compatible, nothing changes for the end user)
* **UNDER-THE-HOOD** Added standalone mode for debugging purposes


### LibreArp 1.1

* **FIX** Linux builds now should work on distros with older GLib (building on Ubuntu 16.04 LTS)
* **FIX** Notes are now highlighted when played


### LibreArp 1.0

The initial release
