/*
  ==============================================================================

    SynthSound.h
    Created: 2 Mar 2021 11:28:49am
    Author:  Mitchell Elliott

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote (int midiNoteNumber) override { return true; };
    bool appliesToChannel (int midiChannel) override { return true; };
};
