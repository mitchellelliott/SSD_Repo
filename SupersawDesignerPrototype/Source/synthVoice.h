/*
  ==============================================================================

    synthVoice.h
    Created: 2 Mar 2021 11:28:18am
    Author:  Mitchell Elliott

  ==============================================================================
*/

#pragma once
#include "SynthSound.h"
#include "Data/adsrData.h"
#include "Data/oscData.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound (juce::SynthesiserSound *sound) override;
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved (int newPitchWheelValue) override;
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples) override;
    
    void reset();
    
    std::array<OscData, 2>& getOscillator1() { return osc1; }
    std::array<OscData, 2>& getOscillator2() { return osc2; }
    AdsrData& getAdsr() { return adsr; }
    
    
private:
    static constexpr int numChannelsToProcess { 2 };
    std::array<OscData, numChannelsToProcess> osc1;
    std::array<OscData, numChannelsToProcess> osc2;
    
    AdsrData adsr;
    juce::AudioBuffer<float> synthBuffer;
    
    juce::dsp::Gain<float> gain;
    bool isPrepared {false};
    
    // Sine Wave  (return std::sin(x);)
    // Saw Wave  (return x / juce::MathConstants<float>::pi)
    // Square Wave (return x < 0.0f ? -1.0f : 1.0f;)
    
};
