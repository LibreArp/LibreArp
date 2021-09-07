# LibreArp Changelog

## Versioning pattern

Information on LibreArp's versioning pattern can be found
in the [wiki](https://gitlab.com/LibreArp/LibreArp/wikis/versioning-pattern).

## Changelog

### LibreArp 2.2

* **NEW** The loop is now a freely movable region
  * The loop is allowed to start at an arbitrary time point
  * Notes can now exist outside the loop region - they are disabled if that is the case
* **NEW** Selection can now be stretched using the new green time selection borders
  * Useful for quick pattern rescaling, creation of triplets, quintuplets and more
* **NEW** *Behaviour modes* for when the host is not playing a track (*Silence*, *Passthrough*, *Pattern*)
  * Default is *Passthrough*
* **NEW** The pattern editor now provides some basic tooltips when hovering different elements
* **IMPROVE** Note highlight is now hidden when the mouse cursor leaves the editor
* **IMPROVE (Windows)** `LibreArp.vst3` is now supplied in an archive with the recommended directory structure pre-created
* **FIX** Output notes are no longer held indefinitely when the *MIDI Input Channel* is changed while playing
* **FIX** Fixed editor unresponsiveness during playback
* **FIX** Drag action type is now properly recognized when the mouse button is released
  * Fixes unwanted notes created by clicking right after releasing the mouse button without movement
* **FIX (LV2)** The editor is resizeable again using the reintroduced resizer corner

### LibreArp 2.1

* **NEW** Added a setting for GUI scale
* **IMPROVE** The plugin now remembers the velocity of the last edited note
* **IMPROVE** Changed the slogan on the *About* tab to match the one on the website and on GitLab
* **IMPROVE (Linux)** `LibreArp.so` is now supplied in an archive with the required directory structure pre-created
* **FIX** Fixed a pretty serious memory leak in handling Pattern editor's drag actions
* **FIX** Renoise now correctly accepts our MIDI output


### LibreArp 2.0

* **NEW** A new look-and-feel (based on a mock-up by [**Marek Jędrzejewski**](https://github.com/marekjedrzejewski))
* **NEW** Notes can now be added/removed from selection using `Ctrl + Shift + Left click`
* **NEW** Visualization of octaves
    * Notes can now be moved by an octave using `Ctrl + Up/Down`
* **NEW** Visualization of bars
* **NEW** Behaviour screen for local settings (MIDI in/out channels, octaves transposition, input velocity etc.)
* **NEW** Pattern preset saving/loading
* **NEW** Notes now have a settable velocity
  * Change using `Alt + Scroll Up/Down` when hovering over them (also works on selections)
  * `Alt + Middle click` to reset
* **NEW** The plugin is now able to automatically check for updates via its GitHub page (opt-in)
* **IMPROVE** Performance improvements
* **IMPROVE** Plugin is now marked as an instrument for better compatibility with some hosts
* **IMPROVE** Non-note MIDI data now gets passed through the plugin
* **IMPROVE** Input velocity is now taken into account when playing the arpeggio
    * This may be changed in the Behaviour screen
* **FIX** About box text is no longer mangled under Windows
* **FIX** Fix a crash that happens when editing patterns during playback
* **FIX** Fix a crash caused by invalid MIDI note data
* **FIX** Fix some potential race-conditions of the GUI and audio processing threads
* **FIX** Disable unused JUCE web browser module
    * This was causing some hosts to fail to scan the plugin
* **FIX** The pattern editor no longer scrolls awkwardly when editing notes
* **UNDER-THE-HOOD** Updated to JUCE 6
* **UNDER-THE-HOOD** Builds are now pure CMake (allows for automated builds)
* **UNDER-THE-HOOD** Added standalone version for debugging purposes

**Important note:** For licensing and technical reasons, the plugin no longer supports VST2. The VST3 version is incompatible with older versions of the plugin and cannot be simply dropped-in in the older versions' stead.


### LibreArp 1.1

* **FIX** Linux builds now should work on distros with older GLib (building on Ubuntu 16.04 LTS)
* **FIX** Notes are now highlighted when played


### LibreArp 1.0

The initial release
