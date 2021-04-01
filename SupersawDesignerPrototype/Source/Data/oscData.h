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
    void prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels);
    void setWaveType(const int choice);
    void setFreq (const int midiNoteNumber);
    void setGain (const float levelInDecibels);
    void renderNextBlock (juce::dsp::AudioBlock<float>& block);
    float processNextSample(float input);
    void setParams(const int oscChoice, const float oscGain);
    void resetAll();
    
private:
    
    juce::dsp::Gain<float> gain;
    
};
