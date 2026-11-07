#pragma once
#include <JuceHeader.h>

class LoFiCrusherAudioProcessor final : public juce::AudioProcessor
{
public:
    LoFiCrusherAudioProcessor();
    ~LoFiCrusherAudioProcessor() override = default;

    void prepareToPlay(double, int) override;
    void releaseResources() override {}
    bool isBusesLayoutSupported(const BusesLayout&) const override;
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }
    const juce::String getName() const override { return "LoFi Crusher"; }
    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }
    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int) override {}
    const juce::String getProgramName(int) override { return {}; }
    void changeProgramName(int, const juce::String&) override {}
    void getStateInformation(juce::MemoryBlock&) override;
    void setStateInformation(const void*, int) override;

    juce::AudioProcessorValueTreeState parameters;

private:
    double sampleRate = 44100.0;
    float held[2] {};
    int counter = 0;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LoFiCrusherAudioProcessor)
};
