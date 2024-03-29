# LibreArp Changelog

## Versioning pattern

Information on LibreArp's versioning pattern can be found
in the [wiki](https://gitlab.com/LibreArp/LibreArp/wikis/versioning-pattern).

## Changelog

### LibreArp 2.5

* **NEW** *Selection duplication*: Using `Ctrl+B` and `Ctrl+Shift+B`, it is now possible to duplicate selected notes
  * Without `Shift`, new notes are placed *after* the selection; with `Shift`, they are placed *before* the selection
* **NEW** *Pattern offset*: Using the new *Record offset* button, you can set the starting position of the pattern
  relative to the song.
  * Arm the button by a click, set the starting position in the host DAW and start playback. The pattern will be offset
    to start at that starting position.
* **NEW** *Manual time signature*: You may now set the time signature visualized by the Pattern Editor manually,
  for better usability in hosts that do not properly report the time signature to their plugins.
* **IMPROVE** For consistency, the note bar (left to the pattern grid) now reacts to mouse scrolling and middle clicking
  similarly to the beat bar (above the pattern grid).
* **IMPROVE** Section titles have been introduced to the *Behaviour* tab for to improve clarity
* **IMPROVE** The default and minimum editor size is now 800x600 to accommodate for new controls on the *Behaviour* tab
* **FIX** The first note now gets transposed correctly into negative octaves, instead of being one extra octave lower

### LibreArp 2.4

* **NEW** *Note panel*: A panel to the left of the pattern editor visualizing octaves and note numbers
* **IMPROVE** Added scroll and zoom smoothing
* **IMPROVE** Extended pattern editor tooltips
  * They now describe the function of modifiers (`Alt`, `Ctrl`, `Shift`)
* **FIX** The grid and other elements in the pattern editor is now drawn more precisely relative to the notes
* **FIX** When zooming, scroll now remains in position relative to content
* **FIX** *Snap* is now a menu that only allows safe values
* **FIX** *Chord size* now correctly reads "Auto" when set to zero

### LibreArp 2.3

* **NEW** *Smart octaves*: When the input chord spans multiple octaves, transposition is done by that number of octaves
  * Guarantees that a higher LibreArp note will always be higher in the output MIDI
  * On by default in new instances; off by default in existing ones
* **NEW** The loop can now be resized and moved from the beat bar above the note grid
* **NEW** Added a *Swing* parameter that staggers the pattern in real time
* **NEW** Added a *Chord size* parameter that makes the plugin use a fixed number of input notes
  * If the actual number of input notes is greater than the chord size, they are selected according to the new *Note selection mode* parameter.
* **NEW** Added a *Bypass* parameter for DAWs that do not have a built-in bypass function
* **FIX** The plugin no longer crashes when the user clicks *Cancel* in the preset chooser dialog

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
