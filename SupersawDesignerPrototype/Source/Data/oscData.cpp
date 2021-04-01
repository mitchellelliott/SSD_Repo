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
    fmOsc.prepare(spec);
    gain.prepare(spec);
    
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

void OscData::setOscTune (const int pitch)
{
    lastPitch = pitch;
    setFrequency(juce::MidiMessage::getMidiNoteInHertz ((lastMidiNote + lastPitch)+fmModulator));

}

void OscData::setFreq(const int midiNoteNumber)
{
    setFrequency(juce::MidiMessage::getMidiNoteInHertz ((midiNoteNumber + lastPitch)+fmModulator));
    lastMidiNote = midiNoteNumber;
}

void OscData::setFmOsc(const float freq, const float depth){
    fmDepth = depth;
    fmOsc.setFrequency(freq);
    setFrequency(juce::MidiMessage::getMidiNoteInHertz ((lastMidiNote + lastPitch) + fmModulator));
}

void OscData::renderNextBlock ( juce::dsp::AudioBlock<float>& block)
{
    jassert (block.getNumSamples() > 0);
    process(juce::dsp::ProcessContextReplacing<float> (block));
    gain.process (juce::dsp::ProcessContextReplacing<float> (block));
}

float OscData::processNextSample (float input)
{
    fmModulator = fmOsc.processSample(input) * fmDepth;
    return gain.processSample (processSample (input));
}

void OscData::setParams(const int oscChoice, const float oscGain, const int oscTune, const float fmFreq, const float fmDepth){
    setWaveType(oscChoice);
    setGain(oscGain);
    setOscTune(oscTune);
    setFmOsc(fmFreq, fmDepth);
}

void OscData::resetAll()
{
    reset();
    fmOsc.reset();
    gain.reset();
}
