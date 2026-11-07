cmake_minimum_required(VERSION 3.22)
project(LoFiCrusher VERSION 1.0.0)

include(FetchContent)
FetchContent_Declare(juce
  GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
  GIT_TAG 8.0.4
  GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(juce)

juce_add_plugin(LoFiCrusher
  COMPANY_NAME "Simple Audio"
  IS_SYNTH FALSE
  NEEDS_MIDI_INPUT FALSE
  NEEDS_MIDI_OUTPUT FALSE
  IS_MIDI_EFFECT FALSE
  COPY_PLUGIN_AFTER_BUILD TRUE
  PLUGIN_MANUFACTURER_CODE SmpA
  PLUGIN_CODE LfCr
  FORMATS VST3
  PRODUCT_NAME "LoFi Crusher")

target_sources(LoFiCrusher PRIVATE
  Source/PluginProcessor.cpp
  Source/PluginProcessor.h
  Source/PluginEditor.cpp
  Source/PluginEditor.h)

target_compile_definitions(LoFiCrusher PRIVATE JUCE_WEB_BROWSER=0 JUCE_USE_CURL=0)
target_link_libraries(LoFiCrusher PRIVATE juce::juce_audio_utils)
