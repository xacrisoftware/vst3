#include "PluginEditor.h"

LoFiCrusherAudioProcessorEditor::LoFiCrusherAudioProcessorEditor(LoFiCrusherAudioProcessor& p)
    : AudioProcessorEditor(&p), processor(p)
{
    setSize(360, 220);
    for (auto* slider : { &bits, &downsample, &mix })
    {
        slider->setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
        slider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 22);
        addAndMakeVisible(*slider);
    }
    bitsLabel.setText("BIT DEPTH", juce::dontSendNotification);
    downsampleLabel.setText("DOWNSAMPLE", juce::dontSendNotification);
    mixLabel.setText("MIX", juce::dontSendNotification);
    for (auto* label : { &bitsLabel, &downsampleLabel, &mixLabel })
    {
        label->setJustificationType(juce::Justification::centred);
        addAndMakeVisible(*label);
    }
    bitsAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "bits", bits);
    downsampleAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "downsample", downsample);
    mixAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "mix", mix);
}

void LoFiCrusherAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(24, 24, 24));
    g.setColour(juce::Colours::white);
    g.setFont(juce::Font(20.0f, juce::Font::bold));
    g.drawText("LOFI CRUSHER", 0, 12, getWidth(), 28, juce::Justification::centred);
}

void LoFiCrusherAudioProcessorEditor::resized()
{
    const int top = 58, width = getWidth() / 3;
    for (int i = 0; i < 3; ++i)
    {
        auto area = juce::Rectangle<int>(i * width, top, width, 150);
        auto* slider = i == 0 ? &bits : i == 1 ? &downsample : &mix;
        auto* label = i == 0 ? &bitsLabel : i == 1 ? &downsampleLabel : &mixLabel;
        label->setBounds(area.removeFromTop(24));
        slider->setBounds(area.reduced(8));
    }
}
