/*
  ==============================================================================

    oscData.h
    Created: 2 Mar 2021 11:40:50am
    Author:  Mitchell Elliott

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class OscData : public juce::dsp::Oscillator<float>
{
public:
    void prepareToPlay (juce::dsp::ProcessSpec& spec);
    void setWaveType(const int choice);
    void setWaveFrequency(const int midiNoteNumber);
    void getNextAudioBlock (juce::dsp::AudioBlock<float>& block);
    
private:
    
    
};
