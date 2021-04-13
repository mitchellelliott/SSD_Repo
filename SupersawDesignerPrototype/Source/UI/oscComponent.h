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
    
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    void setSliderWithLabel (juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment);
    
    juce::Slider gainSlider;
    juce::Slider tuneSlider;
    juce::Slider fmFreqSlider;
    juce::Slider fmDepthSlider;
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    std::unique_ptr<SliderAttachment> gainSliderAttachment;
    std::unique_ptr<SliderAttachment> tuneSliderAttachment;
    std::unique_ptr<SliderAttachment> fmFreqSliderAttachment;
    std::unique_ptr<SliderAttachment> fmDepthSliderAttachment;
    
    juce::Label gainLabel{"Gain", "Gain"};
    juce::Label detuneLabel{"Detune", "Detune"};
    juce::Label fmFreqLabel {"FM Freq", "FM Freq"};
    juce::Label fmDepthLabel {"FM Depth", "FM Depth"};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};
