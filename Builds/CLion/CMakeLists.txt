# Automatically generated CMakeLists, created by the Projucer
# Don't edit this file! Your changes will be overwritten when you re-save the Projucer project!

cmake_minimum_required (VERSION 3.4.1)

if (NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE "Debug"  CACHE STRING "Choose the type of build." FORCE)
endif (NOT CMAKE_BUILD_TYPE)

###############################################################################
# Linux Makefile
###############################################################################

if (UNIX AND NOT APPLE)

project ("LibreArp" C CXX)

find_package (PkgConfig REQUIRED)
pkg_search_module (FREETYPE2 REQUIRED freetype2)
pkg_search_module (LIBCURL REQUIRED libcurl)
pkg_search_module (X11 REQUIRED x11)
pkg_search_module (XEXT REQUIRED xext)
pkg_search_module (XINERAMA REQUIRED xinerama)
pkg_search_module (WEBKIT2GTK-4.0 REQUIRED webkit2gtk-4.0)
pkg_search_module (GTK+-X11-3.0 REQUIRED gtk+-x11-3.0)

add_library (VST MODULE
    "../../Vendor/juce/modules/juce_audio_plugin_client/juce_audio_plugin_client_VST2.cpp"
    "../../JuceLibraryCode/include_juce_audio_plugin_client_VST2.cpp"
)

set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/juce_audio_plugin_client_VST2.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)

add_library (SHARED_CODE STATIC
    "../../Source/editor/MainEditor.cpp"
    "../../Source/editor/MainEditor.h"
    "../../Source/util/PatternUtil.cpp"
    "../../Source/util/PatternUtil.h"
    "../../Source/ArpEvent.cpp"
    "../../Source/ArpEvent.h"
    "../../Source/ArpIntegrityException.cpp"
    "../../Source/ArpIntegrityException.h"
    "../../Source/ArpNote.cpp"
    "../../Source/ArpNote.h"
    "../../Source/ArpPattern.cpp"
    "../../Source/ArpPattern.h"
    "../../Source/LibreArp.cpp"
    "../../Source/LibreArp.h"
    "../../Source/NoteData.cpp"
    "../../Source/NoteData.h"
    "../../Vendor/juce/modules/juce_audio_basics/audio_play_head/juce_AudioPlayHead.h"
    "../../Vendor/juce/modules/juce_audio_basics/buffers/juce_AudioChannelSet.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/buffers/juce_AudioChannelSet.h"
    "../../Vendor/juce/modules/juce_audio_basics/buffers/juce_AudioDataConverters.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/buffers/juce_AudioDataConverters.h"
    "../../Vendor/juce/modules/juce_audio_basics/buffers/juce_AudioSampleBuffer.h"
    "../../Vendor/juce/modules/juce_audio_basics/buffers/juce_FloatVectorOperations.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/buffers/juce_FloatVectorOperations.h"
    "../../Vendor/juce/modules/juce_audio_basics/effects/juce_CatmullRomInterpolator.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/effects/juce_CatmullRomInterpolator.h"
    "../../Vendor/juce/modules/juce_audio_basics/effects/juce_Decibels.h"
    "../../Vendor/juce/modules/juce_audio_basics/effects/juce_IIRFilter.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/effects/juce_IIRFilter.h"
    "../../Vendor/juce/modules/juce_audio_basics/effects/juce_LagrangeInterpolator.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/effects/juce_LagrangeInterpolator.h"
    "../../Vendor/juce/modules/juce_audio_basics/effects/juce_LinearSmoothedValue.h"
    "../../Vendor/juce/modules/juce_audio_basics/effects/juce_Reverb.h"
    "../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiBuffer.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiBuffer.h"
    "../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiFile.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiFile.h"
    "../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiKeyboardState.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiKeyboardState.h"
    "../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiMessage.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiMessage.h"
    "../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiMessageSequence.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiMessageSequence.h"
    "../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiRPN.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiRPN.h"
    "../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPEInstrument.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPEInstrument.h"
    "../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPEMessages.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPEMessages.h"
    "../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPENote.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPENote.h"
    "../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPESynthesiser.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPESynthesiser.h"
    "../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPESynthesiserBase.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPESynthesiserBase.h"
    "../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPESynthesiserVoice.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPESynthesiserVoice.h"
    "../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPEUtils.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPEUtils.h"
    "../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPEValue.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPEValue.h"
    "../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPEZoneLayout.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPEZoneLayout.h"
    "../../Vendor/juce/modules/juce_audio_basics/native/juce_mac_CoreAudioLayouts.h"
    "../../Vendor/juce/modules/juce_audio_basics/sources/juce_AudioSource.h"
    "../../Vendor/juce/modules/juce_audio_basics/sources/juce_BufferingAudioSource.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/sources/juce_BufferingAudioSource.h"
    "../../Vendor/juce/modules/juce_audio_basics/sources/juce_ChannelRemappingAudioSource.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/sources/juce_ChannelRemappingAudioSource.h"
    "../../Vendor/juce/modules/juce_audio_basics/sources/juce_IIRFilterAudioSource.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/sources/juce_IIRFilterAudioSource.h"
    "../../Vendor/juce/modules/juce_audio_basics/sources/juce_MemoryAudioSource.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/sources/juce_MemoryAudioSource.h"
    "../../Vendor/juce/modules/juce_audio_basics/sources/juce_MixerAudioSource.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/sources/juce_MixerAudioSource.h"
    "../../Vendor/juce/modules/juce_audio_basics/sources/juce_PositionableAudioSource.h"
    "../../Vendor/juce/modules/juce_audio_basics/sources/juce_ResamplingAudioSource.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/sources/juce_ResamplingAudioSource.h"
    "../../Vendor/juce/modules/juce_audio_basics/sources/juce_ReverbAudioSource.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/sources/juce_ReverbAudioSource.h"
    "../../Vendor/juce/modules/juce_audio_basics/sources/juce_ToneGeneratorAudioSource.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/sources/juce_ToneGeneratorAudioSource.h"
    "../../Vendor/juce/modules/juce_audio_basics/synthesisers/juce_Synthesiser.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/synthesisers/juce_Synthesiser.h"
    "../../Vendor/juce/modules/juce_audio_basics/juce_audio_basics.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/juce_audio_basics.mm"
    "../../Vendor/juce/modules/juce_audio_basics/juce_audio_basics.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUBase.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUBase.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUBaseHelper.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUBuffer.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUBuffer.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUCarbonViewBase.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUCarbonViewBase.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUCarbonViewControl.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUCarbonViewControl.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUCarbonViewDispatch.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUDispatch.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUDispatch.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUInputElement.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUInputElement.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUInputFormatConverter.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUMIDIBase.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUMIDIBase.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUOutputBase.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUOutputBase.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUOutputElement.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUOutputElement.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUPlugInDispatch.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUPlugInDispatch.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUScopeElement.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUScopeElement.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUSilentTimeout.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUTimestampGenerator.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUViewLocalizedStringKeys.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAAtomic.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAAtomicStack.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAAudioChannelLayout.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAAudioChannelLayout.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAAUParameter.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAAUParameter.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAAutoDisposer.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CADebugMacros.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CADebugPrintf.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAException.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAHostTimeBase.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAMath.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAMutex.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAMutex.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CarbonEventHandler.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CarbonEventHandler.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAReferenceCounted.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAStreamBasicDescription.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAStreamBasicDescription.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAThreadSafeList.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAVectorUnit.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAVectorUnit.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAVectorUnitTypes.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAXException.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/ComponentBase.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/ComponentBase.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/MusicDeviceBase.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/MusicDeviceBase.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/Standalone/juce_StandaloneFilterApp.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/Standalone/juce_StandaloneFilterWindow.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/utility/juce_CarbonVisibility.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/utility/juce_CheckSettingMacros.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/utility/juce_FakeMouseMoveGenerator.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/utility/juce_IncludeModuleHeaders.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/utility/juce_IncludeSystemHeaders.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/utility/juce_PluginHostType.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/utility/juce_PluginUtilities.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/utility/juce_WindowsHooks.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/VST/juce_VST_Wrapper.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/VST/juce_VST_Wrapper.mm"
    "../../Vendor/juce/modules/juce_audio_plugin_client/VST/juce_VSTCallbackHandler.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/juce_audio_plugin_client_utils.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/juce_audio_plugin_client_VST_utils.mm"
    "../../Vendor/juce/modules/juce_audio_plugin_client/juce_audio_plugin_client.h"
    "../../Vendor/juce/modules/juce_audio_processors/format/juce_AudioPluginFormat.cpp"
    "../../Vendor/juce/modules/juce_audio_processors/format/juce_AudioPluginFormat.h"
    "../../Vendor/juce/modules/juce_audio_processors/format/juce_AudioPluginFormatManager.cpp"
    "../../Vendor/juce/modules/juce_audio_processors/format/juce_AudioPluginFormatManager.h"
    "../../Vendor/juce/modules/juce_audio_processors/format_types/juce_AudioUnitPluginFormat.h"
    "../../Vendor/juce/modules/juce_audio_processors/format_types/juce_AudioUnitPluginFormat.mm"
    "../../Vendor/juce/modules/juce_audio_processors/format_types/juce_LADSPAPluginFormat.cpp"
    "../../Vendor/juce/modules/juce_audio_processors/format_types/juce_LADSPAPluginFormat.h"
    "../../Vendor/juce/modules/juce_audio_processors/format_types/juce_LegacyAudioParameter.cpp"
    "../../Vendor/juce/modules/juce_audio_processors/format_types/juce_VST3Common.h"
    "../../Vendor/juce/modules/juce_audio_processors/format_types/juce_VST3Headers.h"
    "../../Vendor/juce/modules/juce_audio_processors/format_types/juce_VST3PluginFormat.cpp"
    "../../Vendor/juce/modules/juce_audio_processors/format_types/juce_VST3PluginFormat.h"
    "../../Vendor/juce/modules/juce_audio_processors/format_types/juce_VSTCommon.h"
    "../../Vendor/juce/modules/juce_audio_processors/format_types/juce_VSTInterface.h"
    "../../Vendor/juce/modules/juce_audio_processors/format_types/juce_VSTMidiEventList.h"
    "../../Vendor/juce/modules/juce_audio_processors/format_types/juce_VSTPluginFormat.cpp"
    "../../Vendor/juce/modules/juce_audio_processors/format_types/juce_VSTPluginFormat.h"
    "../../Vendor/juce/modules/juce_audio_processors/processors/juce_AudioPluginInstance.cpp"
    "../../Vendor/juce/modules/juce_audio_processors/processors/juce_AudioPluginInstance.h"
    "../../Vendor/juce/modules/juce_audio_processors/processors/juce_AudioProcessor.cpp"
    "../../Vendor/juce/modules/juce_audio_processors/processors/juce_AudioProcessor.h"
    "../../Vendor/juce/modules/juce_audio_processors/processors/juce_AudioProcessorEditor.cpp"
    "../../Vendor/juce/modules/juce_audio_processors/processors/juce_AudioProcessorEditor.h"
    "../../Vendor/juce/modules/juce_audio_processors/processors/juce_AudioProcessorGraph.cpp"
    "../../Vendor/juce/modules/juce_audio_processors/processors/juce_AudioProcessorGraph.h"
    "../../Vendor/juce/modules/juce_audio_processors/processors/juce_AudioProcessorListener.h"
    "../../Vendor/juce/modules/juce_audio_processors/processors/juce_AudioProcessorParameter.h"
    "../../Vendor/juce/modules/juce_audio_processors/processors/juce_GenericAudioProcessorEditor.cpp"
    "../../Vendor/juce/modules/juce_audio_processors/processors/juce_GenericAudioProcessorEditor.h"
    "../../Vendor/juce/modules/juce_audio_processors/processors/juce_PluginDescription.cpp"
    "../../Vendor/juce/modules/juce_audio_processors/processors/juce_PluginDescription.h"
    "../../Vendor/juce/modules/juce_audio_processors/scanning/juce_KnownPluginList.cpp"
    "../../Vendor/juce/modules/juce_audio_processors/scanning/juce_KnownPluginList.h"
    "../../Vendor/juce/modules/juce_audio_processors/scanning/juce_PluginDirectoryScanner.cpp"
    "../../Vendor/juce/modules/juce_audio_processors/scanning/juce_PluginDirectoryScanner.h"
    "../../Vendor/juce/modules/juce_audio_processors/scanning/juce_PluginListComponent.cpp"
    "../../Vendor/juce/modules/juce_audio_processors/scanning/juce_PluginListComponent.h"
    "../../Vendor/juce/modules/juce_audio_processors/utilities/juce_AudioParameterBool.h"
    "../../Vendor/juce/modules/juce_audio_processors/utilities/juce_AudioParameterChoice.h"
    "../../Vendor/juce/modules/juce_audio_processors/utilities/juce_AudioParameterFloat.h"
    "../../Vendor/juce/modules/juce_audio_processors/utilities/juce_AudioParameterInt.h"
    "../../Vendor/juce/modules/juce_audio_processors/utilities/juce_AudioProcessorParameters.cpp"
    "../../Vendor/juce/modules/juce_audio_processors/utilities/juce_AudioProcessorParameterWithID.h"
    "../../Vendor/juce/modules/juce_audio_processors/utilities/juce_AudioProcessorValueTreeState.cpp"
    "../../Vendor/juce/modules/juce_audio_processors/utilities/juce_AudioProcessorValueTreeState.h"
    "../../Vendor/juce/modules/juce_audio_processors/juce_audio_processors.cpp"
    "../../Vendor/juce/modules/juce_audio_processors/juce_audio_processors.mm"
    "../../Vendor/juce/modules/juce_audio_processors/juce_audio_processors.h"
    "../../Vendor/juce/modules/juce_core/containers/juce_AbstractFifo.cpp"
    "../../Vendor/juce/modules/juce_core/containers/juce_AbstractFifo.h"
    "../../Vendor/juce/modules/juce_core/containers/juce_Array.h"
    "../../Vendor/juce/modules/juce_core/containers/juce_ArrayAllocationBase.h"
    "../../Vendor/juce/modules/juce_core/containers/juce_DynamicObject.cpp"
    "../../Vendor/juce/modules/juce_core/containers/juce_DynamicObject.h"
    "../../Vendor/juce/modules/juce_core/containers/juce_ElementComparator.h"
    "../../Vendor/juce/modules/juce_core/containers/juce_HashMap.h"
    "../../Vendor/juce/modules/juce_core/containers/juce_HashMap_test.cpp"
    "../../Vendor/juce/modules/juce_core/containers/juce_LinkedListPointer.h"
    "../../Vendor/juce/modules/juce_core/containers/juce_ListenerList.h"
    "../../Vendor/juce/modules/juce_core/containers/juce_NamedValueSet.cpp"
    "../../Vendor/juce/modules/juce_core/containers/juce_NamedValueSet.h"
    "../../Vendor/juce/modules/juce_core/containers/juce_OwnedArray.h"
    "../../Vendor/juce/modules/juce_core/containers/juce_PropertySet.cpp"
    "../../Vendor/juce/modules/juce_core/containers/juce_PropertySet.h"
    "../../Vendor/juce/modules/juce_core/containers/juce_ReferenceCountedArray.h"
    "../../Vendor/juce/modules/juce_core/containers/juce_ScopedValueSetter.h"
    "../../Vendor/juce/modules/juce_core/containers/juce_SortedSet.h"
    "../../Vendor/juce/modules/juce_core/containers/juce_SparseSet.cpp"
    "../../Vendor/juce/modules/juce_core/containers/juce_SparseSet.h"
    "../../Vendor/juce/modules/juce_core/containers/juce_Variant.cpp"
    "../../Vendor/juce/modules/juce_core/containers/juce_Variant.h"
    "../../Vendor/juce/modules/juce_core/files/juce_DirectoryIterator.cpp"
    "../../Vendor/juce/modules/juce_core/files/juce_DirectoryIterator.h"
    "../../Vendor/juce/modules/juce_core/files/juce_File.cpp"
    "../../Vendor/juce/modules/juce_core/files/juce_File.h"
    "../../Vendor/juce/modules/juce_core/files/juce_FileFilter.cpp"
    "../../Vendor/juce/modules/juce_core/files/juce_FileFilter.h"
    "../../Vendor/juce/modules/juce_core/files/juce_FileInputStream.cpp"
    "../../Vendor/juce/modules/juce_core/files/juce_FileInputStream.h"
    "../../Vendor/juce/modules/juce_core/files/juce_FileOutputStream.cpp"
    "../../Vendor/juce/modules/juce_core/files/juce_FileOutputStream.h"
    "../../Vendor/juce/modules/juce_core/files/juce_FileSearchPath.cpp"
    "../../Vendor/juce/modules/juce_core/files/juce_FileSearchPath.h"
    "../../Vendor/juce/modules/juce_core/files/juce_MemoryMappedFile.h"
    "../../Vendor/juce/modules/juce_core/files/juce_TemporaryFile.cpp"
    "../../Vendor/juce/modules/juce_core/files/juce_TemporaryFile.h"
    "../../Vendor/juce/modules/juce_core/files/juce_WildcardFileFilter.cpp"
    "../../Vendor/juce/modules/juce_core/files/juce_WildcardFileFilter.h"
    "../../Vendor/juce/modules/juce_core/javascript/juce_Javascript.cpp"
    "../../Vendor/juce/modules/juce_core/javascript/juce_Javascript.h"
    "../../Vendor/juce/modules/juce_core/javascript/juce_JSON.cpp"
    "../../Vendor/juce/modules/juce_core/javascript/juce_JSON.h"
    "../../Vendor/juce/modules/juce_core/logging/juce_FileLogger.cpp"
    "../../Vendor/juce/modules/juce_core/logging/juce_FileLogger.h"
    "../../Vendor/juce/modules/juce_core/logging/juce_Logger.cpp"
    "../../Vendor/juce/modules/juce_core/logging/juce_Logger.h"
    "../../Vendor/juce/modules/juce_core/maths/juce_BigInteger.cpp"
    "../../Vendor/juce/modules/juce_core/maths/juce_BigInteger.h"
    "../../Vendor/juce/modules/juce_core/maths/juce_Expression.cpp"
    "../../Vendor/juce/modules/juce_core/maths/juce_Expression.h"
    "../../Vendor/juce/modules/juce_core/maths/juce_MathsFunctions.h"
    "../../Vendor/juce/modules/juce_core/maths/juce_NormalisableRange.h"
    "../../Vendor/juce/modules/juce_core/maths/juce_Random.cpp"
    "../../Vendor/juce/modules/juce_core/maths/juce_Random.h"
    "../../Vendor/juce/modules/juce_core/maths/juce_Range.h"
    "../../Vendor/juce/modules/juce_core/maths/juce_StatisticsAccumulator.h"
    "../../Vendor/juce/modules/juce_core/memory/juce_Atomic.h"
    "../../Vendor/juce/modules/juce_core/memory/juce_ByteOrder.h"
    "../../Vendor/juce/modules/juce_core/memory/juce_ContainerDeletePolicy.h"
    "../../Vendor/juce/modules/juce_core/memory/juce_HeapBlock.h"
    "../../Vendor/juce/modules/juce_core/memory/juce_LeakedObjectDetector.h"
    "../../Vendor/juce/modules/juce_core/memory/juce_Memory.h"
    "../../Vendor/juce/modules/juce_core/memory/juce_MemoryBlock.cpp"
    "../../Vendor/juce/modules/juce_core/memory/juce_MemoryBlock.h"
    "../../Vendor/juce/modules/juce_core/memory/juce_OptionalScopedPointer.h"
    "../../Vendor/juce/modules/juce_core/memory/juce_ReferenceCountedObject.h"
    "../../Vendor/juce/modules/juce_core/memory/juce_ScopedPointer.h"
    "../../Vendor/juce/modules/juce_core/memory/juce_SharedResourcePointer.h"
    "../../Vendor/juce/modules/juce_core/memory/juce_Singleton.h"
    "../../Vendor/juce/modules/juce_core/memory/juce_WeakReference.h"
    "../../Vendor/juce/modules/juce_core/misc/juce_Result.cpp"
    "../../Vendor/juce/modules/juce_core/misc/juce_Result.h"
    "../../Vendor/juce/modules/juce_core/misc/juce_RuntimePermissions.cpp"
    "../../Vendor/juce/modules/juce_core/misc/juce_RuntimePermissions.h"
    "../../Vendor/juce/modules/juce_core/misc/juce_StdFunctionCompat.cpp"
    "../../Vendor/juce/modules/juce_core/misc/juce_StdFunctionCompat.h"
    "../../Vendor/juce/modules/juce_core/misc/juce_Uuid.cpp"
    "../../Vendor/juce/modules/juce_core/misc/juce_Uuid.h"
    "../../Vendor/juce/modules/juce_core/misc/juce_WindowsRegistry.h"
    "../../Vendor/juce/modules/juce_core/native/juce_android_Files.cpp"
    "../../Vendor/juce/modules/juce_core/native/juce_android_JNIHelpers.h"
    "../../Vendor/juce/modules/juce_core/native/juce_android_Misc.cpp"
    "../../Vendor/juce/modules/juce_core/native/juce_android_Network.cpp"
    "../../Vendor/juce/modules/juce_core/native/juce_android_RuntimePermissions.cpp"
    "../../Vendor/juce/modules/juce_core/native/juce_android_SystemStats.cpp"
    "../../Vendor/juce/modules/juce_core/native/juce_android_Threads.cpp"
    "../../Vendor/juce/modules/juce_core/native/juce_BasicNativeHeaders.h"
    "../../Vendor/juce/modules/juce_core/native/juce_curl_Network.cpp"
    "../../Vendor/juce/modules/juce_core/native/juce_linux_CommonFile.cpp"
    "../../Vendor/juce/modules/juce_core/native/juce_linux_Files.cpp"
    "../../Vendor/juce/modules/juce_core/native/juce_linux_Network.cpp"
    "../../Vendor/juce/modules/juce_core/native/juce_linux_SystemStats.cpp"
    "../../Vendor/juce/modules/juce_core/native/juce_linux_Threads.cpp"
    "../../Vendor/juce/modules/juce_core/native/juce_mac_ClangBugWorkaround.h"
    "../../Vendor/juce/modules/juce_core/native/juce_mac_Files.mm"
    "../../Vendor/juce/modules/juce_core/native/juce_mac_Network.mm"
    "../../Vendor/juce/modules/juce_core/native/juce_mac_Strings.mm"
    "../../Vendor/juce/modules/juce_core/native/juce_mac_SystemStats.mm"
    "../../Vendor/juce/modules/juce_core/native/juce_mac_Threads.mm"
    "../../Vendor/juce/modules/juce_core/native/juce_osx_ObjCHelpers.h"
    "../../Vendor/juce/modules/juce_core/native/juce_posix_NamedPipe.cpp"
    "../../Vendor/juce/modules/juce_core/native/juce_posix_SharedCode.h"
    "../../Vendor/juce/modules/juce_core/native/juce_win32_ComSmartPtr.h"
    "../../Vendor/juce/modules/juce_core/native/juce_win32_Files.cpp"
    "../../Vendor/juce/modules/juce_core/native/juce_win32_Network.cpp"
    "../../Vendor/juce/modules/juce_core/native/juce_win32_Registry.cpp"
    "../../Vendor/juce/modules/juce_core/native/juce_win32_SystemStats.cpp"
    "../../Vendor/juce/modules/juce_core/native/juce_win32_Threads.cpp"
    "../../Vendor/juce/modules/juce_core/network/juce_IPAddress.cpp"
    "../../Vendor/juce/modules/juce_core/network/juce_IPAddress.h"
    "../../Vendor/juce/modules/juce_core/network/juce_MACAddress.cpp"
    "../../Vendor/juce/modules/juce_core/network/juce_MACAddress.h"
    "../../Vendor/juce/modules/juce_core/network/juce_NamedPipe.cpp"
    "../../Vendor/juce/modules/juce_core/network/juce_NamedPipe.h"
    "../../Vendor/juce/modules/juce_core/network/juce_Socket.cpp"
    "../../Vendor/juce/modules/juce_core/network/juce_Socket.h"
    "../../Vendor/juce/modules/juce_core/network/juce_URL.cpp"
    "../../Vendor/juce/modules/juce_core/network/juce_URL.h"
    "../../Vendor/juce/modules/juce_core/network/juce_WebInputStream.cpp"
    "../../Vendor/juce/modules/juce_core/network/juce_WebInputStream.h"
    "../../Vendor/juce/modules/juce_core/streams/juce_BufferedInputStream.cpp"
    "../../Vendor/juce/modules/juce_core/streams/juce_BufferedInputStream.h"
    "../../Vendor/juce/modules/juce_core/streams/juce_FileInputSource.cpp"
    "../../Vendor/juce/modules/juce_core/streams/juce_FileInputSource.h"
    "../../Vendor/juce/modules/juce_core/streams/juce_InputSource.h"
    "../../Vendor/juce/modules/juce_core/streams/juce_InputStream.cpp"
    "../../Vendor/juce/modules/juce_core/streams/juce_InputStream.h"
    "../../Vendor/juce/modules/juce_core/streams/juce_MemoryInputStream.cpp"
    "../../Vendor/juce/modules/juce_core/streams/juce_MemoryInputStream.h"
    "../../Vendor/juce/modules/juce_core/streams/juce_MemoryOutputStream.cpp"
    "../../Vendor/juce/modules/juce_core/streams/juce_MemoryOutputStream.h"
    "../../Vendor/juce/modules/juce_core/streams/juce_OutputStream.cpp"
    "../../Vendor/juce/modules/juce_core/streams/juce_OutputStream.h"
    "../../Vendor/juce/modules/juce_core/streams/juce_SubregionStream.cpp"
    "../../Vendor/juce/modules/juce_core/streams/juce_SubregionStream.h"
    "../../Vendor/juce/modules/juce_core/streams/juce_URLInputSource.cpp"
    "../../Vendor/juce/modules/juce_core/streams/juce_URLInputSource.h"
    "../../Vendor/juce/modules/juce_core/system/juce_CompilerSupport.h"
    "../../Vendor/juce/modules/juce_core/system/juce_PlatformDefs.h"
    "../../Vendor/juce/modules/juce_core/system/juce_StandardHeader.h"
    "../../Vendor/juce/modules/juce_core/system/juce_SystemStats.cpp"
    "../../Vendor/juce/modules/juce_core/system/juce_SystemStats.h"
    "../../Vendor/juce/modules/juce_core/system/juce_TargetPlatform.h"
    "../../Vendor/juce/modules/juce_core/text/juce_Base64.cpp"
    "../../Vendor/juce/modules/juce_core/text/juce_Base64.h"
    "../../Vendor/juce/modules/juce_core/text/juce_CharacterFunctions.cpp"
    "../../Vendor/juce/modules/juce_core/text/juce_CharacterFunctions.h"
    "../../Vendor/juce/modules/juce_core/text/juce_CharPointer_ASCII.h"
    "../../Vendor/juce/modules/juce_core/text/juce_CharPointer_UTF8.h"
    "../../Vendor/juce/modules/juce_core/text/juce_CharPointer_UTF16.h"
    "../../Vendor/juce/modules/juce_core/text/juce_CharPointer_UTF32.h"
    "../../Vendor/juce/modules/juce_core/text/juce_Identifier.cpp"
    "../../Vendor/juce/modules/juce_core/text/juce_Identifier.h"
    "../../Vendor/juce/modules/juce_core/text/juce_LocalisedStrings.cpp"
    "../../Vendor/juce/modules/juce_core/text/juce_LocalisedStrings.h"
    "../../Vendor/juce/modules/juce_core/text/juce_NewLine.h"
    "../../Vendor/juce/modules/juce_core/text/juce_String.cpp"
    "../../Vendor/juce/modules/juce_core/text/juce_String.h"
    "../../Vendor/juce/modules/juce_core/text/juce_StringArray.cpp"
    "../../Vendor/juce/modules/juce_core/text/juce_StringArray.h"
    "../../Vendor/juce/modules/juce_core/text/juce_StringPairArray.cpp"
    "../../Vendor/juce/modules/juce_core/text/juce_StringPairArray.h"
    "../../Vendor/juce/modules/juce_core/text/juce_StringPool.cpp"
    "../../Vendor/juce/modules/juce_core/text/juce_StringPool.h"
    "../../Vendor/juce/modules/juce_core/text/juce_StringRef.h"
    "../../Vendor/juce/modules/juce_core/text/juce_TextDiff.cpp"
    "../../Vendor/juce/modules/juce_core/text/juce_TextDiff.h"
    "../../Vendor/juce/modules/juce_core/threads/juce_ChildProcess.cpp"
    "../../Vendor/juce/modules/juce_core/threads/juce_ChildProcess.h"
    "../../Vendor/juce/modules/juce_core/threads/juce_CriticalSection.h"
    "../../Vendor/juce/modules/juce_core/threads/juce_DynamicLibrary.h"
    "../../Vendor/juce/modules/juce_core/threads/juce_HighResolutionTimer.cpp"
    "../../Vendor/juce/modules/juce_core/threads/juce_HighResolutionTimer.h"
    "../../Vendor/juce/modules/juce_core/threads/juce_InterProcessLock.h"
    "../../Vendor/juce/modules/juce_core/threads/juce_Process.h"
    "../../Vendor/juce/modules/juce_core/threads/juce_ReadWriteLock.cpp"
    "../../Vendor/juce/modules/juce_core/threads/juce_ReadWriteLock.h"
    "../../Vendor/juce/modules/juce_core/threads/juce_ScopedLock.h"
    "../../Vendor/juce/modules/juce_core/threads/juce_ScopedReadLock.h"
    "../../Vendor/juce/modules/juce_core/threads/juce_ScopedWriteLock.h"
    "../../Vendor/juce/modules/juce_core/threads/juce_SpinLock.h"
    "../../Vendor/juce/modules/juce_core/threads/juce_Thread.cpp"
    "../../Vendor/juce/modules/juce_core/threads/juce_Thread.h"
    "../../Vendor/juce/modules/juce_core/threads/juce_ThreadLocalValue.h"
    "../../Vendor/juce/modules/juce_core/threads/juce_ThreadPool.cpp"
    "../../Vendor/juce/modules/juce_core/threads/juce_ThreadPool.h"
    "../../Vendor/juce/modules/juce_core/threads/juce_TimeSliceThread.cpp"
    "../../Vendor/juce/modules/juce_core/threads/juce_TimeSliceThread.h"
    "../../Vendor/juce/modules/juce_core/threads/juce_WaitableEvent.h"
    "../../Vendor/juce/modules/juce_core/time/juce_PerformanceCounter.cpp"
    "../../Vendor/juce/modules/juce_core/time/juce_PerformanceCounter.h"
    "../../Vendor/juce/modules/juce_core/time/juce_RelativeTime.cpp"
    "../../Vendor/juce/modules/juce_core/time/juce_RelativeTime.h"
    "../../Vendor/juce/modules/juce_core/time/juce_Time.cpp"
    "../../Vendor/juce/modules/juce_core/time/juce_Time.h"
    "../../Vendor/juce/modules/juce_core/unit_tests/juce_UnitTest.cpp"
    "../../Vendor/juce/modules/juce_core/unit_tests/juce_UnitTest.h"
    "../../Vendor/juce/modules/juce_core/xml/juce_XmlDocument.cpp"
    "../../Vendor/juce/modules/juce_core/xml/juce_XmlDocument.h"
    "../../Vendor/juce/modules/juce_core/xml/juce_XmlElement.cpp"
    "../../Vendor/juce/modules/juce_core/xml/juce_XmlElement.h"
    "../../Vendor/juce/modules/juce_core/zip/zlib/adler32.c"
    "../../Vendor/juce/modules/juce_core/zip/zlib/compress.c"
    "../../Vendor/juce/modules/juce_core/zip/zlib/crc32.c"
    "../../Vendor/juce/modules/juce_core/zip/zlib/crc32.h"
    "../../Vendor/juce/modules/juce_core/zip/zlib/deflate.c"
    "../../Vendor/juce/modules/juce_core/zip/zlib/deflate.h"
    "../../Vendor/juce/modules/juce_core/zip/zlib/infback.c"
    "../../Vendor/juce/modules/juce_core/zip/zlib/inffast.c"
    "../../Vendor/juce/modules/juce_core/zip/zlib/inffast.h"
    "../../Vendor/juce/modules/juce_core/zip/zlib/inffixed.h"
    "../../Vendor/juce/modules/juce_core/zip/zlib/inflate.c"
    "../../Vendor/juce/modules/juce_core/zip/zlib/inflate.h"
    "../../Vendor/juce/modules/juce_core/zip/zlib/inftrees.c"
    "../../Vendor/juce/modules/juce_core/zip/zlib/inftrees.h"
    "../../Vendor/juce/modules/juce_core/zip/zlib/trees.c"
    "../../Vendor/juce/modules/juce_core/zip/zlib/trees.h"
    "../../Vendor/juce/modules/juce_core/zip/zlib/uncompr.c"
    "../../Vendor/juce/modules/juce_core/zip/zlib/zconf.h"
    "../../Vendor/juce/modules/juce_core/zip/zlib/zconf.in.h"
    "../../Vendor/juce/modules/juce_core/zip/zlib/zlib.h"
    "../../Vendor/juce/modules/juce_core/zip/zlib/zutil.c"
    "../../Vendor/juce/modules/juce_core/zip/zlib/zutil.h"
    "../../Vendor/juce/modules/juce_core/zip/juce_GZIPCompressorOutputStream.cpp"
    "../../Vendor/juce/modules/juce_core/zip/juce_GZIPCompressorOutputStream.h"
    "../../Vendor/juce/modules/juce_core/zip/juce_GZIPDecompressorInputStream.cpp"
    "../../Vendor/juce/modules/juce_core/zip/juce_GZIPDecompressorInputStream.h"
    "../../Vendor/juce/modules/juce_core/zip/juce_ZipFile.cpp"
    "../../Vendor/juce/modules/juce_core/zip/juce_ZipFile.h"
    "../../Vendor/juce/modules/juce_core/juce_core.cpp"
    "../../Vendor/juce/modules/juce_core/juce_core.mm"
    "../../Vendor/juce/modules/juce_core/juce_core.h"
    "../../Vendor/juce/modules/juce_data_structures/app_properties/juce_ApplicationProperties.cpp"
    "../../Vendor/juce/modules/juce_data_structures/app_properties/juce_ApplicationProperties.h"
    "../../Vendor/juce/modules/juce_data_structures/app_properties/juce_PropertiesFile.cpp"
    "../../Vendor/juce/modules/juce_data_structures/app_properties/juce_PropertiesFile.h"
    "../../Vendor/juce/modules/juce_data_structures/undomanager/juce_UndoableAction.h"
    "../../Vendor/juce/modules/juce_data_structures/undomanager/juce_UndoManager.cpp"
    "../../Vendor/juce/modules/juce_data_structures/undomanager/juce_UndoManager.h"
    "../../Vendor/juce/modules/juce_data_structures/values/juce_CachedValue.cpp"
    "../../Vendor/juce/modules/juce_data_structures/values/juce_CachedValue.h"
    "../../Vendor/juce/modules/juce_data_structures/values/juce_Value.cpp"
    "../../Vendor/juce/modules/juce_data_structures/values/juce_Value.h"
    "../../Vendor/juce/modules/juce_data_structures/values/juce_ValueTree.cpp"
    "../../Vendor/juce/modules/juce_data_structures/values/juce_ValueTree.h"
    "../../Vendor/juce/modules/juce_data_structures/values/juce_ValueTreeSynchroniser.cpp"
    "../../Vendor/juce/modules/juce_data_structures/values/juce_ValueTreeSynchroniser.h"
    "../../Vendor/juce/modules/juce_data_structures/values/juce_ValueWithDefault.h"
    "../../Vendor/juce/modules/juce_data_structures/juce_data_structures.cpp"
    "../../Vendor/juce/modules/juce_data_structures/juce_data_structures.mm"
    "../../Vendor/juce/modules/juce_data_structures/juce_data_structures.h"
    "../../Vendor/juce/modules/juce_events/broadcasters/juce_ActionBroadcaster.cpp"
    "../../Vendor/juce/modules/juce_events/broadcasters/juce_ActionBroadcaster.h"
    "../../Vendor/juce/modules/juce_events/broadcasters/juce_ActionListener.h"
    "../../Vendor/juce/modules/juce_events/broadcasters/juce_AsyncUpdater.cpp"
    "../../Vendor/juce/modules/juce_events/broadcasters/juce_AsyncUpdater.h"
    "../../Vendor/juce/modules/juce_events/broadcasters/juce_ChangeBroadcaster.cpp"
    "../../Vendor/juce/modules/juce_events/broadcasters/juce_ChangeBroadcaster.h"
    "../../Vendor/juce/modules/juce_events/broadcasters/juce_ChangeListener.h"
    "../../Vendor/juce/modules/juce_events/interprocess/juce_ConnectedChildProcess.cpp"
    "../../Vendor/juce/modules/juce_events/interprocess/juce_ConnectedChildProcess.h"
    "../../Vendor/juce/modules/juce_events/interprocess/juce_InterprocessConnection.cpp"
    "../../Vendor/juce/modules/juce_events/interprocess/juce_InterprocessConnection.h"
    "../../Vendor/juce/modules/juce_events/interprocess/juce_InterprocessConnectionServer.cpp"
    "../../Vendor/juce/modules/juce_events/interprocess/juce_InterprocessConnectionServer.h"
    "../../Vendor/juce/modules/juce_events/messages/juce_ApplicationBase.cpp"
    "../../Vendor/juce/modules/juce_events/messages/juce_ApplicationBase.h"
    "../../Vendor/juce/modules/juce_events/messages/juce_CallbackMessage.h"
    "../../Vendor/juce/modules/juce_events/messages/juce_DeletedAtShutdown.cpp"
    "../../Vendor/juce/modules/juce_events/messages/juce_DeletedAtShutdown.h"
    "../../Vendor/juce/modules/juce_events/messages/juce_Initialisation.h"
    "../../Vendor/juce/modules/juce_events/messages/juce_Message.h"
    "../../Vendor/juce/modules/juce_events/messages/juce_MessageListener.cpp"
    "../../Vendor/juce/modules/juce_events/messages/juce_MessageListener.h"
    "../../Vendor/juce/modules/juce_events/messages/juce_MessageManager.cpp"
    "../../Vendor/juce/modules/juce_events/messages/juce_MessageManager.h"
    "../../Vendor/juce/modules/juce_events/messages/juce_MountedVolumeListChangeDetector.h"
    "../../Vendor/juce/modules/juce_events/messages/juce_NotificationType.h"
    "../../Vendor/juce/modules/juce_events/native/juce_android_Messaging.cpp"
    "../../Vendor/juce/modules/juce_events/native/juce_ios_MessageManager.mm"
    "../../Vendor/juce/modules/juce_events/native/juce_linux_EventLoop.h"
    "../../Vendor/juce/modules/juce_events/native/juce_linux_Messaging.cpp"
    "../../Vendor/juce/modules/juce_events/native/juce_mac_MessageManager.mm"
    "../../Vendor/juce/modules/juce_events/native/juce_osx_MessageQueue.h"
    "../../Vendor/juce/modules/juce_events/native/juce_win32_HiddenMessageWindow.h"
    "../../Vendor/juce/modules/juce_events/native/juce_win32_Messaging.cpp"
    "../../Vendor/juce/modules/juce_events/native/juce_win32_WinRTWrapper.cpp"
    "../../Vendor/juce/modules/juce_events/native/juce_win32_WinRTWrapper.h"
    "../../Vendor/juce/modules/juce_events/timers/juce_MultiTimer.cpp"
    "../../Vendor/juce/modules/juce_events/timers/juce_MultiTimer.h"
    "../../Vendor/juce/modules/juce_events/timers/juce_Timer.cpp"
    "../../Vendor/juce/modules/juce_events/timers/juce_Timer.h"
    "../../Vendor/juce/modules/juce_events/juce_events.cpp"
    "../../Vendor/juce/modules/juce_events/juce_events.mm"
    "../../Vendor/juce/modules/juce_events/juce_events.h"
    "../../Vendor/juce/modules/juce_graphics/colour/juce_Colour.cpp"
    "../../Vendor/juce/modules/juce_graphics/colour/juce_Colour.h"
    "../../Vendor/juce/modules/juce_graphics/colour/juce_ColourGradient.cpp"
    "../../Vendor/juce/modules/juce_graphics/colour/juce_ColourGradient.h"
    "../../Vendor/juce/modules/juce_graphics/colour/juce_Colours.cpp"
    "../../Vendor/juce/modules/juce_graphics/colour/juce_Colours.h"
    "../../Vendor/juce/modules/juce_graphics/colour/juce_FillType.cpp"
    "../../Vendor/juce/modules/juce_graphics/colour/juce_FillType.h"
    "../../Vendor/juce/modules/juce_graphics/colour/juce_PixelFormats.h"
    "../../Vendor/juce/modules/juce_graphics/contexts/juce_GraphicsContext.cpp"
    "../../Vendor/juce/modules/juce_graphics/contexts/juce_GraphicsContext.h"
    "../../Vendor/juce/modules/juce_graphics/contexts/juce_LowLevelGraphicsContext.h"
    "../../Vendor/juce/modules/juce_graphics/contexts/juce_LowLevelGraphicsPostScriptRenderer.cpp"
    "../../Vendor/juce/modules/juce_graphics/contexts/juce_LowLevelGraphicsPostScriptRenderer.h"
    "../../Vendor/juce/modules/juce_graphics/contexts/juce_LowLevelGraphicsSoftwareRenderer.cpp"
    "../../Vendor/juce/modules/juce_graphics/contexts/juce_LowLevelGraphicsSoftwareRenderer.h"
    "../../Vendor/juce/modules/juce_graphics/effects/juce_DropShadowEffect.cpp"
    "../../Vendor/juce/modules/juce_graphics/effects/juce_DropShadowEffect.h"
    "../../Vendor/juce/modules/juce_graphics/effects/juce_GlowEffect.cpp"
    "../../Vendor/juce/modules/juce_graphics/effects/juce_GlowEffect.h"
    "../../Vendor/juce/modules/juce_graphics/effects/juce_ImageEffectFilter.h"
    "../../Vendor/juce/modules/juce_graphics/fonts/juce_AttributedString.cpp"
    "../../Vendor/juce/modules/juce_graphics/fonts/juce_AttributedString.h"
    "../../Vendor/juce/modules/juce_graphics/fonts/juce_CustomTypeface.cpp"
    "../../Vendor/juce/modules/juce_graphics/fonts/juce_CustomTypeface.h"
    "../../Vendor/juce/modules/juce_graphics/fonts/juce_Font.cpp"
    "../../Vendor/juce/modules/juce_graphics/fonts/juce_Font.h"
    "../../Vendor/juce/modules/juce_graphics/fonts/juce_GlyphArrangement.cpp"
    "../../Vendor/juce/modules/juce_graphics/fonts/juce_GlyphArrangement.h"
    "../../Vendor/juce/modules/juce_graphics/fonts/juce_TextLayout.cpp"
    "../../Vendor/juce/modules/juce_graphics/fonts/juce_TextLayout.h"
    "../../Vendor/juce/modules/juce_graphics/fonts/juce_Typeface.cpp"
    "../../Vendor/juce/modules/juce_graphics/fonts/juce_Typeface.h"
    "../../Vendor/juce/modules/juce_graphics/geometry/juce_AffineTransform.cpp"
    "../../Vendor/juce/modules/juce_graphics/geometry/juce_AffineTransform.h"
    "../../Vendor/juce/modules/juce_graphics/geometry/juce_BorderSize.h"
    "../../Vendor/juce/modules/juce_graphics/geometry/juce_EdgeTable.cpp"
    "../../Vendor/juce/modules/juce_graphics/geometry/juce_EdgeTable.h"
    "../../Vendor/juce/modules/juce_graphics/geometry/juce_Line.h"
    "../../Vendor/juce/modules/juce_graphics/geometry/juce_Parallelogram.h"
    "../../Vendor/juce/modules/juce_graphics/geometry/juce_Path.cpp"
    "../../Vendor/juce/modules/juce_graphics/geometry/juce_Path.h"
    "../../Vendor/juce/modules/juce_graphics/geometry/juce_PathIterator.cpp"
    "../../Vendor/juce/modules/juce_graphics/geometry/juce_PathIterator.h"
    "../../Vendor/juce/modules/juce_graphics/geometry/juce_PathStrokeType.cpp"
    "../../Vendor/juce/modules/juce_graphics/geometry/juce_PathStrokeType.h"
    "../../Vendor/juce/modules/juce_graphics/geometry/juce_Point.h"
    "../../Vendor/juce/modules/juce_graphics/geometry/juce_Rectangle.h"
    "../../Vendor/juce/modules/juce_graphics/geometry/juce_RectangleList.h"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/cderror.h"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/changes to libjpeg for JUCE.txt"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcapimin.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcapistd.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jccoefct.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jccolor.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcdctmgr.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jchuff.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jchuff.h"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcinit.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcmainct.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcmarker.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcmaster.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcomapi.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jconfig.h"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcparam.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcphuff.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcprepct.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcsample.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jctrans.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdapimin.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdapistd.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdatasrc.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdcoefct.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdcolor.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdct.h"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jddctmgr.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdhuff.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdhuff.h"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdinput.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdmainct.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdmarker.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdmaster.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdmerge.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdphuff.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdpostct.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdsample.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdtrans.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jerror.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jerror.h"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jfdctflt.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jfdctfst.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jfdctint.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jidctflt.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jidctfst.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jidctint.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jidctred.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jinclude.h"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jmemmgr.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jmemnobs.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jmemsys.h"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jmorecfg.h"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jpegint.h"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jpeglib.h"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jquant1.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jquant2.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jutils.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jversion.h"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/transupp.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/transupp.h"
    "../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/libpng_readme.txt"
    "../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/png.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/png.h"
    "../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngconf.h"
    "../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngerror.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngget.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pnginfo.h"
    "../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngmem.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngpread.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngpriv.h"
    "../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngread.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngrio.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngrtran.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngrutil.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngset.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngstruct.h"
    "../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngtrans.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngwio.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngwrite.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngwtran.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngwutil.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/juce_GIFLoader.cpp"
    "../../Vendor/juce/modules/juce_graphics/image_formats/juce_JPEGLoader.cpp"
    "../../Vendor/juce/modules/juce_graphics/image_formats/juce_PNGLoader.cpp"
    "../../Vendor/juce/modules/juce_graphics/images/juce_Image.cpp"
    "../../Vendor/juce/modules/juce_graphics/images/juce_Image.h"
    "../../Vendor/juce/modules/juce_graphics/images/juce_ImageCache.cpp"
    "../../Vendor/juce/modules/juce_graphics/images/juce_ImageCache.h"
    "../../Vendor/juce/modules/juce_graphics/images/juce_ImageConvolutionKernel.cpp"
    "../../Vendor/juce/modules/juce_graphics/images/juce_ImageConvolutionKernel.h"
    "../../Vendor/juce/modules/juce_graphics/images/juce_ImageFileFormat.cpp"
    "../../Vendor/juce/modules/juce_graphics/images/juce_ImageFileFormat.h"
    "../../Vendor/juce/modules/juce_graphics/native/juce_android_Fonts.cpp"
    "../../Vendor/juce/modules/juce_graphics/native/juce_android_GraphicsContext.cpp"
    "../../Vendor/juce/modules/juce_graphics/native/juce_android_IconHelpers.cpp"
    "../../Vendor/juce/modules/juce_graphics/native/juce_freetype_Fonts.cpp"
    "../../Vendor/juce/modules/juce_graphics/native/juce_linux_Fonts.cpp"
    "../../Vendor/juce/modules/juce_graphics/native/juce_linux_IconHelpers.cpp"
    "../../Vendor/juce/modules/juce_graphics/native/juce_mac_CoreGraphicsContext.h"
    "../../Vendor/juce/modules/juce_graphics/native/juce_mac_CoreGraphicsContext.mm"
    "../../Vendor/juce/modules/juce_graphics/native/juce_mac_CoreGraphicsHelpers.h"
    "../../Vendor/juce/modules/juce_graphics/native/juce_mac_Fonts.mm"
    "../../Vendor/juce/modules/juce_graphics/native/juce_mac_IconHelpers.cpp"
    "../../Vendor/juce/modules/juce_graphics/native/juce_RenderingHelpers.h"
    "../../Vendor/juce/modules/juce_graphics/native/juce_win32_Direct2DGraphicsContext.cpp"
    "../../Vendor/juce/modules/juce_graphics/native/juce_win32_Direct2DGraphicsContext.h"
    "../../Vendor/juce/modules/juce_graphics/native/juce_win32_DirectWriteTypeface.cpp"
    "../../Vendor/juce/modules/juce_graphics/native/juce_win32_DirectWriteTypeLayout.cpp"
    "../../Vendor/juce/modules/juce_graphics/native/juce_win32_Fonts.cpp"
    "../../Vendor/juce/modules/juce_graphics/native/juce_win32_IconHelpers.cpp"
    "../../Vendor/juce/modules/juce_graphics/placement/juce_Justification.h"
    "../../Vendor/juce/modules/juce_graphics/placement/juce_RectanglePlacement.cpp"
    "../../Vendor/juce/modules/juce_graphics/placement/juce_RectanglePlacement.h"
    "../../Vendor/juce/modules/juce_graphics/juce_graphics.cpp"
    "../../Vendor/juce/modules/juce_graphics/juce_graphics.mm"
    "../../Vendor/juce/modules/juce_graphics/juce_graphics.h"
    "../../Vendor/juce/modules/juce_gui_basics/application/juce_Application.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/application/juce_Application.h"
    "../../Vendor/juce/modules/juce_gui_basics/buttons/juce_ArrowButton.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/buttons/juce_ArrowButton.h"
    "../../Vendor/juce/modules/juce_gui_basics/buttons/juce_Button.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/buttons/juce_Button.h"
    "../../Vendor/juce/modules/juce_gui_basics/buttons/juce_DrawableButton.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/buttons/juce_DrawableButton.h"
    "../../Vendor/juce/modules/juce_gui_basics/buttons/juce_HyperlinkButton.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/buttons/juce_HyperlinkButton.h"
    "../../Vendor/juce/modules/juce_gui_basics/buttons/juce_ImageButton.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/buttons/juce_ImageButton.h"
    "../../Vendor/juce/modules/juce_gui_basics/buttons/juce_ShapeButton.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/buttons/juce_ShapeButton.h"
    "../../Vendor/juce/modules/juce_gui_basics/buttons/juce_TextButton.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/buttons/juce_TextButton.h"
    "../../Vendor/juce/modules/juce_gui_basics/buttons/juce_ToggleButton.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/buttons/juce_ToggleButton.h"
    "../../Vendor/juce/modules/juce_gui_basics/buttons/juce_ToolbarButton.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/buttons/juce_ToolbarButton.h"
    "../../Vendor/juce/modules/juce_gui_basics/commands/juce_ApplicationCommandID.h"
    "../../Vendor/juce/modules/juce_gui_basics/commands/juce_ApplicationCommandInfo.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/commands/juce_ApplicationCommandInfo.h"
    "../../Vendor/juce/modules/juce_gui_basics/commands/juce_ApplicationCommandManager.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/commands/juce_ApplicationCommandManager.h"
    "../../Vendor/juce/modules/juce_gui_basics/commands/juce_ApplicationCommandTarget.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/commands/juce_ApplicationCommandTarget.h"
    "../../Vendor/juce/modules/juce_gui_basics/commands/juce_KeyPressMappingSet.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/commands/juce_KeyPressMappingSet.h"
    "../../Vendor/juce/modules/juce_gui_basics/components/juce_CachedComponentImage.h"
    "../../Vendor/juce/modules/juce_gui_basics/components/juce_Component.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/components/juce_Component.h"
    "../../Vendor/juce/modules/juce_gui_basics/components/juce_ComponentListener.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/components/juce_ComponentListener.h"
    "../../Vendor/juce/modules/juce_gui_basics/components/juce_Desktop.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/components/juce_Desktop.h"
    "../../Vendor/juce/modules/juce_gui_basics/components/juce_ModalComponentManager.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/components/juce_ModalComponentManager.h"
    "../../Vendor/juce/modules/juce_gui_basics/drawables/juce_Drawable.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/drawables/juce_Drawable.h"
    "../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawableComposite.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawableComposite.h"
    "../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawableImage.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawableImage.h"
    "../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawablePath.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawablePath.h"
    "../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawableRectangle.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawableRectangle.h"
    "../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawableShape.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawableShape.h"
    "../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawableText.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawableText.h"
    "../../Vendor/juce/modules/juce_gui_basics/drawables/juce_SVGParser.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_ContentSharer.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_ContentSharer.h"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_DirectoryContentsDisplayComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_DirectoryContentsDisplayComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_DirectoryContentsList.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_DirectoryContentsList.h"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileBrowserComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileBrowserComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileBrowserListener.h"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileChooser.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileChooser.h"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileChooserDialogBox.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileChooserDialogBox.h"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileListComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileListComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FilenameComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FilenameComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FilePreviewComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileSearchPathListComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileSearchPathListComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileTreeComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileTreeComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_ImagePreviewComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_ImagePreviewComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_CaretComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_CaretComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_KeyboardFocusTraverser.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_KeyboardFocusTraverser.h"
    "../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_KeyListener.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_KeyListener.h"
    "../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_KeyPress.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_KeyPress.h"
    "../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_ModifierKeys.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_ModifierKeys.h"
    "../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_SystemClipboard.h"
    "../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_TextEditorKeyMapper.h"
    "../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_TextInputTarget.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_AnimatedPosition.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_AnimatedPositionBehaviours.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_ComponentAnimator.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_ComponentAnimator.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_ComponentBoundsConstrainer.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_ComponentBoundsConstrainer.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_ComponentBuilder.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_ComponentBuilder.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_ComponentMovementWatcher.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_ComponentMovementWatcher.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_ConcertinaPanel.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_ConcertinaPanel.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_FlexBox.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_FlexBox.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_FlexItem.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_Grid.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_Grid.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_GridItem.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_GridItem.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_GridUnitTests.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_GroupComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_GroupComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_MultiDocumentPanel.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_MultiDocumentPanel.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_ResizableBorderComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_ResizableBorderComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_ResizableCornerComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_ResizableCornerComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_ResizableEdgeComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_ResizableEdgeComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_ScrollBar.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_ScrollBar.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_SidePanel.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_SidePanel.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_StretchableLayoutManager.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_StretchableLayoutManager.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_StretchableLayoutResizerBar.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_StretchableLayoutResizerBar.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_StretchableObjectResizer.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_StretchableObjectResizer.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_TabbedButtonBar.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_TabbedButtonBar.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_TabbedComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_TabbedComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_Viewport.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_Viewport.h"
    "../../Vendor/juce/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel.h"
    "../../Vendor/juce/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V1.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V1.h"
    "../../Vendor/juce/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V2.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V2.h"
    "../../Vendor/juce/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V3.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V3.h"
    "../../Vendor/juce/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V4.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V4.h"
    "../../Vendor/juce/modules/juce_gui_basics/menus/juce_BurgerMenuComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/menus/juce_BurgerMenuComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/menus/juce_MenuBarComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/menus/juce_MenuBarComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/menus/juce_MenuBarModel.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/menus/juce_MenuBarModel.h"
    "../../Vendor/juce/modules/juce_gui_basics/menus/juce_PopupMenu.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/menus/juce_PopupMenu.h"
    "../../Vendor/juce/modules/juce_gui_basics/misc/juce_BubbleComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/misc/juce_BubbleComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/misc/juce_DropShadower.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/misc/juce_DropShadower.h"
    "../../Vendor/juce/modules/juce_gui_basics/misc/juce_JUCESplashScreen.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/misc/juce_JUCESplashScreen.h"
    "../../Vendor/juce/modules/juce_gui_basics/mouse/juce_ComponentDragger.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/mouse/juce_ComponentDragger.h"
    "../../Vendor/juce/modules/juce_gui_basics/mouse/juce_DragAndDropContainer.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/mouse/juce_DragAndDropContainer.h"
    "../../Vendor/juce/modules/juce_gui_basics/mouse/juce_DragAndDropTarget.h"
    "../../Vendor/juce/modules/juce_gui_basics/mouse/juce_FileDragAndDropTarget.h"
    "../../Vendor/juce/modules/juce_gui_basics/mouse/juce_LassoComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/mouse/juce_MouseCursor.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/mouse/juce_MouseCursor.h"
    "../../Vendor/juce/modules/juce_gui_basics/mouse/juce_MouseEvent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/mouse/juce_MouseEvent.h"
    "../../Vendor/juce/modules/juce_gui_basics/mouse/juce_MouseInactivityDetector.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/mouse/juce_MouseInactivityDetector.h"
    "../../Vendor/juce/modules/juce_gui_basics/mouse/juce_MouseInputSource.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/mouse/juce_MouseInputSource.h"
    "../../Vendor/juce/modules/juce_gui_basics/mouse/juce_MouseListener.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/mouse/juce_MouseListener.h"
    "../../Vendor/juce/modules/juce_gui_basics/mouse/juce_SelectedItemSet.h"
    "../../Vendor/juce/modules/juce_gui_basics/mouse/juce_TextDragAndDropTarget.h"
    "../../Vendor/juce/modules/juce_gui_basics/mouse/juce_TooltipClient.h"
    "../../Vendor/juce/modules/juce_gui_basics/native/juce_android_ContentSharer.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/native/juce_android_FileChooser.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/native/juce_android_Windowing.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/native/juce_common_MimeTypes.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/native/juce_ios_ContentSharer.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/native/juce_ios_FileChooser.mm"
    "../../Vendor/juce/modules/juce_gui_basics/native/juce_ios_UIViewComponentPeer.mm"
    "../../Vendor/juce/modules/juce_gui_basics/native/juce_ios_Windowing.mm"
    "../../Vendor/juce/modules/juce_gui_basics/native/juce_linux_FileChooser.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/native/juce_linux_X11.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/native/juce_linux_X11.h"
    "../../Vendor/juce/modules/juce_gui_basics/native/juce_linux_X11_Clipboard.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/native/juce_linux_X11_Windowing.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/native/juce_mac_FileChooser.mm"
    "../../Vendor/juce/modules/juce_gui_basics/native/juce_mac_MainMenu.mm"
    "../../Vendor/juce/modules/juce_gui_basics/native/juce_mac_MouseCursor.mm"
    "../../Vendor/juce/modules/juce_gui_basics/native/juce_mac_NSViewComponentPeer.mm"
    "../../Vendor/juce/modules/juce_gui_basics/native/juce_mac_Windowing.mm"
    "../../Vendor/juce/modules/juce_gui_basics/native/juce_MultiTouchMapper.h"
    "../../Vendor/juce/modules/juce_gui_basics/native/juce_win32_DragAndDrop.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/native/juce_win32_FileChooser.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/native/juce_win32_Windowing.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/positioning/juce_MarkerList.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/positioning/juce_MarkerList.h"
    "../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativeCoordinate.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativeCoordinate.h"
    "../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativeCoordinatePositioner.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativeCoordinatePositioner.h"
    "../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativeParallelogram.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativeParallelogram.h"
    "../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativePoint.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativePoint.h"
    "../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativePointPath.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativePointPath.h"
    "../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativeRectangle.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativeRectangle.h"
    "../../Vendor/juce/modules/juce_gui_basics/properties/juce_BooleanPropertyComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/properties/juce_BooleanPropertyComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/properties/juce_ButtonPropertyComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/properties/juce_ButtonPropertyComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/properties/juce_ChoicePropertyComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/properties/juce_ChoicePropertyComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/properties/juce_MultiChoicePropertyComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/properties/juce_MultiChoicePropertyComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/properties/juce_PropertyComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/properties/juce_PropertyComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/properties/juce_PropertyPanel.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/properties/juce_PropertyPanel.h"
    "../../Vendor/juce/modules/juce_gui_basics/properties/juce_SliderPropertyComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/properties/juce_SliderPropertyComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/properties/juce_TextPropertyComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/properties/juce_TextPropertyComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ComboBox.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ComboBox.h"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ImageComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ImageComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_Label.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_Label.h"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ListBox.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ListBox.h"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ProgressBar.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ProgressBar.h"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_Slider.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_Slider.h"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_TableHeaderComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_TableHeaderComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_TableListBox.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_TableListBox.h"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_TextEditor.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_TextEditor.h"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_Toolbar.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_Toolbar.h"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ToolbarItemComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ToolbarItemComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ToolbarItemFactory.h"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ToolbarItemPalette.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ToolbarItemPalette.h"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_TreeView.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_TreeView.h"
    "../../Vendor/juce/modules/juce_gui_basics/windows/juce_AlertWindow.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/windows/juce_AlertWindow.h"
    "../../Vendor/juce/modules/juce_gui_basics/windows/juce_CallOutBox.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/windows/juce_CallOutBox.h"
    "../../Vendor/juce/modules/juce_gui_basics/windows/juce_ComponentPeer.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/windows/juce_ComponentPeer.h"
    "../../Vendor/juce/modules/juce_gui_basics/windows/juce_DialogWindow.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/windows/juce_DialogWindow.h"
    "../../Vendor/juce/modules/juce_gui_basics/windows/juce_DocumentWindow.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/windows/juce_DocumentWindow.h"
    "../../Vendor/juce/modules/juce_gui_basics/windows/juce_NativeMessageBox.h"
    "../../Vendor/juce/modules/juce_gui_basics/windows/juce_ResizableWindow.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/windows/juce_ResizableWindow.h"
    "../../Vendor/juce/modules/juce_gui_basics/windows/juce_ThreadWithProgressWindow.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/windows/juce_ThreadWithProgressWindow.h"
    "../../Vendor/juce/modules/juce_gui_basics/windows/juce_TooltipWindow.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/windows/juce_TooltipWindow.h"
    "../../Vendor/juce/modules/juce_gui_basics/windows/juce_TopLevelWindow.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/windows/juce_TopLevelWindow.h"
    "../../Vendor/juce/modules/juce_gui_basics/juce_gui_basics.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/juce_gui_basics.mm"
    "../../Vendor/juce/modules/juce_gui_basics/juce_gui_basics.h"
    "../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_CodeDocument.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_CodeDocument.h"
    "../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_CodeEditorComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_CodeEditorComponent.h"
    "../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_CodeTokeniser.h"
    "../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_CPlusPlusCodeTokeniser.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_CPlusPlusCodeTokeniser.h"
    "../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_CPlusPlusCodeTokeniserFunctions.h"
    "../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_LuaCodeTokeniser.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_LuaCodeTokeniser.h"
    "../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_XMLCodeTokeniser.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_XMLCodeTokeniser.h"
    "../../Vendor/juce/modules/juce_gui_extra/documents/juce_FileBasedDocument.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/documents/juce_FileBasedDocument.h"
    "../../Vendor/juce/modules/juce_gui_extra/embedding/juce_ActiveXControlComponent.h"
    "../../Vendor/juce/modules/juce_gui_extra/embedding/juce_AndroidViewComponent.h"
    "../../Vendor/juce/modules/juce_gui_extra/embedding/juce_NSViewComponent.h"
    "../../Vendor/juce/modules/juce_gui_extra/embedding/juce_UIViewComponent.h"
    "../../Vendor/juce/modules/juce_gui_extra/embedding/juce_XEmbedComponent.h"
    "../../Vendor/juce/modules/juce_gui_extra/misc/juce_AnimatedAppComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/misc/juce_AnimatedAppComponent.h"
    "../../Vendor/juce/modules/juce_gui_extra/misc/juce_AppleRemote.h"
    "../../Vendor/juce/modules/juce_gui_extra/misc/juce_BubbleMessageComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/misc/juce_BubbleMessageComponent.h"
    "../../Vendor/juce/modules/juce_gui_extra/misc/juce_ColourSelector.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/misc/juce_ColourSelector.h"
    "../../Vendor/juce/modules/juce_gui_extra/misc/juce_KeyMappingEditorComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/misc/juce_KeyMappingEditorComponent.h"
    "../../Vendor/juce/modules/juce_gui_extra/misc/juce_LiveConstantEditor.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/misc/juce_LiveConstantEditor.h"
    "../../Vendor/juce/modules/juce_gui_extra/misc/juce_PreferencesPanel.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/misc/juce_PreferencesPanel.h"
    "../../Vendor/juce/modules/juce_gui_extra/misc/juce_PushNotifications.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/misc/juce_PushNotifications.h"
    "../../Vendor/juce/modules/juce_gui_extra/misc/juce_RecentlyOpenedFilesList.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/misc/juce_RecentlyOpenedFilesList.h"
    "../../Vendor/juce/modules/juce_gui_extra/misc/juce_SplashScreen.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/misc/juce_SplashScreen.h"
    "../../Vendor/juce/modules/juce_gui_extra/misc/juce_SystemTrayIconComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/misc/juce_SystemTrayIconComponent.h"
    "../../Vendor/juce/modules/juce_gui_extra/misc/juce_WebBrowserComponent.h"
    "../../Vendor/juce/modules/juce_gui_extra/native/juce_android_PushNotifications.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/native/juce_android_WebBrowserComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/native/juce_AndroidViewComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/native/juce_ios_PushNotifications.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/native/juce_ios_UIViewComponent.mm"
    "../../Vendor/juce/modules/juce_gui_extra/native/juce_linux_X11_SystemTrayIcon.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/native/juce_linux_X11_WebBrowserComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/native/juce_linux_XEmbedComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/native/juce_mac_AppleRemote.mm"
    "../../Vendor/juce/modules/juce_gui_extra/native/juce_mac_CarbonViewWrapperComponent.h"
    "../../Vendor/juce/modules/juce_gui_extra/native/juce_mac_NSViewComponent.mm"
    "../../Vendor/juce/modules/juce_gui_extra/native/juce_mac_PushNotifications.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/native/juce_mac_SystemTrayIcon.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/native/juce_mac_WebBrowserComponent.mm"
    "../../Vendor/juce/modules/juce_gui_extra/native/juce_win32_ActiveXComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/native/juce_win32_SystemTrayIcon.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/native/juce_win32_WebBrowserComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/juce_gui_extra.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/juce_gui_extra.mm"
    "../../Vendor/juce/modules/juce_gui_extra/juce_gui_extra.h"
    "../../JuceLibraryCode/AppConfig.h"
    "../../JuceLibraryCode/include_juce_audio_basics.cpp"
    "../../JuceLibraryCode/include_juce_audio_plugin_client_utils.cpp"
    "../../JuceLibraryCode/include_juce_audio_processors.cpp"
    "../../JuceLibraryCode/include_juce_core.cpp"
    "../../JuceLibraryCode/include_juce_data_structures.cpp"
    "../../JuceLibraryCode/include_juce_events.cpp"
    "../../JuceLibraryCode/include_juce_graphics.cpp"
    "../../JuceLibraryCode/include_juce_gui_basics.cpp"
    "../../JuceLibraryCode/include_juce_gui_extra.cpp"
    "../../JuceLibraryCode/JuceHeader.h"
)

set_source_files_properties ("../../Source/editor/MainEditor.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Source/util/PatternUtil.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Source/ArpEvent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Source/ArpIntegrityException.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Source/ArpNote.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Source/ArpPattern.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Source/LibreArp.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Source/NoteData.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/audio_play_head/juce_AudioPlayHead.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/buffers/juce_AudioChannelSet.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/buffers/juce_AudioChannelSet.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/buffers/juce_AudioDataConverters.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/buffers/juce_AudioDataConverters.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/buffers/juce_AudioSampleBuffer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/buffers/juce_FloatVectorOperations.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/buffers/juce_FloatVectorOperations.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/effects/juce_CatmullRomInterpolator.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/effects/juce_CatmullRomInterpolator.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/effects/juce_Decibels.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/effects/juce_IIRFilter.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/effects/juce_IIRFilter.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/effects/juce_LagrangeInterpolator.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/effects/juce_LagrangeInterpolator.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/effects/juce_LinearSmoothedValue.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/effects/juce_Reverb.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiBuffer.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiBuffer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiFile.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiFile.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiKeyboardState.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiKeyboardState.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiMessage.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiMessage.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiMessageSequence.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiMessageSequence.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiRPN.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiRPN.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPEInstrument.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPEInstrument.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPEMessages.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPEMessages.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPENote.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPENote.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPESynthesiser.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPESynthesiser.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPESynthesiserBase.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPESynthesiserBase.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPESynthesiserVoice.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPESynthesiserVoice.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPEUtils.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPEUtils.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPEValue.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPEValue.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPEZoneLayout.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPEZoneLayout.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/native/juce_mac_CoreAudioLayouts.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/sources/juce_AudioSource.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/sources/juce_BufferingAudioSource.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/sources/juce_BufferingAudioSource.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/sources/juce_ChannelRemappingAudioSource.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/sources/juce_ChannelRemappingAudioSource.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/sources/juce_IIRFilterAudioSource.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/sources/juce_IIRFilterAudioSource.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/sources/juce_MemoryAudioSource.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/sources/juce_MemoryAudioSource.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/sources/juce_MixerAudioSource.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/sources/juce_MixerAudioSource.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/sources/juce_PositionableAudioSource.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/sources/juce_ResamplingAudioSource.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/sources/juce_ResamplingAudioSource.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/sources/juce_ReverbAudioSource.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/sources/juce_ReverbAudioSource.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/sources/juce_ToneGeneratorAudioSource.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/sources/juce_ToneGeneratorAudioSource.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/synthesisers/juce_Synthesiser.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/synthesisers/juce_Synthesiser.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/juce_audio_basics.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/juce_audio_basics.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/juce_audio_basics.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUBase.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUBase.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUBaseHelper.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUBuffer.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUBuffer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUCarbonViewBase.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUCarbonViewBase.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUCarbonViewControl.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUCarbonViewControl.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUCarbonViewDispatch.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUDispatch.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUDispatch.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUInputElement.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUInputElement.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUInputFormatConverter.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUMIDIBase.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUMIDIBase.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUOutputBase.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUOutputBase.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUOutputElement.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUOutputElement.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUPlugInDispatch.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUPlugInDispatch.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUScopeElement.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUScopeElement.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUSilentTimeout.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUTimestampGenerator.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUViewLocalizedStringKeys.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAAtomic.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAAtomicStack.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAAudioChannelLayout.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAAudioChannelLayout.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAAUParameter.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAAUParameter.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAAutoDisposer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CADebugMacros.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CADebugPrintf.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAException.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAHostTimeBase.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAMath.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAMutex.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAMutex.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CarbonEventHandler.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CarbonEventHandler.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAReferenceCounted.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAStreamBasicDescription.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAStreamBasicDescription.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAThreadSafeList.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAVectorUnit.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAVectorUnit.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAVectorUnitTypes.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAXException.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/ComponentBase.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/ComponentBase.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/MusicDeviceBase.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/MusicDeviceBase.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/Standalone/juce_StandaloneFilterApp.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/Standalone/juce_StandaloneFilterWindow.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/utility/juce_CarbonVisibility.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/utility/juce_CheckSettingMacros.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/utility/juce_FakeMouseMoveGenerator.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/utility/juce_IncludeModuleHeaders.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/utility/juce_IncludeSystemHeaders.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/utility/juce_PluginHostType.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/utility/juce_PluginUtilities.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/utility/juce_WindowsHooks.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/VST/juce_VST_Wrapper.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/VST/juce_VST_Wrapper.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/VST/juce_VSTCallbackHandler.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/juce_audio_plugin_client_utils.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/juce_audio_plugin_client_VST_utils.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/juce_audio_plugin_client.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/format/juce_AudioPluginFormat.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/format/juce_AudioPluginFormat.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/format/juce_AudioPluginFormatManager.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/format/juce_AudioPluginFormatManager.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/format_types/juce_AudioUnitPluginFormat.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/format_types/juce_AudioUnitPluginFormat.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/format_types/juce_LADSPAPluginFormat.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/format_types/juce_LADSPAPluginFormat.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/format_types/juce_LegacyAudioParameter.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/format_types/juce_VST3Common.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/format_types/juce_VST3Headers.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/format_types/juce_VST3PluginFormat.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/format_types/juce_VST3PluginFormat.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/format_types/juce_VSTCommon.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/format_types/juce_VSTInterface.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/format_types/juce_VSTMidiEventList.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/format_types/juce_VSTPluginFormat.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/format_types/juce_VSTPluginFormat.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/processors/juce_AudioPluginInstance.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/processors/juce_AudioPluginInstance.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/processors/juce_AudioProcessor.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/processors/juce_AudioProcessor.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/processors/juce_AudioProcessorEditor.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/processors/juce_AudioProcessorEditor.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/processors/juce_AudioProcessorGraph.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/processors/juce_AudioProcessorGraph.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/processors/juce_AudioProcessorListener.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/processors/juce_AudioProcessorParameter.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/processors/juce_GenericAudioProcessorEditor.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/processors/juce_GenericAudioProcessorEditor.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/processors/juce_PluginDescription.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/processors/juce_PluginDescription.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/scanning/juce_KnownPluginList.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/scanning/juce_KnownPluginList.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/scanning/juce_PluginDirectoryScanner.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/scanning/juce_PluginDirectoryScanner.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/scanning/juce_PluginListComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/scanning/juce_PluginListComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/utilities/juce_AudioParameterBool.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/utilities/juce_AudioParameterChoice.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/utilities/juce_AudioParameterFloat.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/utilities/juce_AudioParameterInt.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/utilities/juce_AudioProcessorParameters.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/utilities/juce_AudioProcessorParameterWithID.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/utilities/juce_AudioProcessorValueTreeState.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/utilities/juce_AudioProcessorValueTreeState.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/juce_audio_processors.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/juce_audio_processors.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/juce_audio_processors.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/containers/juce_AbstractFifo.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/containers/juce_AbstractFifo.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/containers/juce_Array.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/containers/juce_ArrayAllocationBase.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/containers/juce_DynamicObject.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/containers/juce_DynamicObject.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/containers/juce_ElementComparator.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/containers/juce_HashMap.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/containers/juce_HashMap_test.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/containers/juce_LinkedListPointer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/containers/juce_ListenerList.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/containers/juce_NamedValueSet.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/containers/juce_NamedValueSet.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/containers/juce_OwnedArray.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/containers/juce_PropertySet.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/containers/juce_PropertySet.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/containers/juce_ReferenceCountedArray.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/containers/juce_ScopedValueSetter.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/containers/juce_SortedSet.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/containers/juce_SparseSet.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/containers/juce_SparseSet.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/containers/juce_Variant.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/containers/juce_Variant.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/files/juce_DirectoryIterator.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/files/juce_DirectoryIterator.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/files/juce_File.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/files/juce_File.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/files/juce_FileFilter.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/files/juce_FileFilter.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/files/juce_FileInputStream.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/files/juce_FileInputStream.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/files/juce_FileOutputStream.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/files/juce_FileOutputStream.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/files/juce_FileSearchPath.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/files/juce_FileSearchPath.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/files/juce_MemoryMappedFile.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/files/juce_TemporaryFile.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/files/juce_TemporaryFile.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/files/juce_WildcardFileFilter.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/files/juce_WildcardFileFilter.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/javascript/juce_Javascript.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/javascript/juce_Javascript.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/javascript/juce_JSON.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/javascript/juce_JSON.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/logging/juce_FileLogger.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/logging/juce_FileLogger.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/logging/juce_Logger.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/logging/juce_Logger.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/maths/juce_BigInteger.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/maths/juce_BigInteger.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/maths/juce_Expression.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/maths/juce_Expression.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/maths/juce_MathsFunctions.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/maths/juce_NormalisableRange.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/maths/juce_Random.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/maths/juce_Random.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/maths/juce_Range.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/maths/juce_StatisticsAccumulator.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/memory/juce_Atomic.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/memory/juce_ByteOrder.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/memory/juce_ContainerDeletePolicy.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/memory/juce_HeapBlock.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/memory/juce_LeakedObjectDetector.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/memory/juce_Memory.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/memory/juce_MemoryBlock.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/memory/juce_MemoryBlock.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/memory/juce_OptionalScopedPointer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/memory/juce_ReferenceCountedObject.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/memory/juce_ScopedPointer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/memory/juce_SharedResourcePointer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/memory/juce_Singleton.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/memory/juce_WeakReference.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/misc/juce_Result.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/misc/juce_Result.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/misc/juce_RuntimePermissions.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/misc/juce_RuntimePermissions.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/misc/juce_StdFunctionCompat.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/misc/juce_StdFunctionCompat.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/misc/juce_Uuid.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/misc/juce_Uuid.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/misc/juce_WindowsRegistry.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_android_Files.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_android_JNIHelpers.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_android_Misc.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_android_Network.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_android_RuntimePermissions.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_android_SystemStats.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_android_Threads.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_BasicNativeHeaders.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_curl_Network.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_linux_CommonFile.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_linux_Files.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_linux_Network.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_linux_SystemStats.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_linux_Threads.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_mac_ClangBugWorkaround.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_mac_Files.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_mac_Network.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_mac_Strings.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_mac_SystemStats.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_mac_Threads.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_osx_ObjCHelpers.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_posix_NamedPipe.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_posix_SharedCode.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_win32_ComSmartPtr.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_win32_Files.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_win32_Network.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_win32_Registry.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_win32_SystemStats.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_win32_Threads.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/network/juce_IPAddress.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/network/juce_IPAddress.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/network/juce_MACAddress.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/network/juce_MACAddress.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/network/juce_NamedPipe.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/network/juce_NamedPipe.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/network/juce_Socket.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/network/juce_Socket.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/network/juce_URL.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/network/juce_URL.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/network/juce_WebInputStream.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/network/juce_WebInputStream.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/streams/juce_BufferedInputStream.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/streams/juce_BufferedInputStream.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/streams/juce_FileInputSource.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/streams/juce_FileInputSource.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/streams/juce_InputSource.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/streams/juce_InputStream.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/streams/juce_InputStream.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/streams/juce_MemoryInputStream.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/streams/juce_MemoryInputStream.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/streams/juce_MemoryOutputStream.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/streams/juce_MemoryOutputStream.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/streams/juce_OutputStream.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/streams/juce_OutputStream.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/streams/juce_SubregionStream.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/streams/juce_SubregionStream.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/streams/juce_URLInputSource.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/streams/juce_URLInputSource.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/system/juce_CompilerSupport.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/system/juce_PlatformDefs.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/system/juce_StandardHeader.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/system/juce_SystemStats.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/system/juce_SystemStats.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/system/juce_TargetPlatform.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_Base64.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_Base64.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_CharacterFunctions.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_CharacterFunctions.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_CharPointer_ASCII.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_CharPointer_UTF8.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_CharPointer_UTF16.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_CharPointer_UTF32.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_Identifier.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_Identifier.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_LocalisedStrings.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_LocalisedStrings.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_NewLine.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_String.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_String.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_StringArray.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_StringArray.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_StringPairArray.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_StringPairArray.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_StringPool.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_StringPool.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_StringRef.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_TextDiff.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_TextDiff.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/threads/juce_ChildProcess.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/threads/juce_ChildProcess.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/threads/juce_CriticalSection.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/threads/juce_DynamicLibrary.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/threads/juce_HighResolutionTimer.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/threads/juce_HighResolutionTimer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/threads/juce_InterProcessLock.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/threads/juce_Process.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/threads/juce_ReadWriteLock.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/threads/juce_ReadWriteLock.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/threads/juce_ScopedLock.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/threads/juce_ScopedReadLock.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/threads/juce_ScopedWriteLock.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/threads/juce_SpinLock.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/threads/juce_Thread.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/threads/juce_Thread.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/threads/juce_ThreadLocalValue.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/threads/juce_ThreadPool.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/threads/juce_ThreadPool.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/threads/juce_TimeSliceThread.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/threads/juce_TimeSliceThread.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/threads/juce_WaitableEvent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/time/juce_PerformanceCounter.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/time/juce_PerformanceCounter.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/time/juce_RelativeTime.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/time/juce_RelativeTime.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/time/juce_Time.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/time/juce_Time.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/unit_tests/juce_UnitTest.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/unit_tests/juce_UnitTest.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/xml/juce_XmlDocument.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/xml/juce_XmlDocument.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/xml/juce_XmlElement.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/xml/juce_XmlElement.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/zlib/adler32.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/zlib/compress.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/zlib/crc32.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/zlib/crc32.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/zlib/deflate.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/zlib/deflate.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/zlib/infback.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/zlib/inffast.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/zlib/inffast.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/zlib/inffixed.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/zlib/inflate.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/zlib/inflate.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/zlib/inftrees.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/zlib/inftrees.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/zlib/trees.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/zlib/trees.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/zlib/uncompr.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/zlib/zconf.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/zlib/zconf.in.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/zlib/zlib.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/zlib/zutil.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/zlib/zutil.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/juce_GZIPCompressorOutputStream.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/juce_GZIPCompressorOutputStream.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/juce_GZIPDecompressorInputStream.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/juce_GZIPDecompressorInputStream.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/juce_ZipFile.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/juce_ZipFile.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/juce_core.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/juce_core.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/juce_core.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_data_structures/app_properties/juce_ApplicationProperties.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_data_structures/app_properties/juce_ApplicationProperties.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_data_structures/app_properties/juce_PropertiesFile.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_data_structures/app_properties/juce_PropertiesFile.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_data_structures/undomanager/juce_UndoableAction.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_data_structures/undomanager/juce_UndoManager.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_data_structures/undomanager/juce_UndoManager.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_data_structures/values/juce_CachedValue.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_data_structures/values/juce_CachedValue.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_data_structures/values/juce_Value.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_data_structures/values/juce_Value.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_data_structures/values/juce_ValueTree.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_data_structures/values/juce_ValueTree.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_data_structures/values/juce_ValueTreeSynchroniser.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_data_structures/values/juce_ValueTreeSynchroniser.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_data_structures/values/juce_ValueWithDefault.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_data_structures/juce_data_structures.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_data_structures/juce_data_structures.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_data_structures/juce_data_structures.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/broadcasters/juce_ActionBroadcaster.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/broadcasters/juce_ActionBroadcaster.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/broadcasters/juce_ActionListener.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/broadcasters/juce_AsyncUpdater.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/broadcasters/juce_AsyncUpdater.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/broadcasters/juce_ChangeBroadcaster.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/broadcasters/juce_ChangeBroadcaster.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/broadcasters/juce_ChangeListener.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/interprocess/juce_ConnectedChildProcess.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/interprocess/juce_ConnectedChildProcess.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/interprocess/juce_InterprocessConnection.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/interprocess/juce_InterprocessConnection.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/interprocess/juce_InterprocessConnectionServer.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/interprocess/juce_InterprocessConnectionServer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/messages/juce_ApplicationBase.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/messages/juce_ApplicationBase.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/messages/juce_CallbackMessage.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/messages/juce_DeletedAtShutdown.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/messages/juce_DeletedAtShutdown.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/messages/juce_Initialisation.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/messages/juce_Message.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/messages/juce_MessageListener.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/messages/juce_MessageListener.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/messages/juce_MessageManager.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/messages/juce_MessageManager.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/messages/juce_MountedVolumeListChangeDetector.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/messages/juce_NotificationType.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/native/juce_android_Messaging.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/native/juce_ios_MessageManager.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/native/juce_linux_EventLoop.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/native/juce_linux_Messaging.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/native/juce_mac_MessageManager.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/native/juce_osx_MessageQueue.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/native/juce_win32_HiddenMessageWindow.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/native/juce_win32_Messaging.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/native/juce_win32_WinRTWrapper.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/native/juce_win32_WinRTWrapper.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/timers/juce_MultiTimer.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/timers/juce_MultiTimer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/timers/juce_Timer.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/timers/juce_Timer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/juce_events.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/juce_events.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/juce_events.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/colour/juce_Colour.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/colour/juce_Colour.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/colour/juce_ColourGradient.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/colour/juce_ColourGradient.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/colour/juce_Colours.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/colour/juce_Colours.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/colour/juce_FillType.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/colour/juce_FillType.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/colour/juce_PixelFormats.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/contexts/juce_GraphicsContext.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/contexts/juce_GraphicsContext.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/contexts/juce_LowLevelGraphicsContext.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/contexts/juce_LowLevelGraphicsPostScriptRenderer.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/contexts/juce_LowLevelGraphicsPostScriptRenderer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/contexts/juce_LowLevelGraphicsSoftwareRenderer.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/contexts/juce_LowLevelGraphicsSoftwareRenderer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/effects/juce_DropShadowEffect.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/effects/juce_DropShadowEffect.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/effects/juce_GlowEffect.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/effects/juce_GlowEffect.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/effects/juce_ImageEffectFilter.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/fonts/juce_AttributedString.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/fonts/juce_AttributedString.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/fonts/juce_CustomTypeface.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/fonts/juce_CustomTypeface.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/fonts/juce_Font.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/fonts/juce_Font.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/fonts/juce_GlyphArrangement.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/fonts/juce_GlyphArrangement.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/fonts/juce_TextLayout.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/fonts/juce_TextLayout.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/fonts/juce_Typeface.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/fonts/juce_Typeface.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/geometry/juce_AffineTransform.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/geometry/juce_AffineTransform.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/geometry/juce_BorderSize.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/geometry/juce_EdgeTable.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/geometry/juce_EdgeTable.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/geometry/juce_Line.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/geometry/juce_Parallelogram.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/geometry/juce_Path.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/geometry/juce_Path.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/geometry/juce_PathIterator.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/geometry/juce_PathIterator.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/geometry/juce_PathStrokeType.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/geometry/juce_PathStrokeType.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/geometry/juce_Point.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/geometry/juce_Rectangle.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/geometry/juce_RectangleList.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/cderror.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/changes to libjpeg for JUCE.txt" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcapimin.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcapistd.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jccoefct.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jccolor.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcdctmgr.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jchuff.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jchuff.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcinit.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcmainct.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcmarker.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcmaster.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcomapi.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jconfig.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcparam.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcphuff.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcprepct.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcsample.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jctrans.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdapimin.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdapistd.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdatasrc.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdcoefct.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdcolor.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdct.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jddctmgr.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdhuff.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdhuff.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdinput.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdmainct.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdmarker.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdmaster.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdmerge.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdphuff.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdpostct.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdsample.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdtrans.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jerror.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jerror.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jfdctflt.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jfdctfst.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jfdctint.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jidctflt.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jidctfst.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jidctint.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jidctred.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jinclude.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jmemmgr.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jmemnobs.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jmemsys.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jmorecfg.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jpegint.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jpeglib.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jquant1.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jquant2.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jutils.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jversion.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/transupp.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/transupp.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/libpng_readme.txt" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/png.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/png.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngconf.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngerror.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngget.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pnginfo.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngmem.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngpread.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngpriv.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngread.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngrio.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngrtran.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngrutil.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngset.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngstruct.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngtrans.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngwio.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngwrite.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngwtran.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngwutil.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/juce_GIFLoader.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/juce_JPEGLoader.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/juce_PNGLoader.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/images/juce_Image.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/images/juce_Image.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/images/juce_ImageCache.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/images/juce_ImageCache.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/images/juce_ImageConvolutionKernel.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/images/juce_ImageConvolutionKernel.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/images/juce_ImageFileFormat.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/images/juce_ImageFileFormat.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/native/juce_android_Fonts.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/native/juce_android_GraphicsContext.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/native/juce_android_IconHelpers.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/native/juce_freetype_Fonts.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/native/juce_linux_Fonts.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/native/juce_linux_IconHelpers.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/native/juce_mac_CoreGraphicsContext.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/native/juce_mac_CoreGraphicsContext.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/native/juce_mac_CoreGraphicsHelpers.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/native/juce_mac_Fonts.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/native/juce_mac_IconHelpers.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/native/juce_RenderingHelpers.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/native/juce_win32_Direct2DGraphicsContext.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/native/juce_win32_Direct2DGraphicsContext.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/native/juce_win32_DirectWriteTypeface.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/native/juce_win32_DirectWriteTypeLayout.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/native/juce_win32_Fonts.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/native/juce_win32_IconHelpers.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/placement/juce_Justification.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/placement/juce_RectanglePlacement.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/placement/juce_RectanglePlacement.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/juce_graphics.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/juce_graphics.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/juce_graphics.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/application/juce_Application.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/application/juce_Application.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/buttons/juce_ArrowButton.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/buttons/juce_ArrowButton.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/buttons/juce_Button.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/buttons/juce_Button.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/buttons/juce_DrawableButton.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/buttons/juce_DrawableButton.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/buttons/juce_HyperlinkButton.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/buttons/juce_HyperlinkButton.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/buttons/juce_ImageButton.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/buttons/juce_ImageButton.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/buttons/juce_ShapeButton.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/buttons/juce_ShapeButton.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/buttons/juce_TextButton.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/buttons/juce_TextButton.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/buttons/juce_ToggleButton.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/buttons/juce_ToggleButton.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/buttons/juce_ToolbarButton.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/buttons/juce_ToolbarButton.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/commands/juce_ApplicationCommandID.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/commands/juce_ApplicationCommandInfo.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/commands/juce_ApplicationCommandInfo.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/commands/juce_ApplicationCommandManager.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/commands/juce_ApplicationCommandManager.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/commands/juce_ApplicationCommandTarget.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/commands/juce_ApplicationCommandTarget.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/commands/juce_KeyPressMappingSet.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/commands/juce_KeyPressMappingSet.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/components/juce_CachedComponentImage.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/components/juce_Component.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/components/juce_Component.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/components/juce_ComponentListener.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/components/juce_ComponentListener.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/components/juce_Desktop.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/components/juce_Desktop.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/components/juce_ModalComponentManager.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/components/juce_ModalComponentManager.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/drawables/juce_Drawable.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/drawables/juce_Drawable.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawableComposite.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawableComposite.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawableImage.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawableImage.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawablePath.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawablePath.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawableRectangle.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawableRectangle.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawableShape.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawableShape.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawableText.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawableText.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/drawables/juce_SVGParser.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_ContentSharer.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_ContentSharer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_DirectoryContentsDisplayComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_DirectoryContentsDisplayComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_DirectoryContentsList.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_DirectoryContentsList.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileBrowserComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileBrowserComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileBrowserListener.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileChooser.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileChooser.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileChooserDialogBox.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileChooserDialogBox.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileListComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileListComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FilenameComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FilenameComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FilePreviewComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileSearchPathListComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileSearchPathListComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileTreeComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileTreeComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_ImagePreviewComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_ImagePreviewComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_CaretComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_CaretComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_KeyboardFocusTraverser.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_KeyboardFocusTraverser.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_KeyListener.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_KeyListener.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_KeyPress.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_KeyPress.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_ModifierKeys.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_ModifierKeys.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_SystemClipboard.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_TextEditorKeyMapper.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_TextInputTarget.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_AnimatedPosition.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_AnimatedPositionBehaviours.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_ComponentAnimator.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_ComponentAnimator.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_ComponentBoundsConstrainer.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_ComponentBoundsConstrainer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_ComponentBuilder.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_ComponentBuilder.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_ComponentMovementWatcher.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_ComponentMovementWatcher.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_ConcertinaPanel.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_ConcertinaPanel.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_FlexBox.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_FlexBox.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_FlexItem.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_Grid.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_Grid.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_GridItem.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_GridItem.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_GridUnitTests.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_GroupComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_GroupComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_MultiDocumentPanel.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_MultiDocumentPanel.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_ResizableBorderComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_ResizableBorderComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_ResizableCornerComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_ResizableCornerComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_ResizableEdgeComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_ResizableEdgeComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_ScrollBar.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_ScrollBar.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_SidePanel.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_SidePanel.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_StretchableLayoutManager.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_StretchableLayoutManager.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_StretchableLayoutResizerBar.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_StretchableLayoutResizerBar.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_StretchableObjectResizer.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_StretchableObjectResizer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_TabbedButtonBar.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_TabbedButtonBar.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_TabbedComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_TabbedComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_Viewport.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_Viewport.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V1.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V1.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V2.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V2.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V3.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V3.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V4.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V4.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/menus/juce_BurgerMenuComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/menus/juce_BurgerMenuComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/menus/juce_MenuBarComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/menus/juce_MenuBarComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/menus/juce_MenuBarModel.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/menus/juce_MenuBarModel.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/menus/juce_PopupMenu.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/menus/juce_PopupMenu.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/misc/juce_BubbleComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/misc/juce_BubbleComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/misc/juce_DropShadower.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/misc/juce_DropShadower.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/misc/juce_JUCESplashScreen.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/misc/juce_JUCESplashScreen.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/mouse/juce_ComponentDragger.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/mouse/juce_ComponentDragger.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/mouse/juce_DragAndDropContainer.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/mouse/juce_DragAndDropContainer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/mouse/juce_DragAndDropTarget.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/mouse/juce_FileDragAndDropTarget.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/mouse/juce_LassoComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/mouse/juce_MouseCursor.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/mouse/juce_MouseCursor.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/mouse/juce_MouseEvent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/mouse/juce_MouseEvent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/mouse/juce_MouseInactivityDetector.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/mouse/juce_MouseInactivityDetector.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/mouse/juce_MouseInputSource.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/mouse/juce_MouseInputSource.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/mouse/juce_MouseListener.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/mouse/juce_MouseListener.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/mouse/juce_SelectedItemSet.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/mouse/juce_TextDragAndDropTarget.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/mouse/juce_TooltipClient.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/native/juce_android_ContentSharer.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/native/juce_android_FileChooser.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/native/juce_android_Windowing.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/native/juce_common_MimeTypes.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/native/juce_ios_ContentSharer.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/native/juce_ios_FileChooser.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/native/juce_ios_UIViewComponentPeer.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/native/juce_ios_Windowing.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/native/juce_linux_FileChooser.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/native/juce_linux_X11.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/native/juce_linux_X11.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/native/juce_linux_X11_Clipboard.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/native/juce_linux_X11_Windowing.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/native/juce_mac_FileChooser.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/native/juce_mac_MainMenu.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/native/juce_mac_MouseCursor.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/native/juce_mac_NSViewComponentPeer.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/native/juce_mac_Windowing.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/native/juce_MultiTouchMapper.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/native/juce_win32_DragAndDrop.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/native/juce_win32_FileChooser.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/native/juce_win32_Windowing.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/positioning/juce_MarkerList.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/positioning/juce_MarkerList.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativeCoordinate.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativeCoordinate.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativeCoordinatePositioner.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativeCoordinatePositioner.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativeParallelogram.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativeParallelogram.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativePoint.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativePoint.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativePointPath.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativePointPath.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativeRectangle.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativeRectangle.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/properties/juce_BooleanPropertyComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/properties/juce_BooleanPropertyComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/properties/juce_ButtonPropertyComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/properties/juce_ButtonPropertyComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/properties/juce_ChoicePropertyComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/properties/juce_ChoicePropertyComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/properties/juce_MultiChoicePropertyComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/properties/juce_MultiChoicePropertyComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/properties/juce_PropertyComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/properties/juce_PropertyComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/properties/juce_PropertyPanel.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/properties/juce_PropertyPanel.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/properties/juce_SliderPropertyComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/properties/juce_SliderPropertyComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/properties/juce_TextPropertyComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/properties/juce_TextPropertyComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ComboBox.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ComboBox.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ImageComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ImageComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_Label.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_Label.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ListBox.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ListBox.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ProgressBar.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ProgressBar.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_Slider.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_Slider.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_TableHeaderComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_TableHeaderComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_TableListBox.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_TableListBox.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_TextEditor.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_TextEditor.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_Toolbar.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_Toolbar.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ToolbarItemComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ToolbarItemComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ToolbarItemFactory.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ToolbarItemPalette.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ToolbarItemPalette.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_TreeView.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_TreeView.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/windows/juce_AlertWindow.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/windows/juce_AlertWindow.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/windows/juce_CallOutBox.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/windows/juce_CallOutBox.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/windows/juce_ComponentPeer.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/windows/juce_ComponentPeer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/windows/juce_DialogWindow.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/windows/juce_DialogWindow.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/windows/juce_DocumentWindow.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/windows/juce_DocumentWindow.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/windows/juce_NativeMessageBox.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/windows/juce_ResizableWindow.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/windows/juce_ResizableWindow.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/windows/juce_ThreadWithProgressWindow.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/windows/juce_ThreadWithProgressWindow.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/windows/juce_TooltipWindow.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/windows/juce_TooltipWindow.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/windows/juce_TopLevelWindow.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/windows/juce_TopLevelWindow.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/juce_gui_basics.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/juce_gui_basics.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/juce_gui_basics.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_CodeDocument.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_CodeDocument.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_CodeEditorComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_CodeEditorComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_CodeTokeniser.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_CPlusPlusCodeTokeniser.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_CPlusPlusCodeTokeniser.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_CPlusPlusCodeTokeniserFunctions.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_LuaCodeTokeniser.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_LuaCodeTokeniser.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_XMLCodeTokeniser.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_XMLCodeTokeniser.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/documents/juce_FileBasedDocument.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/documents/juce_FileBasedDocument.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/embedding/juce_ActiveXControlComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/embedding/juce_AndroidViewComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/embedding/juce_NSViewComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/embedding/juce_UIViewComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/embedding/juce_XEmbedComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/misc/juce_AnimatedAppComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/misc/juce_AnimatedAppComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/misc/juce_AppleRemote.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/misc/juce_BubbleMessageComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/misc/juce_BubbleMessageComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/misc/juce_ColourSelector.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/misc/juce_ColourSelector.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/misc/juce_KeyMappingEditorComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/misc/juce_KeyMappingEditorComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/misc/juce_LiveConstantEditor.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/misc/juce_LiveConstantEditor.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/misc/juce_PreferencesPanel.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/misc/juce_PreferencesPanel.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/misc/juce_PushNotifications.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/misc/juce_PushNotifications.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/misc/juce_RecentlyOpenedFilesList.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/misc/juce_RecentlyOpenedFilesList.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/misc/juce_SplashScreen.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/misc/juce_SplashScreen.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/misc/juce_SystemTrayIconComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/misc/juce_SystemTrayIconComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/misc/juce_WebBrowserComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/native/juce_android_PushNotifications.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/native/juce_android_WebBrowserComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/native/juce_AndroidViewComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/native/juce_ios_PushNotifications.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/native/juce_ios_UIViewComponent.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/native/juce_linux_X11_SystemTrayIcon.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/native/juce_linux_X11_WebBrowserComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/native/juce_linux_XEmbedComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/native/juce_mac_AppleRemote.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/native/juce_mac_CarbonViewWrapperComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/native/juce_mac_NSViewComponent.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/native/juce_mac_PushNotifications.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/native/juce_mac_SystemTrayIcon.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/native/juce_mac_WebBrowserComponent.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/native/juce_win32_ActiveXComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/native/juce_win32_SystemTrayIcon.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/native/juce_win32_WebBrowserComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/juce_gui_extra.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/juce_gui_extra.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/juce_gui_extra.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../JuceLibraryCode/AppConfig.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../JuceLibraryCode/JuceHeader.h" PROPERTIES HEADER_FILE_ONLY TRUE)

set_target_properties (VST PROPERTIES PREFIX "")
set_target_properties (VST PROPERTIES SUFFIX ".so")

set_target_properties (SHARED_CODE PROPERTIES SUFFIX ".a")

#------------------------------------------------------------------------------
# Config: Debug
#------------------------------------------------------------------------------

if (CMAKE_BUILD_TYPE STREQUAL Debug)

execute_process (COMMAND uname -m OUTPUT_VARIABLE JUCE_ARCH_LABEL OUTPUT_STRIP_TRAILING_WHITESPACE)

include_directories (
    "../../JuceLibraryCode"
    "../../Vendor/juce/modules"
    ${FREETYPE2_INCLUDE_DIRS}
    ${LIBCURL_INCLUDE_DIRS}
    ${X11_INCLUDE_DIRS}
    ${XEXT_INCLUDE_DIRS}
    ${XINERAMA_INCLUDE_DIRS}
    ${WEBKIT2GTK-4.0_INCLUDE_DIRS}
    ${GTK+-X11-3.0_INCLUDE_DIRS}
)

find_library (DL dl
)

find_library (PTHREAD pthread
)

find_library (RT rt
)

set_target_properties (VST PROPERTIES
    OUTPUT_NAME "LibreArp"
    CXX_STANDARD 17
    CXX_EXTENSIONS OFF
)

target_compile_definitions (VST PRIVATE
    LINUX=1
    DEBUG=1
    _DEBUG=1
    JUCER_LINUX_MAKE_6D53C8B4=1
    JUCE_APP_VERSION=0.0
    JUCE_APP_VERSION_HEX=0x0
    JucePlugin_Build_VST=1
    JucePlugin_Build_VST3=0
    JucePlugin_Build_AU=0
    JucePlugin_Build_AUv3=0
    JucePlugin_Build_RTAS=0
    JucePlugin_Build_AAX=0
    JucePlugin_Build_Standalone=0
)

target_compile_options (VST PRIVATE
    -fPIC
    -fvisibility=hidden
)

target_link_libraries (VST PRIVATE
    SHARED_CODE
    -march=native
    -shared
    -Wl,--no-undefined
    ${DL}
    ${PTHREAD}
    ${RT}
    ${FREETYPE2_LIBRARIES}
    ${LIBCURL_LIBRARIES}
    ${X11_LIBRARIES}
    ${XEXT_LIBRARIES}
    ${XINERAMA_LIBRARIES}
    ${WEBKIT2GTK-4.0_LIBRARIES}
    ${GTK+-X11-3.0_LIBRARIES}
)

add_dependencies (VST SHARED_CODE)

set_target_properties (SHARED_CODE PROPERTIES
    OUTPUT_NAME "LibreArp"
    CXX_STANDARD 17
    CXX_EXTENSIONS OFF
)

target_compile_definitions (SHARED_CODE PRIVATE
    LINUX=1
    DEBUG=1
    _DEBUG=1
    JUCER_LINUX_MAKE_6D53C8B4=1
    JUCE_APP_VERSION=0.0
    JUCE_APP_VERSION_HEX=0x0
    JucePlugin_Build_VST=1
    JucePlugin_Build_VST3=0
    JucePlugin_Build_AU=0
    JucePlugin_Build_AUv3=0
    JucePlugin_Build_RTAS=0
    JucePlugin_Build_AAX=0
    JucePlugin_Build_Standalone=0
    JUCE_SHARED_CODE=1
)

target_link_libraries (SHARED_CODE PRIVATE
    -march=native
    ${DL}
    ${PTHREAD}
    ${RT}
    ${FREETYPE2_LIBRARIES}
    ${LIBCURL_LIBRARIES}
    ${X11_LIBRARIES}
    ${XEXT_LIBRARIES}
    ${XINERAMA_LIBRARIES}
    ${WEBKIT2GTK-4.0_LIBRARIES}
    ${GTK+-X11-3.0_LIBRARIES}
)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=native -pthread -fPIC -g -ggdb -O0")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_C_FLAGS} ")

endif (CMAKE_BUILD_TYPE STREQUAL Debug)

#------------------------------------------------------------------------------
# Config: Release_64
#------------------------------------------------------------------------------

if (CMAKE_BUILD_TYPE STREQUAL Release_64)

execute_process (COMMAND uname -m OUTPUT_VARIABLE JUCE_ARCH_LABEL OUTPUT_STRIP_TRAILING_WHITESPACE)

include_directories (
    "../../JuceLibraryCode"
    "../../Vendor/juce/modules"
    ${FREETYPE2_INCLUDE_DIRS}
    ${LIBCURL_INCLUDE_DIRS}
    ${X11_INCLUDE_DIRS}
    ${XEXT_INCLUDE_DIRS}
    ${XINERAMA_INCLUDE_DIRS}
    ${WEBKIT2GTK-4.0_INCLUDE_DIRS}
    ${GTK+-X11-3.0_INCLUDE_DIRS}
)

find_library (DL dl
)

find_library (PTHREAD pthread
)

find_library (RT rt
)

set_target_properties (VST PROPERTIES
    OUTPUT_NAME "LibreArp.x86_64"
    CXX_STANDARD 17
    CXX_EXTENSIONS OFF
)

target_compile_definitions (VST PRIVATE
    LINUX=1
    NDEBUG=1
    JUCER_LINUX_MAKE_6D53C8B4=1
    JUCE_APP_VERSION=0.0
    JUCE_APP_VERSION_HEX=0x0
    JucePlugin_Build_VST=1
    JucePlugin_Build_VST3=0
    JucePlugin_Build_AU=0
    JucePlugin_Build_AUv3=0
    JucePlugin_Build_RTAS=0
    JucePlugin_Build_AAX=0
    JucePlugin_Build_Standalone=0
)

target_compile_options (VST PRIVATE
    -fPIC
    -fvisibility=hidden
)

target_link_libraries (VST PRIVATE
    SHARED_CODE
    -m64
    -shared
    -Wl,--no-undefined
    -fvisibility=hidden
    ${DL}
    ${PTHREAD}
    ${RT}
    ${FREETYPE2_LIBRARIES}
    ${LIBCURL_LIBRARIES}
    ${X11_LIBRARIES}
    ${XEXT_LIBRARIES}
    ${XINERAMA_LIBRARIES}
    ${WEBKIT2GTK-4.0_LIBRARIES}
    ${GTK+-X11-3.0_LIBRARIES}
)

add_dependencies (VST SHARED_CODE)

set_target_properties (SHARED_CODE PROPERTIES
    OUTPUT_NAME "LibreArp.x86_64"
    CXX_STANDARD 17
    CXX_EXTENSIONS OFF
)

target_compile_definitions (SHARED_CODE PRIVATE
    LINUX=1
    NDEBUG=1
    JUCER_LINUX_MAKE_6D53C8B4=1
    JUCE_APP_VERSION=0.0
    JUCE_APP_VERSION_HEX=0x0
    JucePlugin_Build_VST=1
    JucePlugin_Build_VST3=0
    JucePlugin_Build_AU=0
    JucePlugin_Build_AUv3=0
    JucePlugin_Build_RTAS=0
    JucePlugin_Build_AAX=0
    JucePlugin_Build_Standalone=0
    JUCE_SHARED_CODE=1
)

target_link_libraries (SHARED_CODE PRIVATE
    -m64
    -fvisibility=hidden
    ${DL}
    ${PTHREAD}
    ${RT}
    ${FREETYPE2_LIBRARIES}
    ${LIBCURL_LIBRARIES}
    ${X11_LIBRARIES}
    ${XEXT_LIBRARIES}
    ${XINERAMA_LIBRARIES}
    ${WEBKIT2GTK-4.0_LIBRARIES}
    ${GTK+-X11-3.0_LIBRARIES}
)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m64 -pthread -fPIC -O3")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_C_FLAGS} ")

endif (CMAKE_BUILD_TYPE STREQUAL Release_64)

#------------------------------------------------------------------------------
# Config: Release_32
#------------------------------------------------------------------------------

if (CMAKE_BUILD_TYPE STREQUAL Release_32)

execute_process (COMMAND uname -m OUTPUT_VARIABLE JUCE_ARCH_LABEL OUTPUT_STRIP_TRAILING_WHITESPACE)

include_directories (
    "../../JuceLibraryCode"
    "../../Vendor/juce/modules"
    ${FREETYPE2_INCLUDE_DIRS}
    ${LIBCURL_INCLUDE_DIRS}
    ${X11_INCLUDE_DIRS}
    ${XEXT_INCLUDE_DIRS}
    ${XINERAMA_INCLUDE_DIRS}
    ${WEBKIT2GTK-4.0_INCLUDE_DIRS}
    ${GTK+-X11-3.0_INCLUDE_DIRS}
)

find_library (DL dl
)

find_library (PTHREAD pthread
)

find_library (RT rt
)

set_target_properties (VST PROPERTIES
    OUTPUT_NAME "LibreArp.x86"
    CXX_STANDARD 17
    CXX_EXTENSIONS OFF
)

target_compile_definitions (VST PRIVATE
    LINUX=1
    NDEBUG=1
    JUCER_LINUX_MAKE_6D53C8B4=1
    JUCE_APP_VERSION=0.0
    JUCE_APP_VERSION_HEX=0x0
    JucePlugin_Build_VST=1
    JucePlugin_Build_VST3=0
    JucePlugin_Build_AU=0
    JucePlugin_Build_AUv3=0
    JucePlugin_Build_RTAS=0
    JucePlugin_Build_AAX=0
    JucePlugin_Build_Standalone=0
)

target_compile_options (VST PRIVATE
    -fPIC
    -fvisibility=hidden
)

target_link_libraries (VST PRIVATE
    SHARED_CODE
    -m32
    -shared
    -Wl,--no-undefined
    -fvisibility=hidden
    ${DL}
    ${PTHREAD}
    ${RT}
    ${FREETYPE2_LIBRARIES}
    ${LIBCURL_LIBRARIES}
    ${X11_LIBRARIES}
    ${XEXT_LIBRARIES}
    ${XINERAMA_LIBRARIES}
    ${WEBKIT2GTK-4.0_LIBRARIES}
    ${GTK+-X11-3.0_LIBRARIES}
)

add_dependencies (VST SHARED_CODE)

set_target_properties (SHARED_CODE PROPERTIES
    OUTPUT_NAME "LibreArp.x86"
    CXX_STANDARD 17
    CXX_EXTENSIONS OFF
)

target_compile_definitions (SHARED_CODE PRIVATE
    LINUX=1
    NDEBUG=1
    JUCER_LINUX_MAKE_6D53C8B4=1
    JUCE_APP_VERSION=0.0
    JUCE_APP_VERSION_HEX=0x0
    JucePlugin_Build_VST=1
    JucePlugin_Build_VST3=0
    JucePlugin_Build_AU=0
    JucePlugin_Build_AUv3=0
    JucePlugin_Build_RTAS=0
    JucePlugin_Build_AAX=0
    JucePlugin_Build_Standalone=0
    JUCE_SHARED_CODE=1
)

target_link_libraries (SHARED_CODE PRIVATE
    -m32
    -fvisibility=hidden
    ${DL}
    ${PTHREAD}
    ${RT}
    ${FREETYPE2_LIBRARIES}
    ${LIBCURL_LIBRARIES}
    ${X11_LIBRARIES}
    ${XEXT_LIBRARIES}
    ${XINERAMA_LIBRARIES}
    ${WEBKIT2GTK-4.0_LIBRARIES}
    ${GTK+-X11-3.0_LIBRARIES}
)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32 -pthread -fPIC -O3")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_C_FLAGS} ")

endif (CMAKE_BUILD_TYPE STREQUAL Release_32)

endif()

###############################################################################
# Code::Blocks (Windows)
###############################################################################

if (WIN32)

project ("LibreArp" C CXX)

add_library (SHARED_CODE STATIC
    "../../Source/editor/MainEditor.cpp"
    "../../Source/editor/MainEditor.h"
    "../../Source/util/PatternUtil.cpp"
    "../../Source/util/PatternUtil.h"
    "../../Source/ArpEvent.cpp"
    "../../Source/ArpEvent.h"
    "../../Source/ArpIntegrityException.cpp"
    "../../Source/ArpIntegrityException.h"
    "../../Source/ArpNote.cpp"
    "../../Source/ArpNote.h"
    "../../Source/ArpPattern.cpp"
    "../../Source/ArpPattern.h"
    "../../Source/LibreArp.cpp"
    "../../Source/LibreArp.h"
    "../../Source/NoteData.cpp"
    "../../Source/NoteData.h"
    "../../Vendor/juce/modules/juce_audio_basics/audio_play_head/juce_AudioPlayHead.h"
    "../../Vendor/juce/modules/juce_audio_basics/buffers/juce_AudioChannelSet.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/buffers/juce_AudioChannelSet.h"
    "../../Vendor/juce/modules/juce_audio_basics/buffers/juce_AudioDataConverters.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/buffers/juce_AudioDataConverters.h"
    "../../Vendor/juce/modules/juce_audio_basics/buffers/juce_AudioSampleBuffer.h"
    "../../Vendor/juce/modules/juce_audio_basics/buffers/juce_FloatVectorOperations.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/buffers/juce_FloatVectorOperations.h"
    "../../Vendor/juce/modules/juce_audio_basics/effects/juce_CatmullRomInterpolator.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/effects/juce_CatmullRomInterpolator.h"
    "../../Vendor/juce/modules/juce_audio_basics/effects/juce_Decibels.h"
    "../../Vendor/juce/modules/juce_audio_basics/effects/juce_IIRFilter.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/effects/juce_IIRFilter.h"
    "../../Vendor/juce/modules/juce_audio_basics/effects/juce_LagrangeInterpolator.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/effects/juce_LagrangeInterpolator.h"
    "../../Vendor/juce/modules/juce_audio_basics/effects/juce_LinearSmoothedValue.h"
    "../../Vendor/juce/modules/juce_audio_basics/effects/juce_Reverb.h"
    "../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiBuffer.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiBuffer.h"
    "../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiFile.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiFile.h"
    "../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiKeyboardState.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiKeyboardState.h"
    "../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiMessage.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiMessage.h"
    "../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiMessageSequence.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiMessageSequence.h"
    "../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiRPN.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiRPN.h"
    "../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPEInstrument.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPEInstrument.h"
    "../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPEMessages.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPEMessages.h"
    "../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPENote.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPENote.h"
    "../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPESynthesiser.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPESynthesiser.h"
    "../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPESynthesiserBase.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPESynthesiserBase.h"
    "../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPESynthesiserVoice.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPESynthesiserVoice.h"
    "../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPEUtils.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPEUtils.h"
    "../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPEValue.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPEValue.h"
    "../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPEZoneLayout.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPEZoneLayout.h"
    "../../Vendor/juce/modules/juce_audio_basics/native/juce_mac_CoreAudioLayouts.h"
    "../../Vendor/juce/modules/juce_audio_basics/sources/juce_AudioSource.h"
    "../../Vendor/juce/modules/juce_audio_basics/sources/juce_BufferingAudioSource.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/sources/juce_BufferingAudioSource.h"
    "../../Vendor/juce/modules/juce_audio_basics/sources/juce_ChannelRemappingAudioSource.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/sources/juce_ChannelRemappingAudioSource.h"
    "../../Vendor/juce/modules/juce_audio_basics/sources/juce_IIRFilterAudioSource.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/sources/juce_IIRFilterAudioSource.h"
    "../../Vendor/juce/modules/juce_audio_basics/sources/juce_MemoryAudioSource.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/sources/juce_MemoryAudioSource.h"
    "../../Vendor/juce/modules/juce_audio_basics/sources/juce_MixerAudioSource.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/sources/juce_MixerAudioSource.h"
    "../../Vendor/juce/modules/juce_audio_basics/sources/juce_PositionableAudioSource.h"
    "../../Vendor/juce/modules/juce_audio_basics/sources/juce_ResamplingAudioSource.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/sources/juce_ResamplingAudioSource.h"
    "../../Vendor/juce/modules/juce_audio_basics/sources/juce_ReverbAudioSource.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/sources/juce_ReverbAudioSource.h"
    "../../Vendor/juce/modules/juce_audio_basics/sources/juce_ToneGeneratorAudioSource.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/sources/juce_ToneGeneratorAudioSource.h"
    "../../Vendor/juce/modules/juce_audio_basics/synthesisers/juce_Synthesiser.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/synthesisers/juce_Synthesiser.h"
    "../../Vendor/juce/modules/juce_audio_basics/juce_audio_basics.cpp"
    "../../Vendor/juce/modules/juce_audio_basics/juce_audio_basics.mm"
    "../../Vendor/juce/modules/juce_audio_basics/juce_audio_basics.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUBase.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUBase.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUBaseHelper.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUBuffer.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUBuffer.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUCarbonViewBase.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUCarbonViewBase.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUCarbonViewControl.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUCarbonViewControl.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUCarbonViewDispatch.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUDispatch.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUDispatch.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUInputElement.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUInputElement.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUInputFormatConverter.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUMIDIBase.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUMIDIBase.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUOutputBase.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUOutputBase.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUOutputElement.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUOutputElement.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUPlugInDispatch.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUPlugInDispatch.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUScopeElement.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUScopeElement.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUSilentTimeout.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUTimestampGenerator.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUViewLocalizedStringKeys.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAAtomic.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAAtomicStack.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAAudioChannelLayout.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAAudioChannelLayout.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAAUParameter.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAAUParameter.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAAutoDisposer.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CADebugMacros.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CADebugPrintf.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAException.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAHostTimeBase.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAMath.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAMutex.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAMutex.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CarbonEventHandler.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CarbonEventHandler.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAReferenceCounted.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAStreamBasicDescription.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAStreamBasicDescription.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAThreadSafeList.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAVectorUnit.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAVectorUnit.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAVectorUnitTypes.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAXException.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/ComponentBase.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/ComponentBase.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/MusicDeviceBase.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/MusicDeviceBase.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/Standalone/juce_StandaloneFilterApp.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/Standalone/juce_StandaloneFilterWindow.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/utility/juce_CarbonVisibility.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/utility/juce_CheckSettingMacros.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/utility/juce_FakeMouseMoveGenerator.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/utility/juce_IncludeModuleHeaders.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/utility/juce_IncludeSystemHeaders.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/utility/juce_PluginHostType.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/utility/juce_PluginUtilities.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/utility/juce_WindowsHooks.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/VST/juce_VST_Wrapper.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/VST/juce_VST_Wrapper.mm"
    "../../Vendor/juce/modules/juce_audio_plugin_client/VST/juce_VSTCallbackHandler.h"
    "../../Vendor/juce/modules/juce_audio_plugin_client/juce_audio_plugin_client_utils.cpp"
    "../../Vendor/juce/modules/juce_audio_plugin_client/juce_audio_plugin_client_VST_utils.mm"
    "../../Vendor/juce/modules/juce_audio_plugin_client/juce_audio_plugin_client.h"
    "../../Vendor/juce/modules/juce_audio_processors/format/juce_AudioPluginFormat.cpp"
    "../../Vendor/juce/modules/juce_audio_processors/format/juce_AudioPluginFormat.h"
    "../../Vendor/juce/modules/juce_audio_processors/format/juce_AudioPluginFormatManager.cpp"
    "../../Vendor/juce/modules/juce_audio_processors/format/juce_AudioPluginFormatManager.h"
    "../../Vendor/juce/modules/juce_audio_processors/format_types/juce_AudioUnitPluginFormat.h"
    "../../Vendor/juce/modules/juce_audio_processors/format_types/juce_AudioUnitPluginFormat.mm"
    "../../Vendor/juce/modules/juce_audio_processors/format_types/juce_LADSPAPluginFormat.cpp"
    "../../Vendor/juce/modules/juce_audio_processors/format_types/juce_LADSPAPluginFormat.h"
    "../../Vendor/juce/modules/juce_audio_processors/format_types/juce_LegacyAudioParameter.cpp"
    "../../Vendor/juce/modules/juce_audio_processors/format_types/juce_VST3Common.h"
    "../../Vendor/juce/modules/juce_audio_processors/format_types/juce_VST3Headers.h"
    "../../Vendor/juce/modules/juce_audio_processors/format_types/juce_VST3PluginFormat.cpp"
    "../../Vendor/juce/modules/juce_audio_processors/format_types/juce_VST3PluginFormat.h"
    "../../Vendor/juce/modules/juce_audio_processors/format_types/juce_VSTCommon.h"
    "../../Vendor/juce/modules/juce_audio_processors/format_types/juce_VSTInterface.h"
    "../../Vendor/juce/modules/juce_audio_processors/format_types/juce_VSTMidiEventList.h"
    "../../Vendor/juce/modules/juce_audio_processors/format_types/juce_VSTPluginFormat.cpp"
    "../../Vendor/juce/modules/juce_audio_processors/format_types/juce_VSTPluginFormat.h"
    "../../Vendor/juce/modules/juce_audio_processors/processors/juce_AudioPluginInstance.cpp"
    "../../Vendor/juce/modules/juce_audio_processors/processors/juce_AudioPluginInstance.h"
    "../../Vendor/juce/modules/juce_audio_processors/processors/juce_AudioProcessor.cpp"
    "../../Vendor/juce/modules/juce_audio_processors/processors/juce_AudioProcessor.h"
    "../../Vendor/juce/modules/juce_audio_processors/processors/juce_AudioProcessorEditor.cpp"
    "../../Vendor/juce/modules/juce_audio_processors/processors/juce_AudioProcessorEditor.h"
    "../../Vendor/juce/modules/juce_audio_processors/processors/juce_AudioProcessorGraph.cpp"
    "../../Vendor/juce/modules/juce_audio_processors/processors/juce_AudioProcessorGraph.h"
    "../../Vendor/juce/modules/juce_audio_processors/processors/juce_AudioProcessorListener.h"
    "../../Vendor/juce/modules/juce_audio_processors/processors/juce_AudioProcessorParameter.h"
    "../../Vendor/juce/modules/juce_audio_processors/processors/juce_GenericAudioProcessorEditor.cpp"
    "../../Vendor/juce/modules/juce_audio_processors/processors/juce_GenericAudioProcessorEditor.h"
    "../../Vendor/juce/modules/juce_audio_processors/processors/juce_PluginDescription.cpp"
    "../../Vendor/juce/modules/juce_audio_processors/processors/juce_PluginDescription.h"
    "../../Vendor/juce/modules/juce_audio_processors/scanning/juce_KnownPluginList.cpp"
    "../../Vendor/juce/modules/juce_audio_processors/scanning/juce_KnownPluginList.h"
    "../../Vendor/juce/modules/juce_audio_processors/scanning/juce_PluginDirectoryScanner.cpp"
    "../../Vendor/juce/modules/juce_audio_processors/scanning/juce_PluginDirectoryScanner.h"
    "../../Vendor/juce/modules/juce_audio_processors/scanning/juce_PluginListComponent.cpp"
    "../../Vendor/juce/modules/juce_audio_processors/scanning/juce_PluginListComponent.h"
    "../../Vendor/juce/modules/juce_audio_processors/utilities/juce_AudioParameterBool.h"
    "../../Vendor/juce/modules/juce_audio_processors/utilities/juce_AudioParameterChoice.h"
    "../../Vendor/juce/modules/juce_audio_processors/utilities/juce_AudioParameterFloat.h"
    "../../Vendor/juce/modules/juce_audio_processors/utilities/juce_AudioParameterInt.h"
    "../../Vendor/juce/modules/juce_audio_processors/utilities/juce_AudioProcessorParameters.cpp"
    "../../Vendor/juce/modules/juce_audio_processors/utilities/juce_AudioProcessorParameterWithID.h"
    "../../Vendor/juce/modules/juce_audio_processors/utilities/juce_AudioProcessorValueTreeState.cpp"
    "../../Vendor/juce/modules/juce_audio_processors/utilities/juce_AudioProcessorValueTreeState.h"
    "../../Vendor/juce/modules/juce_audio_processors/juce_audio_processors.cpp"
    "../../Vendor/juce/modules/juce_audio_processors/juce_audio_processors.mm"
    "../../Vendor/juce/modules/juce_audio_processors/juce_audio_processors.h"
    "../../Vendor/juce/modules/juce_core/containers/juce_AbstractFifo.cpp"
    "../../Vendor/juce/modules/juce_core/containers/juce_AbstractFifo.h"
    "../../Vendor/juce/modules/juce_core/containers/juce_Array.h"
    "../../Vendor/juce/modules/juce_core/containers/juce_ArrayAllocationBase.h"
    "../../Vendor/juce/modules/juce_core/containers/juce_DynamicObject.cpp"
    "../../Vendor/juce/modules/juce_core/containers/juce_DynamicObject.h"
    "../../Vendor/juce/modules/juce_core/containers/juce_ElementComparator.h"
    "../../Vendor/juce/modules/juce_core/containers/juce_HashMap.h"
    "../../Vendor/juce/modules/juce_core/containers/juce_HashMap_test.cpp"
    "../../Vendor/juce/modules/juce_core/containers/juce_LinkedListPointer.h"
    "../../Vendor/juce/modules/juce_core/containers/juce_ListenerList.h"
    "../../Vendor/juce/modules/juce_core/containers/juce_NamedValueSet.cpp"
    "../../Vendor/juce/modules/juce_core/containers/juce_NamedValueSet.h"
    "../../Vendor/juce/modules/juce_core/containers/juce_OwnedArray.h"
    "../../Vendor/juce/modules/juce_core/containers/juce_PropertySet.cpp"
    "../../Vendor/juce/modules/juce_core/containers/juce_PropertySet.h"
    "../../Vendor/juce/modules/juce_core/containers/juce_ReferenceCountedArray.h"
    "../../Vendor/juce/modules/juce_core/containers/juce_ScopedValueSetter.h"
    "../../Vendor/juce/modules/juce_core/containers/juce_SortedSet.h"
    "../../Vendor/juce/modules/juce_core/containers/juce_SparseSet.cpp"
    "../../Vendor/juce/modules/juce_core/containers/juce_SparseSet.h"
    "../../Vendor/juce/modules/juce_core/containers/juce_Variant.cpp"
    "../../Vendor/juce/modules/juce_core/containers/juce_Variant.h"
    "../../Vendor/juce/modules/juce_core/files/juce_DirectoryIterator.cpp"
    "../../Vendor/juce/modules/juce_core/files/juce_DirectoryIterator.h"
    "../../Vendor/juce/modules/juce_core/files/juce_File.cpp"
    "../../Vendor/juce/modules/juce_core/files/juce_File.h"
    "../../Vendor/juce/modules/juce_core/files/juce_FileFilter.cpp"
    "../../Vendor/juce/modules/juce_core/files/juce_FileFilter.h"
    "../../Vendor/juce/modules/juce_core/files/juce_FileInputStream.cpp"
    "../../Vendor/juce/modules/juce_core/files/juce_FileInputStream.h"
    "../../Vendor/juce/modules/juce_core/files/juce_FileOutputStream.cpp"
    "../../Vendor/juce/modules/juce_core/files/juce_FileOutputStream.h"
    "../../Vendor/juce/modules/juce_core/files/juce_FileSearchPath.cpp"
    "../../Vendor/juce/modules/juce_core/files/juce_FileSearchPath.h"
    "../../Vendor/juce/modules/juce_core/files/juce_MemoryMappedFile.h"
    "../../Vendor/juce/modules/juce_core/files/juce_TemporaryFile.cpp"
    "../../Vendor/juce/modules/juce_core/files/juce_TemporaryFile.h"
    "../../Vendor/juce/modules/juce_core/files/juce_WildcardFileFilter.cpp"
    "../../Vendor/juce/modules/juce_core/files/juce_WildcardFileFilter.h"
    "../../Vendor/juce/modules/juce_core/javascript/juce_Javascript.cpp"
    "../../Vendor/juce/modules/juce_core/javascript/juce_Javascript.h"
    "../../Vendor/juce/modules/juce_core/javascript/juce_JSON.cpp"
    "../../Vendor/juce/modules/juce_core/javascript/juce_JSON.h"
    "../../Vendor/juce/modules/juce_core/logging/juce_FileLogger.cpp"
    "../../Vendor/juce/modules/juce_core/logging/juce_FileLogger.h"
    "../../Vendor/juce/modules/juce_core/logging/juce_Logger.cpp"
    "../../Vendor/juce/modules/juce_core/logging/juce_Logger.h"
    "../../Vendor/juce/modules/juce_core/maths/juce_BigInteger.cpp"
    "../../Vendor/juce/modules/juce_core/maths/juce_BigInteger.h"
    "../../Vendor/juce/modules/juce_core/maths/juce_Expression.cpp"
    "../../Vendor/juce/modules/juce_core/maths/juce_Expression.h"
    "../../Vendor/juce/modules/juce_core/maths/juce_MathsFunctions.h"
    "../../Vendor/juce/modules/juce_core/maths/juce_NormalisableRange.h"
    "../../Vendor/juce/modules/juce_core/maths/juce_Random.cpp"
    "../../Vendor/juce/modules/juce_core/maths/juce_Random.h"
    "../../Vendor/juce/modules/juce_core/maths/juce_Range.h"
    "../../Vendor/juce/modules/juce_core/maths/juce_StatisticsAccumulator.h"
    "../../Vendor/juce/modules/juce_core/memory/juce_Atomic.h"
    "../../Vendor/juce/modules/juce_core/memory/juce_ByteOrder.h"
    "../../Vendor/juce/modules/juce_core/memory/juce_ContainerDeletePolicy.h"
    "../../Vendor/juce/modules/juce_core/memory/juce_HeapBlock.h"
    "../../Vendor/juce/modules/juce_core/memory/juce_LeakedObjectDetector.h"
    "../../Vendor/juce/modules/juce_core/memory/juce_Memory.h"
    "../../Vendor/juce/modules/juce_core/memory/juce_MemoryBlock.cpp"
    "../../Vendor/juce/modules/juce_core/memory/juce_MemoryBlock.h"
    "../../Vendor/juce/modules/juce_core/memory/juce_OptionalScopedPointer.h"
    "../../Vendor/juce/modules/juce_core/memory/juce_ReferenceCountedObject.h"
    "../../Vendor/juce/modules/juce_core/memory/juce_ScopedPointer.h"
    "../../Vendor/juce/modules/juce_core/memory/juce_SharedResourcePointer.h"
    "../../Vendor/juce/modules/juce_core/memory/juce_Singleton.h"
    "../../Vendor/juce/modules/juce_core/memory/juce_WeakReference.h"
    "../../Vendor/juce/modules/juce_core/misc/juce_Result.cpp"
    "../../Vendor/juce/modules/juce_core/misc/juce_Result.h"
    "../../Vendor/juce/modules/juce_core/misc/juce_RuntimePermissions.cpp"
    "../../Vendor/juce/modules/juce_core/misc/juce_RuntimePermissions.h"
    "../../Vendor/juce/modules/juce_core/misc/juce_StdFunctionCompat.cpp"
    "../../Vendor/juce/modules/juce_core/misc/juce_StdFunctionCompat.h"
    "../../Vendor/juce/modules/juce_core/misc/juce_Uuid.cpp"
    "../../Vendor/juce/modules/juce_core/misc/juce_Uuid.h"
    "../../Vendor/juce/modules/juce_core/misc/juce_WindowsRegistry.h"
    "../../Vendor/juce/modules/juce_core/native/juce_android_Files.cpp"
    "../../Vendor/juce/modules/juce_core/native/juce_android_JNIHelpers.h"
    "../../Vendor/juce/modules/juce_core/native/juce_android_Misc.cpp"
    "../../Vendor/juce/modules/juce_core/native/juce_android_Network.cpp"
    "../../Vendor/juce/modules/juce_core/native/juce_android_RuntimePermissions.cpp"
    "../../Vendor/juce/modules/juce_core/native/juce_android_SystemStats.cpp"
    "../../Vendor/juce/modules/juce_core/native/juce_android_Threads.cpp"
    "../../Vendor/juce/modules/juce_core/native/juce_BasicNativeHeaders.h"
    "../../Vendor/juce/modules/juce_core/native/juce_curl_Network.cpp"
    "../../Vendor/juce/modules/juce_core/native/juce_linux_CommonFile.cpp"
    "../../Vendor/juce/modules/juce_core/native/juce_linux_Files.cpp"
    "../../Vendor/juce/modules/juce_core/native/juce_linux_Network.cpp"
    "../../Vendor/juce/modules/juce_core/native/juce_linux_SystemStats.cpp"
    "../../Vendor/juce/modules/juce_core/native/juce_linux_Threads.cpp"
    "../../Vendor/juce/modules/juce_core/native/juce_mac_ClangBugWorkaround.h"
    "../../Vendor/juce/modules/juce_core/native/juce_mac_Files.mm"
    "../../Vendor/juce/modules/juce_core/native/juce_mac_Network.mm"
    "../../Vendor/juce/modules/juce_core/native/juce_mac_Strings.mm"
    "../../Vendor/juce/modules/juce_core/native/juce_mac_SystemStats.mm"
    "../../Vendor/juce/modules/juce_core/native/juce_mac_Threads.mm"
    "../../Vendor/juce/modules/juce_core/native/juce_osx_ObjCHelpers.h"
    "../../Vendor/juce/modules/juce_core/native/juce_posix_NamedPipe.cpp"
    "../../Vendor/juce/modules/juce_core/native/juce_posix_SharedCode.h"
    "../../Vendor/juce/modules/juce_core/native/juce_win32_ComSmartPtr.h"
    "../../Vendor/juce/modules/juce_core/native/juce_win32_Files.cpp"
    "../../Vendor/juce/modules/juce_core/native/juce_win32_Network.cpp"
    "../../Vendor/juce/modules/juce_core/native/juce_win32_Registry.cpp"
    "../../Vendor/juce/modules/juce_core/native/juce_win32_SystemStats.cpp"
    "../../Vendor/juce/modules/juce_core/native/juce_win32_Threads.cpp"
    "../../Vendor/juce/modules/juce_core/network/juce_IPAddress.cpp"
    "../../Vendor/juce/modules/juce_core/network/juce_IPAddress.h"
    "../../Vendor/juce/modules/juce_core/network/juce_MACAddress.cpp"
    "../../Vendor/juce/modules/juce_core/network/juce_MACAddress.h"
    "../../Vendor/juce/modules/juce_core/network/juce_NamedPipe.cpp"
    "../../Vendor/juce/modules/juce_core/network/juce_NamedPipe.h"
    "../../Vendor/juce/modules/juce_core/network/juce_Socket.cpp"
    "../../Vendor/juce/modules/juce_core/network/juce_Socket.h"
    "../../Vendor/juce/modules/juce_core/network/juce_URL.cpp"
    "../../Vendor/juce/modules/juce_core/network/juce_URL.h"
    "../../Vendor/juce/modules/juce_core/network/juce_WebInputStream.cpp"
    "../../Vendor/juce/modules/juce_core/network/juce_WebInputStream.h"
    "../../Vendor/juce/modules/juce_core/streams/juce_BufferedInputStream.cpp"
    "../../Vendor/juce/modules/juce_core/streams/juce_BufferedInputStream.h"
    "../../Vendor/juce/modules/juce_core/streams/juce_FileInputSource.cpp"
    "../../Vendor/juce/modules/juce_core/streams/juce_FileInputSource.h"
    "../../Vendor/juce/modules/juce_core/streams/juce_InputSource.h"
    "../../Vendor/juce/modules/juce_core/streams/juce_InputStream.cpp"
    "../../Vendor/juce/modules/juce_core/streams/juce_InputStream.h"
    "../../Vendor/juce/modules/juce_core/streams/juce_MemoryInputStream.cpp"
    "../../Vendor/juce/modules/juce_core/streams/juce_MemoryInputStream.h"
    "../../Vendor/juce/modules/juce_core/streams/juce_MemoryOutputStream.cpp"
    "../../Vendor/juce/modules/juce_core/streams/juce_MemoryOutputStream.h"
    "../../Vendor/juce/modules/juce_core/streams/juce_OutputStream.cpp"
    "../../Vendor/juce/modules/juce_core/streams/juce_OutputStream.h"
    "../../Vendor/juce/modules/juce_core/streams/juce_SubregionStream.cpp"
    "../../Vendor/juce/modules/juce_core/streams/juce_SubregionStream.h"
    "../../Vendor/juce/modules/juce_core/streams/juce_URLInputSource.cpp"
    "../../Vendor/juce/modules/juce_core/streams/juce_URLInputSource.h"
    "../../Vendor/juce/modules/juce_core/system/juce_CompilerSupport.h"
    "../../Vendor/juce/modules/juce_core/system/juce_PlatformDefs.h"
    "../../Vendor/juce/modules/juce_core/system/juce_StandardHeader.h"
    "../../Vendor/juce/modules/juce_core/system/juce_SystemStats.cpp"
    "../../Vendor/juce/modules/juce_core/system/juce_SystemStats.h"
    "../../Vendor/juce/modules/juce_core/system/juce_TargetPlatform.h"
    "../../Vendor/juce/modules/juce_core/text/juce_Base64.cpp"
    "../../Vendor/juce/modules/juce_core/text/juce_Base64.h"
    "../../Vendor/juce/modules/juce_core/text/juce_CharacterFunctions.cpp"
    "../../Vendor/juce/modules/juce_core/text/juce_CharacterFunctions.h"
    "../../Vendor/juce/modules/juce_core/text/juce_CharPointer_ASCII.h"
    "../../Vendor/juce/modules/juce_core/text/juce_CharPointer_UTF8.h"
    "../../Vendor/juce/modules/juce_core/text/juce_CharPointer_UTF16.h"
    "../../Vendor/juce/modules/juce_core/text/juce_CharPointer_UTF32.h"
    "../../Vendor/juce/modules/juce_core/text/juce_Identifier.cpp"
    "../../Vendor/juce/modules/juce_core/text/juce_Identifier.h"
    "../../Vendor/juce/modules/juce_core/text/juce_LocalisedStrings.cpp"
    "../../Vendor/juce/modules/juce_core/text/juce_LocalisedStrings.h"
    "../../Vendor/juce/modules/juce_core/text/juce_NewLine.h"
    "../../Vendor/juce/modules/juce_core/text/juce_String.cpp"
    "../../Vendor/juce/modules/juce_core/text/juce_String.h"
    "../../Vendor/juce/modules/juce_core/text/juce_StringArray.cpp"
    "../../Vendor/juce/modules/juce_core/text/juce_StringArray.h"
    "../../Vendor/juce/modules/juce_core/text/juce_StringPairArray.cpp"
    "../../Vendor/juce/modules/juce_core/text/juce_StringPairArray.h"
    "../../Vendor/juce/modules/juce_core/text/juce_StringPool.cpp"
    "../../Vendor/juce/modules/juce_core/text/juce_StringPool.h"
    "../../Vendor/juce/modules/juce_core/text/juce_StringRef.h"
    "../../Vendor/juce/modules/juce_core/text/juce_TextDiff.cpp"
    "../../Vendor/juce/modules/juce_core/text/juce_TextDiff.h"
    "../../Vendor/juce/modules/juce_core/threads/juce_ChildProcess.cpp"
    "../../Vendor/juce/modules/juce_core/threads/juce_ChildProcess.h"
    "../../Vendor/juce/modules/juce_core/threads/juce_CriticalSection.h"
    "../../Vendor/juce/modules/juce_core/threads/juce_DynamicLibrary.h"
    "../../Vendor/juce/modules/juce_core/threads/juce_HighResolutionTimer.cpp"
    "../../Vendor/juce/modules/juce_core/threads/juce_HighResolutionTimer.h"
    "../../Vendor/juce/modules/juce_core/threads/juce_InterProcessLock.h"
    "../../Vendor/juce/modules/juce_core/threads/juce_Process.h"
    "../../Vendor/juce/modules/juce_core/threads/juce_ReadWriteLock.cpp"
    "../../Vendor/juce/modules/juce_core/threads/juce_ReadWriteLock.h"
    "../../Vendor/juce/modules/juce_core/threads/juce_ScopedLock.h"
    "../../Vendor/juce/modules/juce_core/threads/juce_ScopedReadLock.h"
    "../../Vendor/juce/modules/juce_core/threads/juce_ScopedWriteLock.h"
    "../../Vendor/juce/modules/juce_core/threads/juce_SpinLock.h"
    "../../Vendor/juce/modules/juce_core/threads/juce_Thread.cpp"
    "../../Vendor/juce/modules/juce_core/threads/juce_Thread.h"
    "../../Vendor/juce/modules/juce_core/threads/juce_ThreadLocalValue.h"
    "../../Vendor/juce/modules/juce_core/threads/juce_ThreadPool.cpp"
    "../../Vendor/juce/modules/juce_core/threads/juce_ThreadPool.h"
    "../../Vendor/juce/modules/juce_core/threads/juce_TimeSliceThread.cpp"
    "../../Vendor/juce/modules/juce_core/threads/juce_TimeSliceThread.h"
    "../../Vendor/juce/modules/juce_core/threads/juce_WaitableEvent.h"
    "../../Vendor/juce/modules/juce_core/time/juce_PerformanceCounter.cpp"
    "../../Vendor/juce/modules/juce_core/time/juce_PerformanceCounter.h"
    "../../Vendor/juce/modules/juce_core/time/juce_RelativeTime.cpp"
    "../../Vendor/juce/modules/juce_core/time/juce_RelativeTime.h"
    "../../Vendor/juce/modules/juce_core/time/juce_Time.cpp"
    "../../Vendor/juce/modules/juce_core/time/juce_Time.h"
    "../../Vendor/juce/modules/juce_core/unit_tests/juce_UnitTest.cpp"
    "../../Vendor/juce/modules/juce_core/unit_tests/juce_UnitTest.h"
    "../../Vendor/juce/modules/juce_core/xml/juce_XmlDocument.cpp"
    "../../Vendor/juce/modules/juce_core/xml/juce_XmlDocument.h"
    "../../Vendor/juce/modules/juce_core/xml/juce_XmlElement.cpp"
    "../../Vendor/juce/modules/juce_core/xml/juce_XmlElement.h"
    "../../Vendor/juce/modules/juce_core/zip/zlib/adler32.c"
    "../../Vendor/juce/modules/juce_core/zip/zlib/compress.c"
    "../../Vendor/juce/modules/juce_core/zip/zlib/crc32.c"
    "../../Vendor/juce/modules/juce_core/zip/zlib/crc32.h"
    "../../Vendor/juce/modules/juce_core/zip/zlib/deflate.c"
    "../../Vendor/juce/modules/juce_core/zip/zlib/deflate.h"
    "../../Vendor/juce/modules/juce_core/zip/zlib/infback.c"
    "../../Vendor/juce/modules/juce_core/zip/zlib/inffast.c"
    "../../Vendor/juce/modules/juce_core/zip/zlib/inffast.h"
    "../../Vendor/juce/modules/juce_core/zip/zlib/inffixed.h"
    "../../Vendor/juce/modules/juce_core/zip/zlib/inflate.c"
    "../../Vendor/juce/modules/juce_core/zip/zlib/inflate.h"
    "../../Vendor/juce/modules/juce_core/zip/zlib/inftrees.c"
    "../../Vendor/juce/modules/juce_core/zip/zlib/inftrees.h"
    "../../Vendor/juce/modules/juce_core/zip/zlib/trees.c"
    "../../Vendor/juce/modules/juce_core/zip/zlib/trees.h"
    "../../Vendor/juce/modules/juce_core/zip/zlib/uncompr.c"
    "../../Vendor/juce/modules/juce_core/zip/zlib/zconf.h"
    "../../Vendor/juce/modules/juce_core/zip/zlib/zconf.in.h"
    "../../Vendor/juce/modules/juce_core/zip/zlib/zlib.h"
    "../../Vendor/juce/modules/juce_core/zip/zlib/zutil.c"
    "../../Vendor/juce/modules/juce_core/zip/zlib/zutil.h"
    "../../Vendor/juce/modules/juce_core/zip/juce_GZIPCompressorOutputStream.cpp"
    "../../Vendor/juce/modules/juce_core/zip/juce_GZIPCompressorOutputStream.h"
    "../../Vendor/juce/modules/juce_core/zip/juce_GZIPDecompressorInputStream.cpp"
    "../../Vendor/juce/modules/juce_core/zip/juce_GZIPDecompressorInputStream.h"
    "../../Vendor/juce/modules/juce_core/zip/juce_ZipFile.cpp"
    "../../Vendor/juce/modules/juce_core/zip/juce_ZipFile.h"
    "../../Vendor/juce/modules/juce_core/juce_core.cpp"
    "../../Vendor/juce/modules/juce_core/juce_core.mm"
    "../../Vendor/juce/modules/juce_core/juce_core.h"
    "../../Vendor/juce/modules/juce_data_structures/app_properties/juce_ApplicationProperties.cpp"
    "../../Vendor/juce/modules/juce_data_structures/app_properties/juce_ApplicationProperties.h"
    "../../Vendor/juce/modules/juce_data_structures/app_properties/juce_PropertiesFile.cpp"
    "../../Vendor/juce/modules/juce_data_structures/app_properties/juce_PropertiesFile.h"
    "../../Vendor/juce/modules/juce_data_structures/undomanager/juce_UndoableAction.h"
    "../../Vendor/juce/modules/juce_data_structures/undomanager/juce_UndoManager.cpp"
    "../../Vendor/juce/modules/juce_data_structures/undomanager/juce_UndoManager.h"
    "../../Vendor/juce/modules/juce_data_structures/values/juce_CachedValue.cpp"
    "../../Vendor/juce/modules/juce_data_structures/values/juce_CachedValue.h"
    "../../Vendor/juce/modules/juce_data_structures/values/juce_Value.cpp"
    "../../Vendor/juce/modules/juce_data_structures/values/juce_Value.h"
    "../../Vendor/juce/modules/juce_data_structures/values/juce_ValueTree.cpp"
    "../../Vendor/juce/modules/juce_data_structures/values/juce_ValueTree.h"
    "../../Vendor/juce/modules/juce_data_structures/values/juce_ValueTreeSynchroniser.cpp"
    "../../Vendor/juce/modules/juce_data_structures/values/juce_ValueTreeSynchroniser.h"
    "../../Vendor/juce/modules/juce_data_structures/values/juce_ValueWithDefault.h"
    "../../Vendor/juce/modules/juce_data_structures/juce_data_structures.cpp"
    "../../Vendor/juce/modules/juce_data_structures/juce_data_structures.mm"
    "../../Vendor/juce/modules/juce_data_structures/juce_data_structures.h"
    "../../Vendor/juce/modules/juce_events/broadcasters/juce_ActionBroadcaster.cpp"
    "../../Vendor/juce/modules/juce_events/broadcasters/juce_ActionBroadcaster.h"
    "../../Vendor/juce/modules/juce_events/broadcasters/juce_ActionListener.h"
    "../../Vendor/juce/modules/juce_events/broadcasters/juce_AsyncUpdater.cpp"
    "../../Vendor/juce/modules/juce_events/broadcasters/juce_AsyncUpdater.h"
    "../../Vendor/juce/modules/juce_events/broadcasters/juce_ChangeBroadcaster.cpp"
    "../../Vendor/juce/modules/juce_events/broadcasters/juce_ChangeBroadcaster.h"
    "../../Vendor/juce/modules/juce_events/broadcasters/juce_ChangeListener.h"
    "../../Vendor/juce/modules/juce_events/interprocess/juce_ConnectedChildProcess.cpp"
    "../../Vendor/juce/modules/juce_events/interprocess/juce_ConnectedChildProcess.h"
    "../../Vendor/juce/modules/juce_events/interprocess/juce_InterprocessConnection.cpp"
    "../../Vendor/juce/modules/juce_events/interprocess/juce_InterprocessConnection.h"
    "../../Vendor/juce/modules/juce_events/interprocess/juce_InterprocessConnectionServer.cpp"
    "../../Vendor/juce/modules/juce_events/interprocess/juce_InterprocessConnectionServer.h"
    "../../Vendor/juce/modules/juce_events/messages/juce_ApplicationBase.cpp"
    "../../Vendor/juce/modules/juce_events/messages/juce_ApplicationBase.h"
    "../../Vendor/juce/modules/juce_events/messages/juce_CallbackMessage.h"
    "../../Vendor/juce/modules/juce_events/messages/juce_DeletedAtShutdown.cpp"
    "../../Vendor/juce/modules/juce_events/messages/juce_DeletedAtShutdown.h"
    "../../Vendor/juce/modules/juce_events/messages/juce_Initialisation.h"
    "../../Vendor/juce/modules/juce_events/messages/juce_Message.h"
    "../../Vendor/juce/modules/juce_events/messages/juce_MessageListener.cpp"
    "../../Vendor/juce/modules/juce_events/messages/juce_MessageListener.h"
    "../../Vendor/juce/modules/juce_events/messages/juce_MessageManager.cpp"
    "../../Vendor/juce/modules/juce_events/messages/juce_MessageManager.h"
    "../../Vendor/juce/modules/juce_events/messages/juce_MountedVolumeListChangeDetector.h"
    "../../Vendor/juce/modules/juce_events/messages/juce_NotificationType.h"
    "../../Vendor/juce/modules/juce_events/native/juce_android_Messaging.cpp"
    "../../Vendor/juce/modules/juce_events/native/juce_ios_MessageManager.mm"
    "../../Vendor/juce/modules/juce_events/native/juce_linux_EventLoop.h"
    "../../Vendor/juce/modules/juce_events/native/juce_linux_Messaging.cpp"
    "../../Vendor/juce/modules/juce_events/native/juce_mac_MessageManager.mm"
    "../../Vendor/juce/modules/juce_events/native/juce_osx_MessageQueue.h"
    "../../Vendor/juce/modules/juce_events/native/juce_win32_HiddenMessageWindow.h"
    "../../Vendor/juce/modules/juce_events/native/juce_win32_Messaging.cpp"
    "../../Vendor/juce/modules/juce_events/native/juce_win32_WinRTWrapper.cpp"
    "../../Vendor/juce/modules/juce_events/native/juce_win32_WinRTWrapper.h"
    "../../Vendor/juce/modules/juce_events/timers/juce_MultiTimer.cpp"
    "../../Vendor/juce/modules/juce_events/timers/juce_MultiTimer.h"
    "../../Vendor/juce/modules/juce_events/timers/juce_Timer.cpp"
    "../../Vendor/juce/modules/juce_events/timers/juce_Timer.h"
    "../../Vendor/juce/modules/juce_events/juce_events.cpp"
    "../../Vendor/juce/modules/juce_events/juce_events.mm"
    "../../Vendor/juce/modules/juce_events/juce_events.h"
    "../../Vendor/juce/modules/juce_graphics/colour/juce_Colour.cpp"
    "../../Vendor/juce/modules/juce_graphics/colour/juce_Colour.h"
    "../../Vendor/juce/modules/juce_graphics/colour/juce_ColourGradient.cpp"
    "../../Vendor/juce/modules/juce_graphics/colour/juce_ColourGradient.h"
    "../../Vendor/juce/modules/juce_graphics/colour/juce_Colours.cpp"
    "../../Vendor/juce/modules/juce_graphics/colour/juce_Colours.h"
    "../../Vendor/juce/modules/juce_graphics/colour/juce_FillType.cpp"
    "../../Vendor/juce/modules/juce_graphics/colour/juce_FillType.h"
    "../../Vendor/juce/modules/juce_graphics/colour/juce_PixelFormats.h"
    "../../Vendor/juce/modules/juce_graphics/contexts/juce_GraphicsContext.cpp"
    "../../Vendor/juce/modules/juce_graphics/contexts/juce_GraphicsContext.h"
    "../../Vendor/juce/modules/juce_graphics/contexts/juce_LowLevelGraphicsContext.h"
    "../../Vendor/juce/modules/juce_graphics/contexts/juce_LowLevelGraphicsPostScriptRenderer.cpp"
    "../../Vendor/juce/modules/juce_graphics/contexts/juce_LowLevelGraphicsPostScriptRenderer.h"
    "../../Vendor/juce/modules/juce_graphics/contexts/juce_LowLevelGraphicsSoftwareRenderer.cpp"
    "../../Vendor/juce/modules/juce_graphics/contexts/juce_LowLevelGraphicsSoftwareRenderer.h"
    "../../Vendor/juce/modules/juce_graphics/effects/juce_DropShadowEffect.cpp"
    "../../Vendor/juce/modules/juce_graphics/effects/juce_DropShadowEffect.h"
    "../../Vendor/juce/modules/juce_graphics/effects/juce_GlowEffect.cpp"
    "../../Vendor/juce/modules/juce_graphics/effects/juce_GlowEffect.h"
    "../../Vendor/juce/modules/juce_graphics/effects/juce_ImageEffectFilter.h"
    "../../Vendor/juce/modules/juce_graphics/fonts/juce_AttributedString.cpp"
    "../../Vendor/juce/modules/juce_graphics/fonts/juce_AttributedString.h"
    "../../Vendor/juce/modules/juce_graphics/fonts/juce_CustomTypeface.cpp"
    "../../Vendor/juce/modules/juce_graphics/fonts/juce_CustomTypeface.h"
    "../../Vendor/juce/modules/juce_graphics/fonts/juce_Font.cpp"
    "../../Vendor/juce/modules/juce_graphics/fonts/juce_Font.h"
    "../../Vendor/juce/modules/juce_graphics/fonts/juce_GlyphArrangement.cpp"
    "../../Vendor/juce/modules/juce_graphics/fonts/juce_GlyphArrangement.h"
    "../../Vendor/juce/modules/juce_graphics/fonts/juce_TextLayout.cpp"
    "../../Vendor/juce/modules/juce_graphics/fonts/juce_TextLayout.h"
    "../../Vendor/juce/modules/juce_graphics/fonts/juce_Typeface.cpp"
    "../../Vendor/juce/modules/juce_graphics/fonts/juce_Typeface.h"
    "../../Vendor/juce/modules/juce_graphics/geometry/juce_AffineTransform.cpp"
    "../../Vendor/juce/modules/juce_graphics/geometry/juce_AffineTransform.h"
    "../../Vendor/juce/modules/juce_graphics/geometry/juce_BorderSize.h"
    "../../Vendor/juce/modules/juce_graphics/geometry/juce_EdgeTable.cpp"
    "../../Vendor/juce/modules/juce_graphics/geometry/juce_EdgeTable.h"
    "../../Vendor/juce/modules/juce_graphics/geometry/juce_Line.h"
    "../../Vendor/juce/modules/juce_graphics/geometry/juce_Parallelogram.h"
    "../../Vendor/juce/modules/juce_graphics/geometry/juce_Path.cpp"
    "../../Vendor/juce/modules/juce_graphics/geometry/juce_Path.h"
    "../../Vendor/juce/modules/juce_graphics/geometry/juce_PathIterator.cpp"
    "../../Vendor/juce/modules/juce_graphics/geometry/juce_PathIterator.h"
    "../../Vendor/juce/modules/juce_graphics/geometry/juce_PathStrokeType.cpp"
    "../../Vendor/juce/modules/juce_graphics/geometry/juce_PathStrokeType.h"
    "../../Vendor/juce/modules/juce_graphics/geometry/juce_Point.h"
    "../../Vendor/juce/modules/juce_graphics/geometry/juce_Rectangle.h"
    "../../Vendor/juce/modules/juce_graphics/geometry/juce_RectangleList.h"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/cderror.h"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/changes to libjpeg for JUCE.txt"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcapimin.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcapistd.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jccoefct.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jccolor.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcdctmgr.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jchuff.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jchuff.h"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcinit.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcmainct.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcmarker.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcmaster.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcomapi.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jconfig.h"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcparam.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcphuff.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcprepct.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcsample.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jctrans.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdapimin.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdapistd.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdatasrc.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdcoefct.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdcolor.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdct.h"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jddctmgr.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdhuff.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdhuff.h"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdinput.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdmainct.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdmarker.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdmaster.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdmerge.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdphuff.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdpostct.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdsample.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdtrans.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jerror.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jerror.h"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jfdctflt.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jfdctfst.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jfdctint.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jidctflt.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jidctfst.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jidctint.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jidctred.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jinclude.h"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jmemmgr.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jmemnobs.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jmemsys.h"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jmorecfg.h"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jpegint.h"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jpeglib.h"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jquant1.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jquant2.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jutils.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jversion.h"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/transupp.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/transupp.h"
    "../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/libpng_readme.txt"
    "../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/png.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/png.h"
    "../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngconf.h"
    "../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngerror.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngget.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pnginfo.h"
    "../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngmem.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngpread.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngpriv.h"
    "../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngread.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngrio.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngrtran.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngrutil.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngset.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngstruct.h"
    "../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngtrans.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngwio.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngwrite.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngwtran.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngwutil.c"
    "../../Vendor/juce/modules/juce_graphics/image_formats/juce_GIFLoader.cpp"
    "../../Vendor/juce/modules/juce_graphics/image_formats/juce_JPEGLoader.cpp"
    "../../Vendor/juce/modules/juce_graphics/image_formats/juce_PNGLoader.cpp"
    "../../Vendor/juce/modules/juce_graphics/images/juce_Image.cpp"
    "../../Vendor/juce/modules/juce_graphics/images/juce_Image.h"
    "../../Vendor/juce/modules/juce_graphics/images/juce_ImageCache.cpp"
    "../../Vendor/juce/modules/juce_graphics/images/juce_ImageCache.h"
    "../../Vendor/juce/modules/juce_graphics/images/juce_ImageConvolutionKernel.cpp"
    "../../Vendor/juce/modules/juce_graphics/images/juce_ImageConvolutionKernel.h"
    "../../Vendor/juce/modules/juce_graphics/images/juce_ImageFileFormat.cpp"
    "../../Vendor/juce/modules/juce_graphics/images/juce_ImageFileFormat.h"
    "../../Vendor/juce/modules/juce_graphics/native/juce_android_Fonts.cpp"
    "../../Vendor/juce/modules/juce_graphics/native/juce_android_GraphicsContext.cpp"
    "../../Vendor/juce/modules/juce_graphics/native/juce_android_IconHelpers.cpp"
    "../../Vendor/juce/modules/juce_graphics/native/juce_freetype_Fonts.cpp"
    "../../Vendor/juce/modules/juce_graphics/native/juce_linux_Fonts.cpp"
    "../../Vendor/juce/modules/juce_graphics/native/juce_linux_IconHelpers.cpp"
    "../../Vendor/juce/modules/juce_graphics/native/juce_mac_CoreGraphicsContext.h"
    "../../Vendor/juce/modules/juce_graphics/native/juce_mac_CoreGraphicsContext.mm"
    "../../Vendor/juce/modules/juce_graphics/native/juce_mac_CoreGraphicsHelpers.h"
    "../../Vendor/juce/modules/juce_graphics/native/juce_mac_Fonts.mm"
    "../../Vendor/juce/modules/juce_graphics/native/juce_mac_IconHelpers.cpp"
    "../../Vendor/juce/modules/juce_graphics/native/juce_RenderingHelpers.h"
    "../../Vendor/juce/modules/juce_graphics/native/juce_win32_Direct2DGraphicsContext.cpp"
    "../../Vendor/juce/modules/juce_graphics/native/juce_win32_Direct2DGraphicsContext.h"
    "../../Vendor/juce/modules/juce_graphics/native/juce_win32_DirectWriteTypeface.cpp"
    "../../Vendor/juce/modules/juce_graphics/native/juce_win32_DirectWriteTypeLayout.cpp"
    "../../Vendor/juce/modules/juce_graphics/native/juce_win32_Fonts.cpp"
    "../../Vendor/juce/modules/juce_graphics/native/juce_win32_IconHelpers.cpp"
    "../../Vendor/juce/modules/juce_graphics/placement/juce_Justification.h"
    "../../Vendor/juce/modules/juce_graphics/placement/juce_RectanglePlacement.cpp"
    "../../Vendor/juce/modules/juce_graphics/placement/juce_RectanglePlacement.h"
    "../../Vendor/juce/modules/juce_graphics/juce_graphics.cpp"
    "../../Vendor/juce/modules/juce_graphics/juce_graphics.mm"
    "../../Vendor/juce/modules/juce_graphics/juce_graphics.h"
    "../../Vendor/juce/modules/juce_gui_basics/application/juce_Application.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/application/juce_Application.h"
    "../../Vendor/juce/modules/juce_gui_basics/buttons/juce_ArrowButton.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/buttons/juce_ArrowButton.h"
    "../../Vendor/juce/modules/juce_gui_basics/buttons/juce_Button.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/buttons/juce_Button.h"
    "../../Vendor/juce/modules/juce_gui_basics/buttons/juce_DrawableButton.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/buttons/juce_DrawableButton.h"
    "../../Vendor/juce/modules/juce_gui_basics/buttons/juce_HyperlinkButton.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/buttons/juce_HyperlinkButton.h"
    "../../Vendor/juce/modules/juce_gui_basics/buttons/juce_ImageButton.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/buttons/juce_ImageButton.h"
    "../../Vendor/juce/modules/juce_gui_basics/buttons/juce_ShapeButton.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/buttons/juce_ShapeButton.h"
    "../../Vendor/juce/modules/juce_gui_basics/buttons/juce_TextButton.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/buttons/juce_TextButton.h"
    "../../Vendor/juce/modules/juce_gui_basics/buttons/juce_ToggleButton.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/buttons/juce_ToggleButton.h"
    "../../Vendor/juce/modules/juce_gui_basics/buttons/juce_ToolbarButton.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/buttons/juce_ToolbarButton.h"
    "../../Vendor/juce/modules/juce_gui_basics/commands/juce_ApplicationCommandID.h"
    "../../Vendor/juce/modules/juce_gui_basics/commands/juce_ApplicationCommandInfo.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/commands/juce_ApplicationCommandInfo.h"
    "../../Vendor/juce/modules/juce_gui_basics/commands/juce_ApplicationCommandManager.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/commands/juce_ApplicationCommandManager.h"
    "../../Vendor/juce/modules/juce_gui_basics/commands/juce_ApplicationCommandTarget.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/commands/juce_ApplicationCommandTarget.h"
    "../../Vendor/juce/modules/juce_gui_basics/commands/juce_KeyPressMappingSet.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/commands/juce_KeyPressMappingSet.h"
    "../../Vendor/juce/modules/juce_gui_basics/components/juce_CachedComponentImage.h"
    "../../Vendor/juce/modules/juce_gui_basics/components/juce_Component.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/components/juce_Component.h"
    "../../Vendor/juce/modules/juce_gui_basics/components/juce_ComponentListener.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/components/juce_ComponentListener.h"
    "../../Vendor/juce/modules/juce_gui_basics/components/juce_Desktop.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/components/juce_Desktop.h"
    "../../Vendor/juce/modules/juce_gui_basics/components/juce_ModalComponentManager.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/components/juce_ModalComponentManager.h"
    "../../Vendor/juce/modules/juce_gui_basics/drawables/juce_Drawable.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/drawables/juce_Drawable.h"
    "../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawableComposite.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawableComposite.h"
    "../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawableImage.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawableImage.h"
    "../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawablePath.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawablePath.h"
    "../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawableRectangle.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawableRectangle.h"
    "../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawableShape.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawableShape.h"
    "../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawableText.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawableText.h"
    "../../Vendor/juce/modules/juce_gui_basics/drawables/juce_SVGParser.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_ContentSharer.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_ContentSharer.h"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_DirectoryContentsDisplayComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_DirectoryContentsDisplayComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_DirectoryContentsList.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_DirectoryContentsList.h"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileBrowserComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileBrowserComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileBrowserListener.h"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileChooser.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileChooser.h"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileChooserDialogBox.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileChooserDialogBox.h"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileListComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileListComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FilenameComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FilenameComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FilePreviewComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileSearchPathListComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileSearchPathListComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileTreeComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileTreeComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_ImagePreviewComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_ImagePreviewComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_CaretComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_CaretComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_KeyboardFocusTraverser.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_KeyboardFocusTraverser.h"
    "../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_KeyListener.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_KeyListener.h"
    "../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_KeyPress.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_KeyPress.h"
    "../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_ModifierKeys.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_ModifierKeys.h"
    "../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_SystemClipboard.h"
    "../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_TextEditorKeyMapper.h"
    "../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_TextInputTarget.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_AnimatedPosition.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_AnimatedPositionBehaviours.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_ComponentAnimator.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_ComponentAnimator.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_ComponentBoundsConstrainer.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_ComponentBoundsConstrainer.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_ComponentBuilder.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_ComponentBuilder.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_ComponentMovementWatcher.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_ComponentMovementWatcher.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_ConcertinaPanel.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_ConcertinaPanel.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_FlexBox.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_FlexBox.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_FlexItem.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_Grid.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_Grid.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_GridItem.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_GridItem.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_GridUnitTests.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_GroupComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_GroupComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_MultiDocumentPanel.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_MultiDocumentPanel.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_ResizableBorderComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_ResizableBorderComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_ResizableCornerComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_ResizableCornerComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_ResizableEdgeComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_ResizableEdgeComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_ScrollBar.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_ScrollBar.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_SidePanel.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_SidePanel.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_StretchableLayoutManager.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_StretchableLayoutManager.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_StretchableLayoutResizerBar.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_StretchableLayoutResizerBar.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_StretchableObjectResizer.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_StretchableObjectResizer.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_TabbedButtonBar.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_TabbedButtonBar.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_TabbedComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_TabbedComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_Viewport.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/layout/juce_Viewport.h"
    "../../Vendor/juce/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel.h"
    "../../Vendor/juce/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V1.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V1.h"
    "../../Vendor/juce/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V2.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V2.h"
    "../../Vendor/juce/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V3.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V3.h"
    "../../Vendor/juce/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V4.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V4.h"
    "../../Vendor/juce/modules/juce_gui_basics/menus/juce_BurgerMenuComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/menus/juce_BurgerMenuComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/menus/juce_MenuBarComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/menus/juce_MenuBarComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/menus/juce_MenuBarModel.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/menus/juce_MenuBarModel.h"
    "../../Vendor/juce/modules/juce_gui_basics/menus/juce_PopupMenu.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/menus/juce_PopupMenu.h"
    "../../Vendor/juce/modules/juce_gui_basics/misc/juce_BubbleComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/misc/juce_BubbleComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/misc/juce_DropShadower.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/misc/juce_DropShadower.h"
    "../../Vendor/juce/modules/juce_gui_basics/misc/juce_JUCESplashScreen.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/misc/juce_JUCESplashScreen.h"
    "../../Vendor/juce/modules/juce_gui_basics/mouse/juce_ComponentDragger.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/mouse/juce_ComponentDragger.h"
    "../../Vendor/juce/modules/juce_gui_basics/mouse/juce_DragAndDropContainer.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/mouse/juce_DragAndDropContainer.h"
    "../../Vendor/juce/modules/juce_gui_basics/mouse/juce_DragAndDropTarget.h"
    "../../Vendor/juce/modules/juce_gui_basics/mouse/juce_FileDragAndDropTarget.h"
    "../../Vendor/juce/modules/juce_gui_basics/mouse/juce_LassoComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/mouse/juce_MouseCursor.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/mouse/juce_MouseCursor.h"
    "../../Vendor/juce/modules/juce_gui_basics/mouse/juce_MouseEvent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/mouse/juce_MouseEvent.h"
    "../../Vendor/juce/modules/juce_gui_basics/mouse/juce_MouseInactivityDetector.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/mouse/juce_MouseInactivityDetector.h"
    "../../Vendor/juce/modules/juce_gui_basics/mouse/juce_MouseInputSource.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/mouse/juce_MouseInputSource.h"
    "../../Vendor/juce/modules/juce_gui_basics/mouse/juce_MouseListener.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/mouse/juce_MouseListener.h"
    "../../Vendor/juce/modules/juce_gui_basics/mouse/juce_SelectedItemSet.h"
    "../../Vendor/juce/modules/juce_gui_basics/mouse/juce_TextDragAndDropTarget.h"
    "../../Vendor/juce/modules/juce_gui_basics/mouse/juce_TooltipClient.h"
    "../../Vendor/juce/modules/juce_gui_basics/native/juce_android_ContentSharer.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/native/juce_android_FileChooser.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/native/juce_android_Windowing.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/native/juce_common_MimeTypes.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/native/juce_ios_ContentSharer.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/native/juce_ios_FileChooser.mm"
    "../../Vendor/juce/modules/juce_gui_basics/native/juce_ios_UIViewComponentPeer.mm"
    "../../Vendor/juce/modules/juce_gui_basics/native/juce_ios_Windowing.mm"
    "../../Vendor/juce/modules/juce_gui_basics/native/juce_linux_FileChooser.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/native/juce_linux_X11.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/native/juce_linux_X11.h"
    "../../Vendor/juce/modules/juce_gui_basics/native/juce_linux_X11_Clipboard.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/native/juce_linux_X11_Windowing.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/native/juce_mac_FileChooser.mm"
    "../../Vendor/juce/modules/juce_gui_basics/native/juce_mac_MainMenu.mm"
    "../../Vendor/juce/modules/juce_gui_basics/native/juce_mac_MouseCursor.mm"
    "../../Vendor/juce/modules/juce_gui_basics/native/juce_mac_NSViewComponentPeer.mm"
    "../../Vendor/juce/modules/juce_gui_basics/native/juce_mac_Windowing.mm"
    "../../Vendor/juce/modules/juce_gui_basics/native/juce_MultiTouchMapper.h"
    "../../Vendor/juce/modules/juce_gui_basics/native/juce_win32_DragAndDrop.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/native/juce_win32_FileChooser.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/native/juce_win32_Windowing.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/positioning/juce_MarkerList.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/positioning/juce_MarkerList.h"
    "../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativeCoordinate.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativeCoordinate.h"
    "../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativeCoordinatePositioner.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativeCoordinatePositioner.h"
    "../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativeParallelogram.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativeParallelogram.h"
    "../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativePoint.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativePoint.h"
    "../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativePointPath.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativePointPath.h"
    "../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativeRectangle.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativeRectangle.h"
    "../../Vendor/juce/modules/juce_gui_basics/properties/juce_BooleanPropertyComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/properties/juce_BooleanPropertyComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/properties/juce_ButtonPropertyComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/properties/juce_ButtonPropertyComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/properties/juce_ChoicePropertyComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/properties/juce_ChoicePropertyComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/properties/juce_MultiChoicePropertyComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/properties/juce_MultiChoicePropertyComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/properties/juce_PropertyComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/properties/juce_PropertyComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/properties/juce_PropertyPanel.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/properties/juce_PropertyPanel.h"
    "../../Vendor/juce/modules/juce_gui_basics/properties/juce_SliderPropertyComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/properties/juce_SliderPropertyComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/properties/juce_TextPropertyComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/properties/juce_TextPropertyComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ComboBox.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ComboBox.h"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ImageComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ImageComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_Label.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_Label.h"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ListBox.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ListBox.h"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ProgressBar.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ProgressBar.h"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_Slider.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_Slider.h"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_TableHeaderComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_TableHeaderComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_TableListBox.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_TableListBox.h"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_TextEditor.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_TextEditor.h"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_Toolbar.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_Toolbar.h"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ToolbarItemComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ToolbarItemComponent.h"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ToolbarItemFactory.h"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ToolbarItemPalette.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ToolbarItemPalette.h"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_TreeView.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/widgets/juce_TreeView.h"
    "../../Vendor/juce/modules/juce_gui_basics/windows/juce_AlertWindow.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/windows/juce_AlertWindow.h"
    "../../Vendor/juce/modules/juce_gui_basics/windows/juce_CallOutBox.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/windows/juce_CallOutBox.h"
    "../../Vendor/juce/modules/juce_gui_basics/windows/juce_ComponentPeer.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/windows/juce_ComponentPeer.h"
    "../../Vendor/juce/modules/juce_gui_basics/windows/juce_DialogWindow.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/windows/juce_DialogWindow.h"
    "../../Vendor/juce/modules/juce_gui_basics/windows/juce_DocumentWindow.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/windows/juce_DocumentWindow.h"
    "../../Vendor/juce/modules/juce_gui_basics/windows/juce_NativeMessageBox.h"
    "../../Vendor/juce/modules/juce_gui_basics/windows/juce_ResizableWindow.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/windows/juce_ResizableWindow.h"
    "../../Vendor/juce/modules/juce_gui_basics/windows/juce_ThreadWithProgressWindow.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/windows/juce_ThreadWithProgressWindow.h"
    "../../Vendor/juce/modules/juce_gui_basics/windows/juce_TooltipWindow.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/windows/juce_TooltipWindow.h"
    "../../Vendor/juce/modules/juce_gui_basics/windows/juce_TopLevelWindow.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/windows/juce_TopLevelWindow.h"
    "../../Vendor/juce/modules/juce_gui_basics/juce_gui_basics.cpp"
    "../../Vendor/juce/modules/juce_gui_basics/juce_gui_basics.mm"
    "../../Vendor/juce/modules/juce_gui_basics/juce_gui_basics.h"
    "../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_CodeDocument.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_CodeDocument.h"
    "../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_CodeEditorComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_CodeEditorComponent.h"
    "../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_CodeTokeniser.h"
    "../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_CPlusPlusCodeTokeniser.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_CPlusPlusCodeTokeniser.h"
    "../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_CPlusPlusCodeTokeniserFunctions.h"
    "../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_LuaCodeTokeniser.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_LuaCodeTokeniser.h"
    "../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_XMLCodeTokeniser.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_XMLCodeTokeniser.h"
    "../../Vendor/juce/modules/juce_gui_extra/documents/juce_FileBasedDocument.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/documents/juce_FileBasedDocument.h"
    "../../Vendor/juce/modules/juce_gui_extra/embedding/juce_ActiveXControlComponent.h"
    "../../Vendor/juce/modules/juce_gui_extra/embedding/juce_AndroidViewComponent.h"
    "../../Vendor/juce/modules/juce_gui_extra/embedding/juce_NSViewComponent.h"
    "../../Vendor/juce/modules/juce_gui_extra/embedding/juce_UIViewComponent.h"
    "../../Vendor/juce/modules/juce_gui_extra/embedding/juce_XEmbedComponent.h"
    "../../Vendor/juce/modules/juce_gui_extra/misc/juce_AnimatedAppComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/misc/juce_AnimatedAppComponent.h"
    "../../Vendor/juce/modules/juce_gui_extra/misc/juce_AppleRemote.h"
    "../../Vendor/juce/modules/juce_gui_extra/misc/juce_BubbleMessageComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/misc/juce_BubbleMessageComponent.h"
    "../../Vendor/juce/modules/juce_gui_extra/misc/juce_ColourSelector.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/misc/juce_ColourSelector.h"
    "../../Vendor/juce/modules/juce_gui_extra/misc/juce_KeyMappingEditorComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/misc/juce_KeyMappingEditorComponent.h"
    "../../Vendor/juce/modules/juce_gui_extra/misc/juce_LiveConstantEditor.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/misc/juce_LiveConstantEditor.h"
    "../../Vendor/juce/modules/juce_gui_extra/misc/juce_PreferencesPanel.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/misc/juce_PreferencesPanel.h"
    "../../Vendor/juce/modules/juce_gui_extra/misc/juce_PushNotifications.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/misc/juce_PushNotifications.h"
    "../../Vendor/juce/modules/juce_gui_extra/misc/juce_RecentlyOpenedFilesList.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/misc/juce_RecentlyOpenedFilesList.h"
    "../../Vendor/juce/modules/juce_gui_extra/misc/juce_SplashScreen.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/misc/juce_SplashScreen.h"
    "../../Vendor/juce/modules/juce_gui_extra/misc/juce_SystemTrayIconComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/misc/juce_SystemTrayIconComponent.h"
    "../../Vendor/juce/modules/juce_gui_extra/misc/juce_WebBrowserComponent.h"
    "../../Vendor/juce/modules/juce_gui_extra/native/juce_android_PushNotifications.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/native/juce_android_WebBrowserComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/native/juce_AndroidViewComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/native/juce_ios_PushNotifications.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/native/juce_ios_UIViewComponent.mm"
    "../../Vendor/juce/modules/juce_gui_extra/native/juce_linux_X11_SystemTrayIcon.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/native/juce_linux_X11_WebBrowserComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/native/juce_linux_XEmbedComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/native/juce_mac_AppleRemote.mm"
    "../../Vendor/juce/modules/juce_gui_extra/native/juce_mac_CarbonViewWrapperComponent.h"
    "../../Vendor/juce/modules/juce_gui_extra/native/juce_mac_NSViewComponent.mm"
    "../../Vendor/juce/modules/juce_gui_extra/native/juce_mac_PushNotifications.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/native/juce_mac_SystemTrayIcon.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/native/juce_mac_WebBrowserComponent.mm"
    "../../Vendor/juce/modules/juce_gui_extra/native/juce_win32_ActiveXComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/native/juce_win32_SystemTrayIcon.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/native/juce_win32_WebBrowserComponent.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/juce_gui_extra.cpp"
    "../../Vendor/juce/modules/juce_gui_extra/juce_gui_extra.mm"
    "../../Vendor/juce/modules/juce_gui_extra/juce_gui_extra.h"
    "../../JuceLibraryCode/AppConfig.h"
    "../../JuceLibraryCode/include_juce_audio_basics.cpp"
    "../../JuceLibraryCode/include_juce_audio_plugin_client_utils.cpp"
    "../../JuceLibraryCode/include_juce_audio_processors.cpp"
    "../../JuceLibraryCode/include_juce_core.cpp"
    "../../JuceLibraryCode/include_juce_data_structures.cpp"
    "../../JuceLibraryCode/include_juce_events.cpp"
    "../../JuceLibraryCode/include_juce_graphics.cpp"
    "../../JuceLibraryCode/include_juce_gui_basics.cpp"
    "../../JuceLibraryCode/include_juce_gui_extra.cpp"
    "../../JuceLibraryCode/JuceHeader.h"
)

set_source_files_properties ("../../Source/editor/MainEditor.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Source/util/PatternUtil.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Source/ArpEvent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Source/ArpIntegrityException.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Source/ArpNote.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Source/ArpPattern.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Source/LibreArp.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Source/NoteData.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/audio_play_head/juce_AudioPlayHead.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/buffers/juce_AudioChannelSet.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/buffers/juce_AudioChannelSet.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/buffers/juce_AudioDataConverters.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/buffers/juce_AudioDataConverters.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/buffers/juce_AudioSampleBuffer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/buffers/juce_FloatVectorOperations.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/buffers/juce_FloatVectorOperations.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/effects/juce_CatmullRomInterpolator.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/effects/juce_CatmullRomInterpolator.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/effects/juce_Decibels.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/effects/juce_IIRFilter.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/effects/juce_IIRFilter.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/effects/juce_LagrangeInterpolator.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/effects/juce_LagrangeInterpolator.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/effects/juce_LinearSmoothedValue.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/effects/juce_Reverb.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiBuffer.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiBuffer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiFile.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiFile.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiKeyboardState.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiKeyboardState.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiMessage.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiMessage.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiMessageSequence.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiMessageSequence.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiRPN.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/midi/juce_MidiRPN.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPEInstrument.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPEInstrument.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPEMessages.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPEMessages.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPENote.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPENote.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPESynthesiser.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPESynthesiser.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPESynthesiserBase.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPESynthesiserBase.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPESynthesiserVoice.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPESynthesiserVoice.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPEUtils.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPEUtils.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPEValue.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPEValue.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPEZoneLayout.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/mpe/juce_MPEZoneLayout.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/native/juce_mac_CoreAudioLayouts.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/sources/juce_AudioSource.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/sources/juce_BufferingAudioSource.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/sources/juce_BufferingAudioSource.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/sources/juce_ChannelRemappingAudioSource.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/sources/juce_ChannelRemappingAudioSource.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/sources/juce_IIRFilterAudioSource.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/sources/juce_IIRFilterAudioSource.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/sources/juce_MemoryAudioSource.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/sources/juce_MemoryAudioSource.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/sources/juce_MixerAudioSource.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/sources/juce_MixerAudioSource.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/sources/juce_PositionableAudioSource.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/sources/juce_ResamplingAudioSource.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/sources/juce_ResamplingAudioSource.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/sources/juce_ReverbAudioSource.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/sources/juce_ReverbAudioSource.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/sources/juce_ToneGeneratorAudioSource.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/sources/juce_ToneGeneratorAudioSource.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/synthesisers/juce_Synthesiser.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/synthesisers/juce_Synthesiser.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/juce_audio_basics.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/juce_audio_basics.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_basics/juce_audio_basics.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUBase.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUBase.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUBaseHelper.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUBuffer.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUBuffer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUCarbonViewBase.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUCarbonViewBase.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUCarbonViewControl.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUCarbonViewControl.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUCarbonViewDispatch.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUDispatch.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUDispatch.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUInputElement.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUInputElement.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUInputFormatConverter.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUMIDIBase.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUMIDIBase.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUOutputBase.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUOutputBase.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUOutputElement.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUOutputElement.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUPlugInDispatch.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUPlugInDispatch.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUScopeElement.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUScopeElement.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUSilentTimeout.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUTimestampGenerator.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/AUViewLocalizedStringKeys.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAAtomic.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAAtomicStack.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAAudioChannelLayout.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAAudioChannelLayout.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAAUParameter.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAAUParameter.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAAutoDisposer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CADebugMacros.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CADebugPrintf.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAException.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAHostTimeBase.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAMath.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAMutex.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAMutex.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CarbonEventHandler.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CarbonEventHandler.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAReferenceCounted.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAStreamBasicDescription.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAStreamBasicDescription.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAThreadSafeList.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAVectorUnit.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAVectorUnit.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAVectorUnitTypes.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/CAXException.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/ComponentBase.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/ComponentBase.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/MusicDeviceBase.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/AU/CoreAudioUtilityClasses/MusicDeviceBase.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/Standalone/juce_StandaloneFilterApp.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/Standalone/juce_StandaloneFilterWindow.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/utility/juce_CarbonVisibility.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/utility/juce_CheckSettingMacros.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/utility/juce_FakeMouseMoveGenerator.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/utility/juce_IncludeModuleHeaders.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/utility/juce_IncludeSystemHeaders.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/utility/juce_PluginHostType.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/utility/juce_PluginUtilities.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/utility/juce_WindowsHooks.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/VST/juce_VST_Wrapper.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/VST/juce_VST_Wrapper.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/VST/juce_VSTCallbackHandler.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/juce_audio_plugin_client_utils.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/juce_audio_plugin_client_VST_utils.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/juce_audio_plugin_client.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/format/juce_AudioPluginFormat.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/format/juce_AudioPluginFormat.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/format/juce_AudioPluginFormatManager.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/format/juce_AudioPluginFormatManager.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/format_types/juce_AudioUnitPluginFormat.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/format_types/juce_AudioUnitPluginFormat.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/format_types/juce_LADSPAPluginFormat.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/format_types/juce_LADSPAPluginFormat.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/format_types/juce_LegacyAudioParameter.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/format_types/juce_VST3Common.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/format_types/juce_VST3Headers.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/format_types/juce_VST3PluginFormat.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/format_types/juce_VST3PluginFormat.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/format_types/juce_VSTCommon.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/format_types/juce_VSTInterface.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/format_types/juce_VSTMidiEventList.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/format_types/juce_VSTPluginFormat.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/format_types/juce_VSTPluginFormat.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/processors/juce_AudioPluginInstance.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/processors/juce_AudioPluginInstance.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/processors/juce_AudioProcessor.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/processors/juce_AudioProcessor.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/processors/juce_AudioProcessorEditor.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/processors/juce_AudioProcessorEditor.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/processors/juce_AudioProcessorGraph.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/processors/juce_AudioProcessorGraph.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/processors/juce_AudioProcessorListener.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/processors/juce_AudioProcessorParameter.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/processors/juce_GenericAudioProcessorEditor.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/processors/juce_GenericAudioProcessorEditor.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/processors/juce_PluginDescription.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/processors/juce_PluginDescription.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/scanning/juce_KnownPluginList.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/scanning/juce_KnownPluginList.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/scanning/juce_PluginDirectoryScanner.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/scanning/juce_PluginDirectoryScanner.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/scanning/juce_PluginListComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/scanning/juce_PluginListComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/utilities/juce_AudioParameterBool.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/utilities/juce_AudioParameterChoice.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/utilities/juce_AudioParameterFloat.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/utilities/juce_AudioParameterInt.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/utilities/juce_AudioProcessorParameters.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/utilities/juce_AudioProcessorParameterWithID.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/utilities/juce_AudioProcessorValueTreeState.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/utilities/juce_AudioProcessorValueTreeState.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/juce_audio_processors.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/juce_audio_processors.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_audio_processors/juce_audio_processors.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/containers/juce_AbstractFifo.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/containers/juce_AbstractFifo.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/containers/juce_Array.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/containers/juce_ArrayAllocationBase.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/containers/juce_DynamicObject.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/containers/juce_DynamicObject.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/containers/juce_ElementComparator.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/containers/juce_HashMap.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/containers/juce_HashMap_test.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/containers/juce_LinkedListPointer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/containers/juce_ListenerList.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/containers/juce_NamedValueSet.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/containers/juce_NamedValueSet.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/containers/juce_OwnedArray.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/containers/juce_PropertySet.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/containers/juce_PropertySet.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/containers/juce_ReferenceCountedArray.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/containers/juce_ScopedValueSetter.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/containers/juce_SortedSet.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/containers/juce_SparseSet.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/containers/juce_SparseSet.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/containers/juce_Variant.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/containers/juce_Variant.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/files/juce_DirectoryIterator.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/files/juce_DirectoryIterator.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/files/juce_File.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/files/juce_File.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/files/juce_FileFilter.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/files/juce_FileFilter.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/files/juce_FileInputStream.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/files/juce_FileInputStream.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/files/juce_FileOutputStream.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/files/juce_FileOutputStream.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/files/juce_FileSearchPath.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/files/juce_FileSearchPath.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/files/juce_MemoryMappedFile.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/files/juce_TemporaryFile.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/files/juce_TemporaryFile.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/files/juce_WildcardFileFilter.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/files/juce_WildcardFileFilter.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/javascript/juce_Javascript.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/javascript/juce_Javascript.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/javascript/juce_JSON.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/javascript/juce_JSON.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/logging/juce_FileLogger.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/logging/juce_FileLogger.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/logging/juce_Logger.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/logging/juce_Logger.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/maths/juce_BigInteger.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/maths/juce_BigInteger.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/maths/juce_Expression.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/maths/juce_Expression.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/maths/juce_MathsFunctions.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/maths/juce_NormalisableRange.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/maths/juce_Random.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/maths/juce_Random.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/maths/juce_Range.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/maths/juce_StatisticsAccumulator.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/memory/juce_Atomic.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/memory/juce_ByteOrder.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/memory/juce_ContainerDeletePolicy.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/memory/juce_HeapBlock.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/memory/juce_LeakedObjectDetector.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/memory/juce_Memory.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/memory/juce_MemoryBlock.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/memory/juce_MemoryBlock.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/memory/juce_OptionalScopedPointer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/memory/juce_ReferenceCountedObject.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/memory/juce_ScopedPointer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/memory/juce_SharedResourcePointer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/memory/juce_Singleton.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/memory/juce_WeakReference.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/misc/juce_Result.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/misc/juce_Result.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/misc/juce_RuntimePermissions.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/misc/juce_RuntimePermissions.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/misc/juce_StdFunctionCompat.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/misc/juce_StdFunctionCompat.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/misc/juce_Uuid.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/misc/juce_Uuid.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/misc/juce_WindowsRegistry.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_android_Files.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_android_JNIHelpers.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_android_Misc.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_android_Network.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_android_RuntimePermissions.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_android_SystemStats.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_android_Threads.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_BasicNativeHeaders.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_curl_Network.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_linux_CommonFile.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_linux_Files.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_linux_Network.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_linux_SystemStats.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_linux_Threads.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_mac_ClangBugWorkaround.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_mac_Files.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_mac_Network.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_mac_Strings.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_mac_SystemStats.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_mac_Threads.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_osx_ObjCHelpers.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_posix_NamedPipe.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_posix_SharedCode.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_win32_ComSmartPtr.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_win32_Files.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_win32_Network.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_win32_Registry.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_win32_SystemStats.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/native/juce_win32_Threads.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/network/juce_IPAddress.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/network/juce_IPAddress.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/network/juce_MACAddress.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/network/juce_MACAddress.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/network/juce_NamedPipe.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/network/juce_NamedPipe.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/network/juce_Socket.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/network/juce_Socket.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/network/juce_URL.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/network/juce_URL.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/network/juce_WebInputStream.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/network/juce_WebInputStream.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/streams/juce_BufferedInputStream.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/streams/juce_BufferedInputStream.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/streams/juce_FileInputSource.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/streams/juce_FileInputSource.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/streams/juce_InputSource.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/streams/juce_InputStream.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/streams/juce_InputStream.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/streams/juce_MemoryInputStream.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/streams/juce_MemoryInputStream.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/streams/juce_MemoryOutputStream.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/streams/juce_MemoryOutputStream.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/streams/juce_OutputStream.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/streams/juce_OutputStream.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/streams/juce_SubregionStream.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/streams/juce_SubregionStream.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/streams/juce_URLInputSource.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/streams/juce_URLInputSource.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/system/juce_CompilerSupport.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/system/juce_PlatformDefs.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/system/juce_StandardHeader.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/system/juce_SystemStats.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/system/juce_SystemStats.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/system/juce_TargetPlatform.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_Base64.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_Base64.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_CharacterFunctions.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_CharacterFunctions.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_CharPointer_ASCII.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_CharPointer_UTF8.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_CharPointer_UTF16.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_CharPointer_UTF32.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_Identifier.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_Identifier.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_LocalisedStrings.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_LocalisedStrings.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_NewLine.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_String.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_String.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_StringArray.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_StringArray.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_StringPairArray.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_StringPairArray.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_StringPool.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_StringPool.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_StringRef.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_TextDiff.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/text/juce_TextDiff.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/threads/juce_ChildProcess.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/threads/juce_ChildProcess.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/threads/juce_CriticalSection.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/threads/juce_DynamicLibrary.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/threads/juce_HighResolutionTimer.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/threads/juce_HighResolutionTimer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/threads/juce_InterProcessLock.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/threads/juce_Process.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/threads/juce_ReadWriteLock.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/threads/juce_ReadWriteLock.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/threads/juce_ScopedLock.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/threads/juce_ScopedReadLock.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/threads/juce_ScopedWriteLock.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/threads/juce_SpinLock.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/threads/juce_Thread.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/threads/juce_Thread.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/threads/juce_ThreadLocalValue.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/threads/juce_ThreadPool.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/threads/juce_ThreadPool.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/threads/juce_TimeSliceThread.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/threads/juce_TimeSliceThread.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/threads/juce_WaitableEvent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/time/juce_PerformanceCounter.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/time/juce_PerformanceCounter.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/time/juce_RelativeTime.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/time/juce_RelativeTime.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/time/juce_Time.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/time/juce_Time.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/unit_tests/juce_UnitTest.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/unit_tests/juce_UnitTest.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/xml/juce_XmlDocument.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/xml/juce_XmlDocument.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/xml/juce_XmlElement.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/xml/juce_XmlElement.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/zlib/adler32.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/zlib/compress.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/zlib/crc32.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/zlib/crc32.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/zlib/deflate.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/zlib/deflate.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/zlib/infback.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/zlib/inffast.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/zlib/inffast.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/zlib/inffixed.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/zlib/inflate.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/zlib/inflate.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/zlib/inftrees.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/zlib/inftrees.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/zlib/trees.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/zlib/trees.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/zlib/uncompr.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/zlib/zconf.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/zlib/zconf.in.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/zlib/zlib.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/zlib/zutil.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/zlib/zutil.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/juce_GZIPCompressorOutputStream.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/juce_GZIPCompressorOutputStream.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/juce_GZIPDecompressorInputStream.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/juce_GZIPDecompressorInputStream.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/juce_ZipFile.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/zip/juce_ZipFile.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/juce_core.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/juce_core.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_core/juce_core.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_data_structures/app_properties/juce_ApplicationProperties.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_data_structures/app_properties/juce_ApplicationProperties.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_data_structures/app_properties/juce_PropertiesFile.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_data_structures/app_properties/juce_PropertiesFile.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_data_structures/undomanager/juce_UndoableAction.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_data_structures/undomanager/juce_UndoManager.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_data_structures/undomanager/juce_UndoManager.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_data_structures/values/juce_CachedValue.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_data_structures/values/juce_CachedValue.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_data_structures/values/juce_Value.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_data_structures/values/juce_Value.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_data_structures/values/juce_ValueTree.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_data_structures/values/juce_ValueTree.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_data_structures/values/juce_ValueTreeSynchroniser.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_data_structures/values/juce_ValueTreeSynchroniser.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_data_structures/values/juce_ValueWithDefault.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_data_structures/juce_data_structures.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_data_structures/juce_data_structures.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_data_structures/juce_data_structures.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/broadcasters/juce_ActionBroadcaster.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/broadcasters/juce_ActionBroadcaster.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/broadcasters/juce_ActionListener.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/broadcasters/juce_AsyncUpdater.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/broadcasters/juce_AsyncUpdater.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/broadcasters/juce_ChangeBroadcaster.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/broadcasters/juce_ChangeBroadcaster.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/broadcasters/juce_ChangeListener.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/interprocess/juce_ConnectedChildProcess.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/interprocess/juce_ConnectedChildProcess.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/interprocess/juce_InterprocessConnection.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/interprocess/juce_InterprocessConnection.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/interprocess/juce_InterprocessConnectionServer.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/interprocess/juce_InterprocessConnectionServer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/messages/juce_ApplicationBase.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/messages/juce_ApplicationBase.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/messages/juce_CallbackMessage.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/messages/juce_DeletedAtShutdown.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/messages/juce_DeletedAtShutdown.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/messages/juce_Initialisation.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/messages/juce_Message.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/messages/juce_MessageListener.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/messages/juce_MessageListener.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/messages/juce_MessageManager.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/messages/juce_MessageManager.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/messages/juce_MountedVolumeListChangeDetector.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/messages/juce_NotificationType.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/native/juce_android_Messaging.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/native/juce_ios_MessageManager.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/native/juce_linux_EventLoop.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/native/juce_linux_Messaging.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/native/juce_mac_MessageManager.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/native/juce_osx_MessageQueue.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/native/juce_win32_HiddenMessageWindow.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/native/juce_win32_Messaging.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/native/juce_win32_WinRTWrapper.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/native/juce_win32_WinRTWrapper.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/timers/juce_MultiTimer.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/timers/juce_MultiTimer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/timers/juce_Timer.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/timers/juce_Timer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/juce_events.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/juce_events.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_events/juce_events.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/colour/juce_Colour.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/colour/juce_Colour.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/colour/juce_ColourGradient.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/colour/juce_ColourGradient.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/colour/juce_Colours.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/colour/juce_Colours.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/colour/juce_FillType.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/colour/juce_FillType.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/colour/juce_PixelFormats.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/contexts/juce_GraphicsContext.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/contexts/juce_GraphicsContext.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/contexts/juce_LowLevelGraphicsContext.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/contexts/juce_LowLevelGraphicsPostScriptRenderer.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/contexts/juce_LowLevelGraphicsPostScriptRenderer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/contexts/juce_LowLevelGraphicsSoftwareRenderer.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/contexts/juce_LowLevelGraphicsSoftwareRenderer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/effects/juce_DropShadowEffect.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/effects/juce_DropShadowEffect.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/effects/juce_GlowEffect.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/effects/juce_GlowEffect.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/effects/juce_ImageEffectFilter.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/fonts/juce_AttributedString.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/fonts/juce_AttributedString.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/fonts/juce_CustomTypeface.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/fonts/juce_CustomTypeface.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/fonts/juce_Font.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/fonts/juce_Font.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/fonts/juce_GlyphArrangement.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/fonts/juce_GlyphArrangement.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/fonts/juce_TextLayout.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/fonts/juce_TextLayout.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/fonts/juce_Typeface.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/fonts/juce_Typeface.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/geometry/juce_AffineTransform.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/geometry/juce_AffineTransform.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/geometry/juce_BorderSize.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/geometry/juce_EdgeTable.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/geometry/juce_EdgeTable.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/geometry/juce_Line.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/geometry/juce_Parallelogram.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/geometry/juce_Path.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/geometry/juce_Path.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/geometry/juce_PathIterator.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/geometry/juce_PathIterator.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/geometry/juce_PathStrokeType.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/geometry/juce_PathStrokeType.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/geometry/juce_Point.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/geometry/juce_Rectangle.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/geometry/juce_RectangleList.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/cderror.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/changes to libjpeg for JUCE.txt" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcapimin.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcapistd.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jccoefct.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jccolor.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcdctmgr.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jchuff.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jchuff.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcinit.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcmainct.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcmarker.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcmaster.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcomapi.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jconfig.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcparam.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcphuff.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcprepct.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jcsample.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jctrans.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdapimin.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdapistd.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdatasrc.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdcoefct.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdcolor.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdct.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jddctmgr.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdhuff.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdhuff.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdinput.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdmainct.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdmarker.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdmaster.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdmerge.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdphuff.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdpostct.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdsample.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jdtrans.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jerror.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jerror.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jfdctflt.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jfdctfst.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jfdctint.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jidctflt.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jidctfst.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jidctint.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jidctred.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jinclude.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jmemmgr.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jmemnobs.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jmemsys.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jmorecfg.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jpegint.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jpeglib.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jquant1.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jquant2.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jutils.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/jversion.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/transupp.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/jpglib/transupp.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/libpng_readme.txt" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/png.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/png.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngconf.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngerror.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngget.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pnginfo.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngmem.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngpread.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngpriv.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngread.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngrio.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngrtran.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngrutil.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngset.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngstruct.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngtrans.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngwio.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngwrite.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngwtran.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/pnglib/pngwutil.c" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/juce_GIFLoader.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/juce_JPEGLoader.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/image_formats/juce_PNGLoader.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/images/juce_Image.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/images/juce_Image.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/images/juce_ImageCache.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/images/juce_ImageCache.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/images/juce_ImageConvolutionKernel.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/images/juce_ImageConvolutionKernel.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/images/juce_ImageFileFormat.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/images/juce_ImageFileFormat.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/native/juce_android_Fonts.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/native/juce_android_GraphicsContext.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/native/juce_android_IconHelpers.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/native/juce_freetype_Fonts.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/native/juce_linux_Fonts.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/native/juce_linux_IconHelpers.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/native/juce_mac_CoreGraphicsContext.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/native/juce_mac_CoreGraphicsContext.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/native/juce_mac_CoreGraphicsHelpers.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/native/juce_mac_Fonts.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/native/juce_mac_IconHelpers.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/native/juce_RenderingHelpers.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/native/juce_win32_Direct2DGraphicsContext.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/native/juce_win32_Direct2DGraphicsContext.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/native/juce_win32_DirectWriteTypeface.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/native/juce_win32_DirectWriteTypeLayout.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/native/juce_win32_Fonts.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/native/juce_win32_IconHelpers.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/placement/juce_Justification.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/placement/juce_RectanglePlacement.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/placement/juce_RectanglePlacement.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/juce_graphics.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/juce_graphics.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_graphics/juce_graphics.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/application/juce_Application.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/application/juce_Application.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/buttons/juce_ArrowButton.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/buttons/juce_ArrowButton.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/buttons/juce_Button.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/buttons/juce_Button.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/buttons/juce_DrawableButton.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/buttons/juce_DrawableButton.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/buttons/juce_HyperlinkButton.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/buttons/juce_HyperlinkButton.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/buttons/juce_ImageButton.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/buttons/juce_ImageButton.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/buttons/juce_ShapeButton.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/buttons/juce_ShapeButton.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/buttons/juce_TextButton.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/buttons/juce_TextButton.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/buttons/juce_ToggleButton.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/buttons/juce_ToggleButton.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/buttons/juce_ToolbarButton.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/buttons/juce_ToolbarButton.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/commands/juce_ApplicationCommandID.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/commands/juce_ApplicationCommandInfo.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/commands/juce_ApplicationCommandInfo.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/commands/juce_ApplicationCommandManager.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/commands/juce_ApplicationCommandManager.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/commands/juce_ApplicationCommandTarget.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/commands/juce_ApplicationCommandTarget.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/commands/juce_KeyPressMappingSet.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/commands/juce_KeyPressMappingSet.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/components/juce_CachedComponentImage.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/components/juce_Component.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/components/juce_Component.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/components/juce_ComponentListener.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/components/juce_ComponentListener.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/components/juce_Desktop.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/components/juce_Desktop.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/components/juce_ModalComponentManager.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/components/juce_ModalComponentManager.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/drawables/juce_Drawable.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/drawables/juce_Drawable.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawableComposite.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawableComposite.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawableImage.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawableImage.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawablePath.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawablePath.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawableRectangle.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawableRectangle.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawableShape.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawableShape.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawableText.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/drawables/juce_DrawableText.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/drawables/juce_SVGParser.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_ContentSharer.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_ContentSharer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_DirectoryContentsDisplayComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_DirectoryContentsDisplayComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_DirectoryContentsList.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_DirectoryContentsList.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileBrowserComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileBrowserComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileBrowserListener.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileChooser.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileChooser.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileChooserDialogBox.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileChooserDialogBox.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileListComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileListComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FilenameComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FilenameComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FilePreviewComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileSearchPathListComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileSearchPathListComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileTreeComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_FileTreeComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_ImagePreviewComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/filebrowser/juce_ImagePreviewComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_CaretComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_CaretComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_KeyboardFocusTraverser.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_KeyboardFocusTraverser.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_KeyListener.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_KeyListener.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_KeyPress.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_KeyPress.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_ModifierKeys.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_ModifierKeys.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_SystemClipboard.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_TextEditorKeyMapper.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/keyboard/juce_TextInputTarget.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_AnimatedPosition.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_AnimatedPositionBehaviours.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_ComponentAnimator.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_ComponentAnimator.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_ComponentBoundsConstrainer.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_ComponentBoundsConstrainer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_ComponentBuilder.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_ComponentBuilder.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_ComponentMovementWatcher.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_ComponentMovementWatcher.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_ConcertinaPanel.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_ConcertinaPanel.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_FlexBox.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_FlexBox.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_FlexItem.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_Grid.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_Grid.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_GridItem.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_GridItem.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_GridUnitTests.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_GroupComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_GroupComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_MultiDocumentPanel.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_MultiDocumentPanel.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_ResizableBorderComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_ResizableBorderComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_ResizableCornerComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_ResizableCornerComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_ResizableEdgeComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_ResizableEdgeComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_ScrollBar.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_ScrollBar.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_SidePanel.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_SidePanel.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_StretchableLayoutManager.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_StretchableLayoutManager.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_StretchableLayoutResizerBar.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_StretchableLayoutResizerBar.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_StretchableObjectResizer.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_StretchableObjectResizer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_TabbedButtonBar.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_TabbedButtonBar.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_TabbedComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_TabbedComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_Viewport.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/layout/juce_Viewport.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V1.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V1.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V2.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V2.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V3.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V3.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V4.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V4.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/menus/juce_BurgerMenuComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/menus/juce_BurgerMenuComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/menus/juce_MenuBarComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/menus/juce_MenuBarComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/menus/juce_MenuBarModel.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/menus/juce_MenuBarModel.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/menus/juce_PopupMenu.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/menus/juce_PopupMenu.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/misc/juce_BubbleComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/misc/juce_BubbleComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/misc/juce_DropShadower.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/misc/juce_DropShadower.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/misc/juce_JUCESplashScreen.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/misc/juce_JUCESplashScreen.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/mouse/juce_ComponentDragger.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/mouse/juce_ComponentDragger.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/mouse/juce_DragAndDropContainer.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/mouse/juce_DragAndDropContainer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/mouse/juce_DragAndDropTarget.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/mouse/juce_FileDragAndDropTarget.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/mouse/juce_LassoComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/mouse/juce_MouseCursor.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/mouse/juce_MouseCursor.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/mouse/juce_MouseEvent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/mouse/juce_MouseEvent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/mouse/juce_MouseInactivityDetector.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/mouse/juce_MouseInactivityDetector.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/mouse/juce_MouseInputSource.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/mouse/juce_MouseInputSource.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/mouse/juce_MouseListener.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/mouse/juce_MouseListener.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/mouse/juce_SelectedItemSet.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/mouse/juce_TextDragAndDropTarget.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/mouse/juce_TooltipClient.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/native/juce_android_ContentSharer.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/native/juce_android_FileChooser.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/native/juce_android_Windowing.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/native/juce_common_MimeTypes.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/native/juce_ios_ContentSharer.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/native/juce_ios_FileChooser.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/native/juce_ios_UIViewComponentPeer.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/native/juce_ios_Windowing.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/native/juce_linux_FileChooser.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/native/juce_linux_X11.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/native/juce_linux_X11.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/native/juce_linux_X11_Clipboard.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/native/juce_linux_X11_Windowing.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/native/juce_mac_FileChooser.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/native/juce_mac_MainMenu.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/native/juce_mac_MouseCursor.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/native/juce_mac_NSViewComponentPeer.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/native/juce_mac_Windowing.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/native/juce_MultiTouchMapper.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/native/juce_win32_DragAndDrop.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/native/juce_win32_FileChooser.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/native/juce_win32_Windowing.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/positioning/juce_MarkerList.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/positioning/juce_MarkerList.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativeCoordinate.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativeCoordinate.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativeCoordinatePositioner.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativeCoordinatePositioner.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativeParallelogram.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativeParallelogram.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativePoint.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativePoint.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativePointPath.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativePointPath.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativeRectangle.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/positioning/juce_RelativeRectangle.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/properties/juce_BooleanPropertyComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/properties/juce_BooleanPropertyComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/properties/juce_ButtonPropertyComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/properties/juce_ButtonPropertyComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/properties/juce_ChoicePropertyComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/properties/juce_ChoicePropertyComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/properties/juce_MultiChoicePropertyComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/properties/juce_MultiChoicePropertyComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/properties/juce_PropertyComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/properties/juce_PropertyComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/properties/juce_PropertyPanel.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/properties/juce_PropertyPanel.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/properties/juce_SliderPropertyComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/properties/juce_SliderPropertyComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/properties/juce_TextPropertyComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/properties/juce_TextPropertyComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ComboBox.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ComboBox.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ImageComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ImageComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_Label.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_Label.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ListBox.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ListBox.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ProgressBar.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ProgressBar.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_Slider.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_Slider.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_TableHeaderComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_TableHeaderComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_TableListBox.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_TableListBox.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_TextEditor.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_TextEditor.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_Toolbar.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_Toolbar.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ToolbarItemComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ToolbarItemComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ToolbarItemFactory.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ToolbarItemPalette.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_ToolbarItemPalette.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_TreeView.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/widgets/juce_TreeView.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/windows/juce_AlertWindow.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/windows/juce_AlertWindow.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/windows/juce_CallOutBox.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/windows/juce_CallOutBox.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/windows/juce_ComponentPeer.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/windows/juce_ComponentPeer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/windows/juce_DialogWindow.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/windows/juce_DialogWindow.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/windows/juce_DocumentWindow.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/windows/juce_DocumentWindow.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/windows/juce_NativeMessageBox.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/windows/juce_ResizableWindow.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/windows/juce_ResizableWindow.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/windows/juce_ThreadWithProgressWindow.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/windows/juce_ThreadWithProgressWindow.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/windows/juce_TooltipWindow.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/windows/juce_TooltipWindow.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/windows/juce_TopLevelWindow.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/windows/juce_TopLevelWindow.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/juce_gui_basics.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/juce_gui_basics.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_basics/juce_gui_basics.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_CodeDocument.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_CodeDocument.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_CodeEditorComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_CodeEditorComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_CodeTokeniser.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_CPlusPlusCodeTokeniser.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_CPlusPlusCodeTokeniser.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_CPlusPlusCodeTokeniserFunctions.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_LuaCodeTokeniser.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_LuaCodeTokeniser.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_XMLCodeTokeniser.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/code_editor/juce_XMLCodeTokeniser.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/documents/juce_FileBasedDocument.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/documents/juce_FileBasedDocument.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/embedding/juce_ActiveXControlComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/embedding/juce_AndroidViewComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/embedding/juce_NSViewComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/embedding/juce_UIViewComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/embedding/juce_XEmbedComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/misc/juce_AnimatedAppComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/misc/juce_AnimatedAppComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/misc/juce_AppleRemote.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/misc/juce_BubbleMessageComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/misc/juce_BubbleMessageComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/misc/juce_ColourSelector.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/misc/juce_ColourSelector.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/misc/juce_KeyMappingEditorComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/misc/juce_KeyMappingEditorComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/misc/juce_LiveConstantEditor.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/misc/juce_LiveConstantEditor.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/misc/juce_PreferencesPanel.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/misc/juce_PreferencesPanel.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/misc/juce_PushNotifications.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/misc/juce_PushNotifications.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/misc/juce_RecentlyOpenedFilesList.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/misc/juce_RecentlyOpenedFilesList.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/misc/juce_SplashScreen.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/misc/juce_SplashScreen.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/misc/juce_SystemTrayIconComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/misc/juce_SystemTrayIconComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/misc/juce_WebBrowserComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/native/juce_android_PushNotifications.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/native/juce_android_WebBrowserComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/native/juce_AndroidViewComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/native/juce_ios_PushNotifications.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/native/juce_ios_UIViewComponent.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/native/juce_linux_X11_SystemTrayIcon.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/native/juce_linux_X11_WebBrowserComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/native/juce_linux_XEmbedComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/native/juce_mac_AppleRemote.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/native/juce_mac_CarbonViewWrapperComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/native/juce_mac_NSViewComponent.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/native/juce_mac_PushNotifications.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/native/juce_mac_SystemTrayIcon.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/native/juce_mac_WebBrowserComponent.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/native/juce_win32_ActiveXComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/native/juce_win32_SystemTrayIcon.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/native/juce_win32_WebBrowserComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/juce_gui_extra.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/juce_gui_extra.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../Vendor/juce/modules/juce_gui_extra/juce_gui_extra.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../JuceLibraryCode/AppConfig.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties ("../../JuceLibraryCode/JuceHeader.h" PROPERTIES HEADER_FILE_ONLY TRUE)

add_library (VST MODULE
    "../../Vendor/juce/modules/juce_audio_plugin_client/juce_audio_plugin_client_VST2.cpp"
    "../../JuceLibraryCode/include_juce_audio_plugin_client_VST2.cpp"
)

set_source_files_properties ("../../Vendor/juce/modules/juce_audio_plugin_client/juce_audio_plugin_client_VST2.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)

set_target_properties (SHARED_CODE PROPERTIES PREFIX "")
set_target_properties (SHARED_CODE PROPERTIES SUFFIX ".lib")

set_target_properties (VST PROPERTIES PREFIX "")
set_target_properties (VST PROPERTIES SUFFIX ".dll")

#------------------------------------------------------------------------------
# Config: Debug
#------------------------------------------------------------------------------

if (CMAKE_BUILD_TYPE STREQUAL Debug)

include_directories (
    "."
    "../../JuceLibraryCode"
    "../../Vendor/juce/modules"
)

set_target_properties (SHARED_CODE PROPERTIES
    OUTPUT_NAME "LibreArp"
    CXX_STANDARD 17
    CXX_EXTENSIONS OFF
)

target_compile_definitions (SHARED_CODE PRIVATE
    __MINGW__=1
    __MINGW_EXTENSION
    DEBUG=1
    _DEBUG=1
    JUCER_CODEBLOCKS_WINDOWS_8F9AFD66=1
    JUCE_APP_VERSION=0.0
    JUCE_APP_VERSION_HEX=0x0
    JucePlugin_Build_VST=1
    JucePlugin_Build_VST3=0
    JucePlugin_Build_AU=0
    JucePlugin_Build_AUv3=0
    JucePlugin_Build_RTAS=0
    JucePlugin_Build_AAX=0
    JucePlugin_Build_Standalone=0
    JUCE_SHARED_CODE=1
)

target_compile_options (SHARED_CODE PRIVATE
    "-m64"
    "-O0"
    "-mstackrealign"
    "-g"
)

target_link_libraries (SHARED_CODE PRIVATE
    -m64
    -lgdi32
    -luser32
    -lkernel32
    -lcomctl32
    -lcomdlg32
    -limm32
    -lole32
    -loleaut32
    -lrpcrt4
    -lshlwapi
    -luuid
    -lversion
    -lwininet
    -lwinmm
    -lws2_32
    -lwsock32
)

set_target_properties (VST PROPERTIES
    OUTPUT_NAME "LibreArp"
    CXX_STANDARD 17
    CXX_EXTENSIONS OFF
)

target_compile_definitions (VST PRIVATE
    __MINGW__=1
    __MINGW_EXTENSION
    DEBUG=1
    _DEBUG=1
    JUCER_CODEBLOCKS_WINDOWS_8F9AFD66=1
    JUCE_APP_VERSION=0.0
    JUCE_APP_VERSION_HEX=0x0
    JucePlugin_Build_VST=1
    JucePlugin_Build_VST3=0
    JucePlugin_Build_AU=0
    JucePlugin_Build_AUv3=0
    JucePlugin_Build_RTAS=0
    JucePlugin_Build_AAX=0
    JucePlugin_Build_Standalone=0
)

target_compile_options (VST PRIVATE
    "-m64"
    "-O0"
    "-mstackrealign"
    "-g"
)

target_link_libraries (VST PRIVATE
    SHARED_CODE
    -L.
    "-L\"${CMAKE_CURRENT_SOURCE_DIR}/bin/Debug\""
    -m64
    -lgdi32
    -luser32
    -lkernel32
    -lcomctl32
    -lcomdlg32
    -limm32
    -lole32
    -loleaut32
    -lrpcrt4
    -lshlwapi
    -luuid
    -lversion
    -lwininet
    -lwinmm
    -lws2_32
    -lwsock32
)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-strict-aliasing -Wno-strict-overflow")
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_CXX_FLAGS}")

endif (CMAKE_BUILD_TYPE STREQUAL Debug)

#------------------------------------------------------------------------------
# Config: Release_64
#------------------------------------------------------------------------------

if (CMAKE_BUILD_TYPE STREQUAL Release_64)

include_directories (
    "."
    "../../JuceLibraryCode"
    "../../Vendor/juce/modules"
)

set_target_properties (SHARED_CODE PROPERTIES
    OUTPUT_NAME "LibreArp_64"
    CXX_STANDARD 17
    CXX_EXTENSIONS OFF
)

target_compile_definitions (SHARED_CODE PRIVATE
    __MINGW__=1
    __MINGW_EXTENSION
    NDEBUG=1
    JUCER_CODEBLOCKS_WINDOWS_8F9AFD66=1
    JUCE_APP_VERSION=0.0
    JUCE_APP_VERSION_HEX=0x0
    JucePlugin_Build_VST=1
    JucePlugin_Build_VST3=0
    JucePlugin_Build_AU=0
    JucePlugin_Build_AUv3=0
    JucePlugin_Build_RTAS=0
    JucePlugin_Build_AAX=0
    JucePlugin_Build_Standalone=0
    JUCE_SHARED_CODE=1
)

target_compile_options (SHARED_CODE PRIVATE
    "-m64"
    "-O3"
    "-mstackrealign"
)

target_link_libraries (SHARED_CODE PRIVATE
    -m64
    -s
    -lgdi32
    -luser32
    -lkernel32
    -lcomctl32
    -lcomdlg32
    -limm32
    -lole32
    -loleaut32
    -lrpcrt4
    -lshlwapi
    -luuid
    -lversion
    -lwininet
    -lwinmm
    -lws2_32
    -lwsock32
)

set_target_properties (VST PROPERTIES
    OUTPUT_NAME "LibreArp_64"
    CXX_STANDARD 17
    CXX_EXTENSIONS OFF
)

target_compile_definitions (VST PRIVATE
    __MINGW__=1
    __MINGW_EXTENSION
    NDEBUG=1
    JUCER_CODEBLOCKS_WINDOWS_8F9AFD66=1
    JUCE_APP_VERSION=0.0
    JUCE_APP_VERSION_HEX=0x0
    JucePlugin_Build_VST=1
    JucePlugin_Build_VST3=0
    JucePlugin_Build_AU=0
    JucePlugin_Build_AUv3=0
    JucePlugin_Build_RTAS=0
    JucePlugin_Build_AAX=0
    JucePlugin_Build_Standalone=0
)

target_compile_options (VST PRIVATE
    "-m64"
    "-O3"
    "-mstackrealign"
)

target_link_libraries (VST PRIVATE
    SHARED_CODE
    -L.
    "-L\"${CMAKE_CURRENT_SOURCE_DIR}/bin/Release_64\""
    -m64
    -s
    -lgdi32
    -luser32
    -lkernel32
    -lcomctl32
    -lcomdlg32
    -limm32
    -lole32
    -loleaut32
    -lrpcrt4
    -lshlwapi
    -luuid
    -lversion
    -lwininet
    -lwinmm
    -lws2_32
    -lwsock32
)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-strict-aliasing -Wno-strict-overflow")
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_CXX_FLAGS}")

endif (CMAKE_BUILD_TYPE STREQUAL Release_64)

#------------------------------------------------------------------------------
# Config: Release_32
#------------------------------------------------------------------------------

if (CMAKE_BUILD_TYPE STREQUAL Release_32)

include_directories (
    "."
    "../../JuceLibraryCode"
    "../../Vendor/juce/modules"
)

set_target_properties (SHARED_CODE PROPERTIES
    OUTPUT_NAME "LibreArp_32"
    CXX_STANDARD 17
    CXX_EXTENSIONS OFF
)

target_compile_definitions (SHARED_CODE PRIVATE
    __MINGW__=1
    __MINGW_EXTENSION
    NDEBUG=1
    JUCER_CODEBLOCKS_WINDOWS_8F9AFD66=1
    JUCE_APP_VERSION=0.0
    JUCE_APP_VERSION_HEX=0x0
    JucePlugin_Build_VST=1
    JucePlugin_Build_VST3=0
    JucePlugin_Build_AU=0
    JucePlugin_Build_AUv3=0
    JucePlugin_Build_RTAS=0
    JucePlugin_Build_AAX=0
    JucePlugin_Build_Standalone=0
    JUCE_SHARED_CODE=1
)

target_compile_options (SHARED_CODE PRIVATE
    "-m32"
    "-O3"
    "-mstackrealign"
)

target_link_libraries (SHARED_CODE PRIVATE
    -m32
    -s
    -lgdi32
    -luser32
    -lkernel32
    -lcomctl32
    -lcomdlg32
    -limm32
    -lole32
    -loleaut32
    -lrpcrt4
    -lshlwapi
    -luuid
    -lversion
    -lwininet
    -lwinmm
    -lws2_32
    -lwsock32
)

set_target_properties (VST PROPERTIES
    OUTPUT_NAME "LibreArp_32"
    CXX_STANDARD 17
    CXX_EXTENSIONS OFF
)

target_compile_definitions (VST PRIVATE
    __MINGW__=1
    __MINGW_EXTENSION
    NDEBUG=1
    JUCER_CODEBLOCKS_WINDOWS_8F9AFD66=1
    JUCE_APP_VERSION=0.0
    JUCE_APP_VERSION_HEX=0x0
    JucePlugin_Build_VST=1
    JucePlugin_Build_VST3=0
    JucePlugin_Build_AU=0
    JucePlugin_Build_AUv3=0
    JucePlugin_Build_RTAS=0
    JucePlugin_Build_AAX=0
    JucePlugin_Build_Standalone=0
)

target_compile_options (VST PRIVATE
    "-m32"
    "-O3"
    "-mstackrealign"
)

target_link_libraries (VST PRIVATE
    SHARED_CODE
    -L.
    "-L\"${CMAKE_CURRENT_SOURCE_DIR}/bin/Release_32\""
    -m32
    -s
    -lgdi32
    -luser32
    -lkernel32
    -lcomctl32
    -lcomdlg32
    -limm32
    -lole32
    -loleaut32
    -lrpcrt4
    -lshlwapi
    -luuid
    -lversion
    -lwininet
    -lwinmm
    -lws2_32
    -lwsock32
)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-strict-aliasing -Wno-strict-overflow")
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_CXX_FLAGS}")

endif (CMAKE_BUILD_TYPE STREQUAL Release_32)

endif()

