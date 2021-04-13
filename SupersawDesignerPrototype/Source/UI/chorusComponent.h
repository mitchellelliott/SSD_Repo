/*
  ==============================================================================

    chorusComponent.h
    Created: 12 Apr 2021 6:12:00pm
    Author:  Mitchell Elliott

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class chorusComponent  : public juce::Component
{
public:
    chorusComponent(juce::AudioProcessorValueTreeState& apvts, juce::String rateId, juce::String depthId, juce::String centreDelayId, juce::String feedbackId, juce::String mixId);
    ~chorusComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    void setSliderWithLabel (juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment);
    
    juce::Slider rateSlider;
    juce::Slider depthSlider;
    juce::Slider centreDelaySlider;
    juce::Slider feedbackSlider;
    juce::Slider mixSlider;
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    std::unique_ptr<SliderAttachment> rateAttachment;
    std::unique_ptr<SliderAttachment> depthAttachment;
    std::unique_ptr<SliderAttachment> centreDelayAttachment;
    std::unique_ptr<SliderAttachment> feedbackAttachment;
    std::unique_ptr<SliderAttachment> mixAttachment;
    
    juce::Label rateLabel {"RATE", "Rate"};
    juce::Label depthLabel {"DEPTH", "Depth"};
    juce::Label centreDelayLabel {"CENTREDELAY", "Delay"};
    juce::Label feedbackLabel {"FEEDBACK", "Feedback"};
    juce::Label mixLabel {"MIX", "Dry/Wet"};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (chorusComponent)
};
