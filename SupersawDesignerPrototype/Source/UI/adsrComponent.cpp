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
    
    setSliderWithLabel(attackSlider, attackLabel, apvts, "ATTACK", attackAttachment);
    setSliderWithLabel(decaySlider, decayLabel, apvts, "DECAY", decayAttachment);
    setSliderWithLabel(sustainSlider, sustainLabel, apvts, "SUSTAIN", sustainAttachment);
    setSliderWithLabel(releaseSlider, releaseLabel, apvts, "RELEASE", releaseAttachment);

}

AdsrComponent::~AdsrComponent()
{
}

void AdsrComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds();
    auto labelSpace = bounds.removeFromTop(20.f);
    
    g.fillAll(juce::Colours::transparentBlack);
    g.setColour (juce::Colours::gold);
    g.setFont(15.0);

    g.drawText("Envelope", labelSpace.withX(5), juce::Justification::left);
    g.setColour(juce::Colours::white);
    g.drawRoundedRectangle(bounds.toFloat().reduced (5.0f), 5.0f, 2.0f);
    
}

void AdsrComponent::resized()
{
    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 10;
    const auto sliderWidth = bounds.getWidth() / 4 - padding;
    const auto sliderHeight = bounds.getHeight()- (45);
    const auto sliderStartX = padding;
    const auto sliderStartY = 50;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;
    const auto labelStart = sliderStartY - labelYOffset;
    
    
    attackSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    attackLabel.setBounds (attackSlider.getX(), labelStart, sliderWidth, labelHeight);
    
    decaySlider.setBounds(attackSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    decayLabel.setBounds(decaySlider.getX(), labelStart, sliderWidth, labelHeight);
    
    sustainSlider.setBounds(decaySlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    sustainLabel.setBounds(sustainSlider.getX(), labelStart, sliderWidth, labelHeight);
    
    releaseSlider.setBounds(sustainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    releaseLabel.setBounds(releaseSlider.getX(), labelStart, sliderWidth, labelHeight);
    
}

using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

void AdsrComponent::setSliderWithLabel (juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment)
{
    
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
    
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, paramId, slider);
    
    label.setColour (juce::Label::ColourIds::textColourId, juce::Colours::gold);
    label.setFont (15.0f);
    label.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (label);
    
}
