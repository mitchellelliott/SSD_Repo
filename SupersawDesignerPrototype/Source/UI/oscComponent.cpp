/*
  ==============================================================================

    oscComponent.cpp
    Created: 2 Mar 2021 11:41:28am
    Author:  Mitchell Elliott

  ==============================================================================
*/

#include <JuceHeader.h>
#include "oscComponent.h"

OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorId, juce::String gainId, juce::String tuneId, juce::String fmFreqId, juce::String fmDepthId)
{
    juce::StringArray choices { "Sine", "Saw" , "Square" };
    oscWaveSelector.addItemList (choices, 1);
    addAndMakeVisible (oscWaveSelector);

    oscWaveSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, waveSelectorId, oscWaveSelector);
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    gainSliderAttachment = std::make_unique<SliderAttachment>(apvts, gainId, gainSlider);
    tuneSliderAttachment = std::make_unique<SliderAttachment>(apvts, tuneId, tuneSlider);
    fmFreqSliderAttachment = std::make_unique<SliderAttachment>(apvts, fmFreqId, fmFreqSlider);
    fmDepthSliderAttachment = std::make_unique<SliderAttachment>(apvts, fmDepthId, fmDepthSlider);

    setSliderWithLabel(gainSlider, gainLabel, apvts, gainId, gainSliderAttachment);
    setSliderWithLabel(tuneSlider, detuneLabel, apvts, tuneId, tuneSliderAttachment);
    setSliderWithLabel(fmFreqSlider, fmFreqLabel, apvts, fmFreqId, fmFreqSliderAttachment);
    setSliderWithLabel(fmDepthSlider, fmDepthLabel, apvts, fmDepthId, fmDepthSliderAttachment);
    
}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds();
    auto labelSpace = bounds.removeFromTop(20.f);
    
    g.fillAll(juce::Colours::transparentBlack);
    g.setColour (juce::Colours::gold);
    g.setFont(15.0);

    g.drawText("Oscillator", labelSpace.withX(5), juce::Justification::left);
    g.setColour(juce::Colours::white);
    g.drawRoundedRectangle(bounds.toFloat().reduced (5.0f), 5.0f, 2.0f);

}

void OscComponent::resized()
{
    //Slider Visual Parameters
    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 10;
    const auto sliderWidth = bounds.getWidth()/5 - padding;
    const auto sliderHeight = bounds.getHeight() - 40;
    const auto sliderStartX = 125;
    const auto sliderStartY = 40;
    const auto labelYOffset = 15;
    const auto labelHeight = 20;
    const auto labelStart = sliderStartY-labelYOffset;
    
    oscWaveSelector.setBounds(padding*2,padding*5,100,60);
    
    gainSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    gainLabel.setBounds(gainSlider.getX(), labelStart, sliderWidth, labelHeight);
    
    tuneSlider.setBounds(gainSlider.getRight()+padding, sliderStartY, sliderWidth, sliderHeight);
    detuneLabel.setBounds(tuneSlider.getX(), labelStart, sliderWidth, labelHeight);
    
    fmFreqSlider.setBounds(tuneSlider.getRight()+padding, sliderStartY, sliderWidth, sliderHeight);
    fmFreqLabel.setBounds(fmFreqSlider.getX(), labelStart, sliderWidth, labelHeight);
    
    fmDepthSlider.setBounds(fmFreqSlider.getRight()+padding, sliderStartY, sliderWidth, sliderHeight);
    fmDepthLabel.setBounds(fmDepthSlider.getX(), labelStart, sliderWidth, labelHeight);
    
}

void OscComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    addAndMakeVisible(slider);
    
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, paramId, slider);
    
    label.setColour (juce::Label::ColourIds::textColourId, juce::Colours::gold);
    label.setFont (15.0f);
    label.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (label);
}
