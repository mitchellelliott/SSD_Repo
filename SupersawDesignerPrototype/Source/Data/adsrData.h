/*
  ==============================================================================

    adsrData.h
    Created: 2 Mar 2021 11:40:39am
    Author:  Mitchell Elliott

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class AdsrData : public juce::ADSR
{
public:
    void updateADSR (const float attack, const float decay, const float sustain, const float release);
    
private:
    juce::ADSR::Parameters adsrParams;
};
