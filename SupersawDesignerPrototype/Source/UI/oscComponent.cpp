/*
  ==============================================================================

    oscComponent.cpp
    Created: 2 Mar 2021 11:41:28am
    Author:  Mitchell Elliott

  ==============================================================================
*/

#include <JuceHeader.h>
#include "oscComponent.h"

OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorId)
{
    juce::StringArray choices { "Sine", "Saw" , "Square" };
    oscWaveSelector.addItemList (choices, 1);
    addAndMakeVisible (oscWaveSelector);

    oscWaveSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, waveSelectorId, oscWaveSelector);
    
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
    oscWaveSelector.setBounds(0,0,150,75);
}

