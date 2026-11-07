#pragma once
#include "PluginProcessor.h"

class LoFiCrusherAudioProcessorEditor final : public juce::AudioProcessorEditor
{
public:
    explicit LoFiCrusherAudioProcessorEditor(LoFiCrusherAudioProcessor&);
    void paint(juce::Graphics&) override;
    void resized() override;
private:
    LoFiCrusherAudioProcessor& processor;
    juce::Slider bits, downsample, mix;
    juce::Label bitsLabel, downsampleLabel, mixLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> bitsAttachment, downsampleAttachment, mixAttachment;
};
