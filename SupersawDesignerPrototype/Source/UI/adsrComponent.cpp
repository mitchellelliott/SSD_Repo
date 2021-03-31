/*
  ==============================================================================

    adsrComponent.cpp
    Created: 2 Mar 2021 11:41:16am
    Author:  Mitchell Elliott

  ==============================================================================
*/

#include <JuceHeader.h>
#include "adsrComponent.h"

AdsrComponent::AdsrComponent(juce::AudioProcessorValueTreeState& apvts)
{
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    attackAttachment = std::make_unique<SliderAttachment>(apvts, "ATTACK" , attackSlider);
    decayAttachment = std::make_unique<SliderAttachment>(apvts, "DECAY" , decaySlider);
    sustainAttachment = std::make_unique<SliderAttachment>(apvts, "SUSTAIN" , sustainSlider);
    releaseAttachment = std::make_unique<SliderAttachment>(apvts, "RELEASE" , releaseSlider);
    
    setSliderParams(attackSlider);
    setSliderParams(decaySlider);
    setSliderParams(sustainSlider);
    setSliderParams(releaseSlider);

}

AdsrComponent::~AdsrComponent()
{
}

void AdsrComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::transparentBlack);
    auto bounds = getLocalBounds();
    g.setColour (juce::Colours::whitesmoke);
    g.drawRoundedRectangle(bounds.toFloat().reduced (5.0f), 5.0f, 2.0f);
    
    g.setColour (juce::Colours::goldenrod);
    g.setFont(15.0);
    g.setFont (g.getCurrentFont().bold);
}

void AdsrComponent::resized()
{
    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 10;
    const auto sliderWidth = bounds.getWidth() / 4 - padding;
    const auto sliderHeight = bounds.getHeight()- (padding);
    const auto sliderStartX = padding;
    const auto sliderStartY = padding*2;
    
    attackSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    decaySlider.setBounds(attackSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    sustainSlider.setBounds(decaySlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    releaseSlider.setBounds(sustainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);

}

void AdsrComponent::setSliderParams (juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 25);
    addAndMakeVisible(slider);
}
