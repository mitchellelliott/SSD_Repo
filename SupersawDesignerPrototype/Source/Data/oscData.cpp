/*
  ==============================================================================

    oscData.cpp
    Created: 2 Mar 2021 11:40:50am
    Author:  Mitchell Elliott

  ==============================================================================
*/

#include "oscData.h"

void OscData::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    
    
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;
    
    prepare(spec);
    
}

void OscData::setWaveType(const int choice)
{
    switch (choice)
    {
        case 0:
            //sine wave
            initialise([](float x) {return std::sin(x);} );
            break;

        case 1:
            //saw wave
            initialise([](float x) {return x / juce::MathConstants<float>::pi; });
            break;
            
        case 2:
            //square wave
            initialise([](float x) {return x < 0.0f ? -1.0f : 1.0f;});
            break;
            
        default:
            jassertfalse; //will pause plugin execution if one of the statements isn't selected
            break;
    }
}

void OscData::setGain (const float levelInDecibels)
{
    gain.setGainDecibels (levelInDecibels);
}

void OscData::setFreq(const int midiNoteNumber)
{
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
}

void OscData::renderNextBlock ( juce::dsp::AudioBlock<float>& block)
{
    jassert (block.getNumSamples() > 0);
    process(juce::dsp::ProcessContextReplacing<float> (block));
    gain.process (juce::dsp::ProcessContextReplacing<float> (block));
}

float OscData::processNextSample (float input)
{
    return gain.processSample (processSample (input));
}

void OscData::setParams(const int oscChoice, const float oscGain){
    setWaveType(oscChoice);
    setGain(oscGain);
    
}

void OscData::resetAll()
{
    reset();
    gain.reset();
}
