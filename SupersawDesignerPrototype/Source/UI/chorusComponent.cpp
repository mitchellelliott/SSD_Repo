/*
  ==============================================================================

    chorusComponent.cpp
    Created: 12 Apr 2021 6:12:00pm
    Author:  Mitchell Elliott

  ==============================================================================
*/

#include <JuceHeader.h>
#include "chorusComponent.h"

//==============================================================================
chorusComponent::chorusComponent(juce::AudioProcessorValueTreeState& apvts, juce::String rateId, juce::String depthId, juce::String centreDelayId, juce::String feedbackId, juce::String mixId)
{
  
    setSliderWithLabel(rateSlider, rateLabel, apvts, rateId, rateAttachment);
    setSliderWithLabel(depthSlider, depthLabel, apvts, depthId, depthAttachment);
    setSliderWithLabel(centreDelaySlider, centreDelayLabel, apvts, centreDelayId, centreDelayAttachment);
    setSliderWithLabel(feedbackSlider, feedbackLabel, apvts, feedbackId, feedbackAttachment);
    setSliderWithLabel(mixSlider, mixLabel, apvts, mixId, mixAttachment);

}

chorusComponent::~chorusComponent()
{
}

void chorusComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::transparentBlack);
    auto bounds = getLocalBounds();
    g.setColour (juce::Colours::whitesmoke);
    g.drawRoundedRectangle(bounds.toFloat().reduced (5.0f), 5.0f, 2.0f);
    
    g.setColour (juce::Colours::goldenrod);
    g.setFont(15.0);
    g.setFont (g.getCurrentFont().bold);
}

void chorusComponent::resized()
{

    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 10;
    const auto sliderWidth = bounds.getWidth() / 5 - padding;
    const auto sliderHeight = bounds.getHeight()- (45);
    const auto sliderStartX = padding;
    const auto sliderStartY = 50;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;
    const auto labelStart = sliderStartY - labelYOffset;
    
    rateSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    rateLabel.setBounds(rateSlider.getX(), labelStart, sliderWidth, labelHeight);
    
    depthSlider.setBounds(rateSlider.getRight()+padding, sliderStartY, sliderWidth, sliderHeight);
    depthLabel.setBounds(depthSlider.getX(), labelStart, sliderWidth, labelHeight);
    
    centreDelaySlider.setBounds(depthSlider.getRight()+padding, sliderStartY, sliderWidth, sliderHeight);
    centreDelayLabel.setBounds(centreDelaySlider.getX(), labelStart, sliderWidth, labelHeight);
    
    feedbackSlider.setBounds(centreDelaySlider.getRight()+padding, sliderStartY, sliderWidth, sliderHeight);
    feedbackLabel.setBounds(feedbackSlider.getX(), labelStart, sliderWidth, labelHeight);
    
    mixSlider.setBounds(feedbackSlider.getRight()+padding, sliderStartY, sliderWidth, sliderHeight);
    mixLabel.setBounds(mixSlider.getX(), labelStart, sliderWidth, labelHeight);
    

}

using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

void chorusComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment)
{
    
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
    
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, paramId, slider);
    
    label.setColour (juce::Label::ColourIds::textColourId, juce::Colours::gold);
    label.setFont (15.0f);
    label.setJustificationType (juce::Justification::centred);
    addAndMakeVisible(label);
    
}
