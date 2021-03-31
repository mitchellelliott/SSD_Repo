/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SupersawDesignerPrototypeAudioProcessor::SupersawDesignerPrototypeAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this, nullptr, "Parameters", createParameters())
#endif
{
    synth.addSound(new SynthSound());
    synth.addVoice(new SynthVoice());
}

SupersawDesignerPrototypeAudioProcessor::~SupersawDesignerPrototypeAudioProcessor()
{
}

//==============================================================================
const juce::String SupersawDesignerPrototypeAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SupersawDesignerPrototypeAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SupersawDesignerPrototypeAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SupersawDesignerPrototypeAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SupersawDesignerPrototypeAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SupersawDesignerPrototypeAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SupersawDesignerPrototypeAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SupersawDesignerPrototypeAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SupersawDesignerPrototypeAudioProcessor::getProgramName (int index)
{
    return {};
}

void SupersawDesignerPrototypeAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SupersawDesignerPrototypeAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);
    
    for (int i=0; i < synth.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }
    
}

void SupersawDesignerPrototypeAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SupersawDesignerPrototypeAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SupersawDesignerPrototypeAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int i=0; i<synth.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            //Osc controls
            //ADSR
            //LFO
            
            auto& attack = *apvts.getRawParameterValue("ATTACK");
            auto& decay = *apvts.getRawParameterValue("DECAY");
            auto& sustain = *apvts.getRawParameterValue("SUSTAIN");
            auto& release = *apvts.getRawParameterValue("RELEASE");
            
            auto& oscWaveChoice = *apvts.getRawParameterValue("OSC1WAVETYPE");
            
            voice->update (attack.load(), decay.load(), sustain.load(), release.load());
            voice->getOscillator().setWaveType(oscWaveChoice);
            
        }
    }
    
    synth.renderNextBlock (buffer, midiMessages, 0, buffer.getNumSamples());
    
}

//==============================================================================
bool SupersawDesignerPrototypeAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SupersawDesignerPrototypeAudioProcessor::createEditor()
{
    return new SupersawDesignerPrototypeAudioProcessorEditor (*this);
}

//==============================================================================
void SupersawDesignerPrototypeAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SupersawDesignerPrototypeAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SupersawDesignerPrototypeAudioProcessor();
}

// Audio Processor Value Tree State
juce::AudioProcessorValueTreeState::ParameterLayout SupersawDesignerPrototypeAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    //Osc Select
    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC1WAVETYPE", "Osc 1 Wave Type", juce::StringArray { "Sine" , "Saw" , "Square" }, 0));
    
    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC2WAVETYPE", "Osc 2 Wave Type", juce::StringArray { "Sine" , "Saw" , "Square" }, 0));
    
    //ADSR
    params.push_back (std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", juce::NormalisableRange<float> { 0.1f, 1.0f, }, 0.1f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay", juce::NormalisableRange<float> { 0.1f, 1.0f, }, 0.1f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain", juce::NormalisableRange<float> { 0.1f, 1.0f, }, 0.1f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", juce::NormalisableRange<float> { 0.1f, 3.0f, }, 0.4f));
    

    
    
    
    return { params.begin() , params.end() };
}
