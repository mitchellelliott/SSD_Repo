/*
  ==============================================================================

    oscComponent.h
    Created: 2 Mar 2021 11:41:28am
    Author:  Mitchell Elliott

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class OscComponent  : public juce::Component
{
public:
    OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorId, juce::String gainId, juce::String tuneId, juce::String fmFreqId, juce::String fmDepthId);
    ~OscComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox oscWaveSelector;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscWaveSelectorAttachment;
    
    void setSliderParams(juce::Slider& slider);
    
    juce::Slider gainSlider;
    juce::Slider tuneSlider;
    juce::Slider fmFreqSlider;
    juce::Slider fmDepthSlider;
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    std::unique_ptr<SliderAttachment> gainSliderAttachment;
    std::unique_ptr<SliderAttachment> tuneSliderAttachment;
    std::unique_ptr<SliderAttachment> fmFreqSliderAttachment;
    std::unique_ptr<SliderAttachment> fmDepthSliderAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};
