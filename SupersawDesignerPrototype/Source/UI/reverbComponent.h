/*
  ==============================================================================

    reverbComponent.h
    Created: 12 Apr 2021 1:02:09pm
    Author:  Mitchell Elliott

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class reverbComponent  : public juce::Component
{
public:
    reverbComponent(juce::AudioProcessorValueTreeState& apvts, juce::String sizeId, juce::String widthId, juce::String dampingId, juce::String freezeId, juce::String dryId, juce::String wetId);
    ~reverbComponent() override;

    void paint (juce::Graphics& g) override;
    
    void resized() override;

private:
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    void setSliderWithLabel (juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment);
    
    juce::Slider sizeSlider;
    juce::Slider widthSlider;
    juce::Slider dampingSlider;
    juce::Slider freezeSlider;
    juce::Slider drySlider;
    juce::Slider wetSlider;
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    std::unique_ptr<SliderAttachment> sizeAttachment;
    std::unique_ptr<SliderAttachment> widthAttachment;
    std::unique_ptr<SliderAttachment> dampingAttachment;
    std::unique_ptr<SliderAttachment> freezeAttachment;
    std::unique_ptr<SliderAttachment> dryAttachment;
    std::unique_ptr<SliderAttachment> wetAttachment;
    
    juce::Label sizeLabel{"Size", "Size"};
    juce::Label widthLabel {"Width", "Width"};
    juce::Label dampingLabel {"Damping", "Damping"};
    juce::Label freezeLabel {"Freeze", "Freeze"};
    juce::Label dryLabel {"Dry", "Dry"};
    juce::Label wetLabel {"Wet", "Wet"};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (reverbComponent)
};
