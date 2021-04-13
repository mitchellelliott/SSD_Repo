/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SupersawDesignerPrototypeAudioProcessorEditor::SupersawDesignerPrototypeAudioProcessorEditor (SupersawDesignerPrototypeAudioProcessor& p)
: AudioProcessorEditor (&p)
, audioProcessor (p)
, osc1 (audioProcessor.apvts, "OSC1", "OSC1GAIN", "OSC1TUNE", "OSC1FMFREQ", "OSC1FMDEPTH")
, osc2 (audioProcessor.apvts, "OSC2", "OSC2GAIN", "OSC2TUNE", "OSC2FMFREQ", "OSC2FMDEPTH")
, adsr (audioProcessor.apvts)
, reverb (audioProcessor.apvts, "REVERBSIZE", "REVERBDAMPING", "REVERBWIDTH", "REVERBDRY", "REVERBWET", "REVERBFREEZE")
, chorus (audioProcessor.apvts, "CHORUSRATE", "DEPTH", "CENTREDELAY", "FEEDBACK", "MIX")
{
    setSize (1000, 600);
    addAndMakeVisible(osc1);
    addAndMakeVisible(osc2);
    addAndMakeVisible(adsr);
    addAndMakeVisible(reverb);
    addAndMakeVisible(chorus);
    
    
//    //unison Slider 1
//    unisonSlider1.addListener(this);
//    unisonSlider1.setBounds(gainSlider2.getRight()+padding,sliderStartY,sliderWidth,sliderHeight);
//    unisonSlider1.setSliderStyle(juce::Slider::LinearVertical);
//    unisonSlider1.setValue(audioProcessor.osc1Unison);
//    unisonSlider1.setRange(1.f,7.f,1.f);
//    unisonSlider1.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 25, 25);
//    addAndMakeVisible(unisonSlider1);
//
//    //Spread Slider 1
//    spreadSlider1.addListener(this);
//    spreadSlider1.setBounds(unisonSlider1.getRight()+padding,sliderStartY,sliderWidth,sliderHeight);
//    spreadSlider1.setSliderStyle(juce::Slider::LinearVertical);
//    spreadSlider1.setValue(audioProcessor.osc1Spread);
//    spreadSlider1.setRange(1.f,14.f,1.f);
//    spreadSlider1.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 25, 25);
//    addAndMakeVisible(spreadSlider1);
//
//    //Tune Slider 1
//    tuneSlider1.addListener(this);
//    tuneSlider1.setBounds(spreadSlider1.getRight()+padding,sliderStartY,sliderWidth,sliderHeight);
//    tuneSlider1.setSliderStyle(juce::Slider::LinearVertical);
//    tuneSlider1.setValue(audioProcessor.osc1Tune);
//    tuneSlider1.setRange(-50.f,50.f,1.f);
//    tuneSlider1.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 35, 25);
//    addAndMakeVisible(tuneSlider1);
    
//    //Gain Slider 2
//    gainSlider2.addListener(this);
//    gainSlider2.setBounds(sliderStartX,sliderStartY+verticalPadding,sliderWidth,sliderHeight);
//    gainSlider2.setSliderStyle(juce::Slider::LinearVertical);
//    gainSlider2.setValue(audioProcessor.osc2Gain);
//    gainSlider2.setRange(0.f,1.f,0.01f);
//    gainSlider2.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 35, 25);
//    addAndMakeVisible(gainSlider2);
    
//    //unison Slider 2
//    unisonSlider2.addListener(this);
//    unisonSlider2.setBounds(gainSlider2.getRight()+padding,sliderStartY+verticalPadding,sliderWidth,sliderHeight);
//    unisonSlider2.setSliderStyle(juce::Slider::LinearVertical);
//    unisonSlider2.setValue(audioProcessor.osc2Unison);
//    unisonSlider2.setRange(1.f,7.f,1.f);
//    unisonSlider2.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 25, 25);
//    addAndMakeVisible(unisonSlider2);
//
//    //Spread Slider 2
//    spreadSlider2.addListener(this);
//    spreadSlider2.setBounds(unisonSlider2.getRight()+padding,sliderStartY+verticalPadding,sliderWidth,sliderHeight);
//    spreadSlider2.setSliderStyle(juce::Slider::LinearVertical);
//    spreadSlider2.setValue(audioProcessor.osc2Spread);
//    spreadSlider2.setRange(1.f,14.f,1.f);
//    spreadSlider2.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 25, 25);
//    addAndMakeVisible(spreadSlider2);
//
//    //Tune Slider 2
//    tuneSlider2.addListener(this);
//    tuneSlider2.setBounds(spreadSlider2.getRight()+padding,sliderStartY+verticalPadding,sliderWidth,sliderHeight);
//    tuneSlider2.setSliderStyle(juce::Slider::LinearVertical);
//    tuneSlider2.setValue(audioProcessor.osc2Tune);
//    tuneSlider2.setRange(-50.f,50.f,1.f);
//    tuneSlider2.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 35, 25);
//    addAndMakeVisible(tuneSlider2);
    
}

SupersawDesignerPrototypeAudioProcessorEditor::~SupersawDesignerPrototypeAudioProcessorEditor()
{
}

//==============================================================================
void SupersawDesignerPrototypeAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    
    //Osc1 Rectangle
    g.setColour (juce::Colours::whitesmoke);
    g.drawRoundedRectangle(5, 35, getWidth()-10, getHeight()/4, 5.0f, 2.0f);
    
    //Osc2 Rectangle
    g.setColour (juce::Colours::whitesmoke);
    g.drawRoundedRectangle(5, 35+verticalPadding, getWidth()-10, getHeight()/4, 5.0f, 2.0f);
    
    //Title
    g.setColour(juce::Colours::gold);
    g.setFont (juce::Font ("Helvetica Neue", 32.f, juce::Font::bold));
    g.drawFittedText("Supersaw Designer",getLocalBounds(), juce::Justification::centredTop, 1);
    
    //Osc 1 Title
    g.setColour(juce::Colours::gold);
    g.setFont(juce::Font ("Helvetica Neue", 15.f, juce::Font::underlined));
    g.drawFittedText("Oscillator 1", 35, sliderStartY-10, 75, 75, juce::Justification::centredTop, 1);
    
    //Osc 2 Title
    g.setColour(juce::Colours::gold);
    g.setFont(juce::Font ("Helvetica Neue", 15.f, juce::Font::underlined));
    g.drawFittedText("Oscillator 2", 35, sliderStartY+verticalPadding-10, 75, 75, juce::Justification::centredTop, 1);
    
    //Osc1 Level Label
    g.setColour(juce::Colours::gold);
    g.setFont(juce::Font ("Helvetica Neue", 15.f, juce::Font::underlined));
    g.drawFittedText("Level", sliderStartX+padding-15 , sliderStartY-10, 50, 50, juce::Justification::centredTop, 1);

    //Osc1 Tune Label
    g.setColour(juce::Colours::gold);
    g.setFont(juce::Font ("Helvetica Neue", 15.f, juce::Font::underlined));
    g.drawFittedText("Tune", 323 , sliderStartY-10, 50, 50, juce::Justification::centredTop, 1);
    
    //Osc1 Fm Freq Label
    g.setColour(juce::Colours::gold);
    g.setFont(juce::Font ("Helvetica Neue", 15.f, juce::Font::underlined));
    g.drawFittedText("FM Freq", 455, sliderStartY-10, 50, 50,juce::Justification::centredTop, 1);
    
    //Osc1 Fm Depth Label
    g.setColour(juce::Colours::gold);
    g.setFont(juce::Font ("Helvetica Neue", 15.f, juce::Font::underlined));
    g.drawFittedText("FM Depth", 590, sliderStartY-10, 50, 50,juce::Justification::centredTop, 1);
    
    //Osc2 Level Label
    g.setColour(juce::Colours::gold);
    g.setFont(juce::Font ("Helvetica Neue", 15.f, juce::Font::underlined));
    g.drawFittedText("Level", sliderStartX+padding-15 , sliderStartY-10+verticalPadding, 50, 50, juce::Justification::centredTop, 1);
    
    //Osc2 Tune Label
    g.setColour(juce::Colours::gold);
    g.setFont(juce::Font ("Helvetica Neue", 15.f, juce::Font::underlined));
    g.drawFittedText("Tune", 323 , sliderStartY-10+verticalPadding, 50, 50, juce::Justification::centredTop, 1);
    
    //Osc1 Fm Freq Label
    g.setColour(juce::Colours::gold);
    g.setFont(juce::Font ("Helvetica Neue", 15.f, juce::Font::underlined));
    g.drawFittedText("FM Freq", 455, sliderStartY-10+verticalPadding, 50, 50,juce::Justification::centredTop, 1);
    
    //Osc2 Fm Depth Label
    g.setColour(juce::Colours::gold);
    g.setFont(juce::Font ("Helvetica Neue", 15.f, juce::Font::underlined));
    g.drawFittedText("FM Depth", 590, sliderStartY-10+verticalPadding, 50, 50,juce::Justification::centredTop, 1);
    
    //ADSR Envelope Label
    g.setColour(juce::Colours::gold);
    g.setFont(juce::Font ("Helvetica Neue", 15.f, juce::Font::underlined));
    g.drawFittedText("Envelope", 87, 390, 50, 50, juce::Justification::centredTop, 1);
    
}

void SupersawDesignerPrototypeAudioProcessorEditor::resized()
{
    //set osc selector bounds
    osc1.setBounds(25, 75, 950, 100);
    osc2.setBounds(25, 250, 950, 100);

    //set adsr bounds
    adsr.setBounds(0, 380, getWidth()/4, getHeight()/3);
    
    //setReverbBounds
    reverb.setBounds(adsr.getRight(), 380, (getWidth()/4)*1.5, getHeight()/3);
    
    //setChorusBounds
    
    chorus.setBounds(reverb.getRight(), 380, getWidth()/4*1.5, getHeight()/3);
    
    
}

void SupersawDesignerPrototypeAudioProcessorEditor::sliderValueChanged(juce::Slider *slider){
//
//    if (slider == &unisonSlider1){
//        audioProcessor.osc1Unison = unisonSlider1.getValue();
//    }
//    if (slider == &spreadSlider1){
//        audioProcessor.osc1Spread = spreadSlider1.getValue();
//    }
//    if (slider == &tuneSlider1){
//        audioProcessor.osc1Tune = tuneSlider1.getValue();
    
//
//    if (slider == &unisonSlider2){
//        audioProcessor.osc2Unison = unisonSlider2.getValue();
//    }
//    if (slider == &spreadSlider2){
//        audioProcessor.osc2Spread = spreadSlider2.getValue();
//    }
//    if (slider == &tuneSlider2){
//        audioProcessor.osc2Tune = tuneSlider2.getValue();
}
