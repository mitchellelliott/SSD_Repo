/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "synthVoice.h"
#include "UI/adsrComponent.h"
#include "UI/oscComponent.h"
#include "UI/reverbComponent.h"

//==============================================================================
/**
*/
class SupersawDesignerPrototypeAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                                        public juce::Slider::Listener

{
public:
    SupersawDesignerPrototypeAudioProcessorEditor (SupersawDesignerPrototypeAudioProcessor&);
    ~SupersawDesignerPrototypeAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void sliderValueChanged(juce::Slider * slider) override;
    
    //Slider Visual Parameters
    const int padding = 50;
    const int sliderWidth = 100;
    const int sliderHeight = 100;
    const int sliderStartX = 150;
    const int sliderStartY = 60;
    const int verticalPadding = 175;

private:
    SupersawDesignerPrototypeAudioProcessor& audioProcessor;
    OscComponent osc1;
    OscComponent osc2;
    AdsrComponent adsr;
    reverbComponent reverb;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SupersawDesignerPrototypeAudioProcessorEditor);
};
