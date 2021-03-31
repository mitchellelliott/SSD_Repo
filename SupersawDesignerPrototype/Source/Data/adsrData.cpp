/*
  ==============================================================================

    adsrData.cpp
    Created: 2 Mar 2021 11:40:39am
    Author:  Mitchell Elliott

  ==============================================================================
*/

#include "adsrData.h"

void AdsrData::updateADSR (const float attack, const float decay, const float sustain, const float release)
{
    adsrParams.attack = attack;
    adsrParams.decay = decay;
    adsrParams.sustain = sustain;
    adsrParams.release = release;
    
    setParameters(adsrParams);
}
