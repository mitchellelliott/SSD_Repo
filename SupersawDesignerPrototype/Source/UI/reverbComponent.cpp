/*
  ==============================================================================

    reverbComponent.cpp
    Created: 12 Apr 2021 1:02:09pm
    Author:  Mitchell Elliott

  ==============================================================================
*/

#include <JuceHeader.h>
#include "reverbComponent.h"

//==============================================================================
reverbComponent::reverbComponent(juce::AudioProcessorValueTreeState& apvts, juce::String sizeId, juce::String widthId, juce::String dampingId, juce::String freezeId, juce::String dryId, juce::String wetId)
{

    setSliderWithLabel(sizeSlider, sizeLabel, apvts, sizeId, sizeAttachment);
    setSliderWithLabel(widthSlider, widthLabel, apvts, widthId, widthAttachment);
    setSliderWithLabel(dampingSlider, dampingLabel, apvts, dampingId, dampingAttachment);
    setSliderWithLabel(freezeSlider, freezeLabel, apvts, freezeId, freezeAttachment);
    setSliderWithLabel(drySlider, dryLabel, apvts, dryId, dryAttachment);
    setSliderWithLabel(wetSlider, wetLabel, apvts, wetId, wetAttachment);

}

reverbComponent::~reverbComponent()
{
}

void reverbComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::transparentBlack);
    auto bounds = getLocalBounds();
    g.setColour (juce::Colours::whitesmoke);
    g.drawRoundedRectangle(bounds.toFloat().reduced (5.0f), 5.0f, 2.0f);
    
    g.setColour (juce::Colours::goldenrod);
    g.setFont(15.0);
    g.setFont (g.getCurrentFont().bold);
}

void reverbComponent::resized()
{
    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 10;
    const auto sliderWidth = bounds.getWidth() / 6 - padding;
    const auto sliderHeight = bounds.getHeight()- (45);
    const auto sliderStartX = padding;
    const auto sliderStartY = 50;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;
    const auto labelStart = sliderStartY - labelYOffset;

    sizeSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    sizeLabel.setBounds(sizeSlider.getX(), labelStart, sliderWidth, labelHeight);
    
    widthSlider.setBounds(sizeSlider.getRight()+padding, sliderStartY, sliderWidth, sliderHeight);
    widthLabel.setBounds(widthSlider.getX(), labelStart, sliderWidth, labelHeight);
    
    dampingSlider.setBounds(widthSlider.getRight()+padding, sliderStartY, sliderWidth, sliderHeight);
    dampingLabel.setBounds(dampingSlider.getX(), labelStart, sliderWidth, labelHeight);
    
    freezeSlider.setBounds(dampingSlider.getRight()+padding, sliderStartY, sliderWidth, sliderHeight);
    freezeLabel.setBounds(freezeSlider.getX(), labelStart, sliderWidth, labelHeight);
    
    drySlider.setBounds(freezeSlider.getRight()+padding, sliderStartY, sliderWidth, sliderHeight);
    dryLabel.setBounds(drySlider.getX(), labelStart, sliderWidth, labelHeight);
    
    wetSlider.setBounds(drySlider.getRight()+padding, sliderStartY, sliderWidth, sliderHeight);
    wetLabel.setBounds(wetSlider.getX(), labelStart, sliderWidth, labelHeight);
    
    
}

using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

void reverbComponent::setSliderWithLabel(juce::Slider &slider, juce::Label &label, juce::AudioProcessorValueTreeState &apvts, juce::String paramId, std::unique_ptr<Attachment> &attachment){
    
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
    
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, paramId, slider);
    
    label.setColour (juce::Label::ColourIds::textColourId, juce::Colours::gold);
    label.setFont (15.0f);
    label.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (label);
    
}
