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
    void setOscTune (const int pitch);
    void setGain (const float levelInDecibels);
    void setFmOsc (const float freq, const float depth);
    void renderNextBlock (juce::dsp::AudioBlock<float>& block);
    float processNextSample(float input);
    void setParams(const int oscChoice, const float oscGain, const int oscTune, const float fmFreq, const float fmDepth);
    void resetAll();
    
private:
    juce::dsp::Oscillator<float> fmOsc { [](float x) { return std::sin (x); }};
    juce::dsp::Gain<float> gain;
    int lastPitch { 0 };
    int lastMidiNote { 0 };
    float fmDepth { 0.0f };
    float fmModulator { 0.0f };
    
};
