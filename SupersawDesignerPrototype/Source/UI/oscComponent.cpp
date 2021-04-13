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

    setSliderParams(gainSlider);
    setSliderParams(tuneSlider);
    setSliderParams(fmFreqSlider);
    setSliderParams(fmDepthSlider);
    
}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::transparentBlack);
    
}

void OscComponent::resized()
{
    //Slider Visual Parameters
    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 10;
    const auto sliderWidth = 200;
    const auto sliderHeight = getHeight() - padding;
    const auto sliderStartX = 125 ;
    const auto sliderStartY = 0;
    
    oscWaveSelector.setBounds(0,0,100,75);
    gainSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    tuneSlider.setBounds(gainSlider.getRight()+padding, sliderStartY, sliderWidth, sliderHeight);
    fmFreqSlider.setBounds(tuneSlider.getRight()+padding, sliderStartY, sliderWidth, sliderHeight);
    fmDepthSlider.setBounds(fmFreqSlider.getRight()+padding, sliderStartY, sliderWidth, sliderHeight);
    
}

void OscComponent::setSliderParams(juce::Slider& slider){
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
}
