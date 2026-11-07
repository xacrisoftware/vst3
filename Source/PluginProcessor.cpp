#include "PluginProcessor.h"
#include "PluginEditor.h"

LoFiCrusherAudioProcessor::LoFiCrusherAudioProcessor()
    : AudioProcessor(BusesProperties().withInput("Input", juce::AudioChannelSet::stereo(), true)
                                      .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
      parameters(*this, nullptr, "PARAMETERS", {
          std::make_unique<juce::AudioParameterFloat>("bits", "Bit Depth", juce::NormalisableRange<float>(4.0f, 16.0f, 1.0f), 8.0f),
          std::make_unique<juce::AudioParameterFloat>("downsample", "Downsample", juce::NormalisableRange<float>(1.0f, 20.0f, 1.0f), 8.0f),
          std::make_unique<juce::AudioParameterFloat>("mix", "Mix", 0.0f, 1.0f, 0.8f) }) {}

void LoFiCrusherAudioProcessor::prepareToPlay(double rate, int)
{
    sampleRate = rate;
    held[0] = held[1] = 0.0f;
    counter = 0;
}

bool LoFiCrusherAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    return layouts.getMainInputChannelSet() == juce::AudioChannelSet::mono()
        || layouts.getMainInputChannelSet() == juce::AudioChannelSet::stereo();
}

void LoFiCrusherAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;
    const auto bits = parameters.getRawParameterValue("bits")->load();
    const auto holdEvery = juce::jmax(1, (int) parameters.getRawParameterValue("downsample")->load());
    const auto mix = parameters.getRawParameterValue("mix")->load();
    const auto levels = std::pow(2.0f, bits - 1.0f);

    for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
    {
        if (counter++ % holdEvery == 0)
            for (int channel = 0; channel < buffer.getNumChannels() && channel < 2; ++channel)
                held[channel] = std::round(juce::jlimit(-1.0f, 1.0f, buffer.getSample(channel, sample)) * levels) / levels;

        for (int channel = 0; channel < buffer.getNumChannels() && channel < 2; ++channel)
        {
            const auto dry = buffer.getSample(channel, sample);
            buffer.setSample(channel, sample, dry + (held[channel] - dry) * mix);
        }
    }
}

void LoFiCrusherAudioProcessor::getStateInformation(juce::MemoryBlock& dest)
{
    if (auto state = parameters.copyState(); auto xml = state.createXml())
        copyXmlToBinary(*xml, dest);
}

void LoFiCrusherAudioProcessor::setStateInformation(const void* data, int size)
{
    if (auto xml = getXmlFromBinary(data, size); xml != nullptr)
        parameters.replaceState(juce::ValueTree::fromXml(*xml));
}

juce::AudioProcessorEditor* LoFiCrusherAudioProcessor::createEditor()
{
    return new LoFiCrusherAudioProcessorEditor(*this);
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new LoFiCrusherAudioProcessor();
}
