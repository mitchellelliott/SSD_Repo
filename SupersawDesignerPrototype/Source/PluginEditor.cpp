/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SupersawDesignerPrototypeAudioProcessorEditor::SupersawDesignerPrototypeAudioProcessorEditor (SupersawDesignerPrototypeAudioProcessor& p)
: AudioProcessorEditor (&p), audioProcessor (p), osc1 (audioProcessor.apvts, "OSC1WAVETYPE"), osc2 (audioProcessor.apvts, "OSC2WAVETYPE"), adsr (audioProcessor.apvts)
{
    setSize (700, 600);
    addAndMakeVisible(osc1);
    addAndMakeVisible(osc2);
    addAndMakeVisible(adsr);
    
    //Gain Slider 1
    gainSlider1.addListener(this);
    gainSlider1.setBounds(sliderStartX,sliderStartY,sliderWidth,sliderHeight);
    gainSlider1.setSliderStyle(juce::Slider::LinearVertical);
    gainSlider1.setValue(audioProcessor.osc1Gain);
    gainSlider1.setRange(0.f,1.f,0.01f);
    gainSlider1.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 35, 25);
    addAndMakeVisible(gainSlider1);
    
    //unison Slider 1
    unisonSlider1.addListener(this);
    unisonSlider1.setBounds(gainSlider1.getRight()+padding,sliderStartY,sliderWidth,sliderHeight);
    unisonSlider1.setSliderStyle(juce::Slider::LinearVertical);
    unisonSlider1.setValue(audioProcessor.osc1Unison);
    unisonSlider1.setRange(1.f,7.f,1.f);
    unisonSlider1.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 25, 25);
    addAndMakeVisible(unisonSlider1);
    
    //Spread Slider 1
    spreadSlider1.addListener(this);
    spreadSlider1.setBounds(unisonSlider1.getRight()+padding,sliderStartY,sliderWidth,sliderHeight);
    spreadSlider1.setSliderStyle(juce::Slider::LinearVertical);
    spreadSlider1.setValue(audioProcessor.osc1Spread);
    spreadSlider1.setRange(1.f,14.f,1.f);
    spreadSlider1.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 25, 25);
    addAndMakeVisible(spreadSlider1);
    
    //Tune Slider 1
    tuneSlider1.addListener(this);
    tuneSlider1.setBounds(spreadSlider1.getRight()+padding,sliderStartY,sliderWidth,sliderHeight);
    tuneSlider1.setSliderStyle(juce::Slider::LinearVertical);
    tuneSlider1.setValue(audioProcessor.osc1Tune);
    tuneSlider1.setRange(-50.f,50.f,1.f);
    tuneSlider1.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 35, 25);
    addAndMakeVisible(tuneSlider1);
    
    //Gain Slider 2
    gainSlider2.addListener(this);
    gainSlider2.setBounds(sliderStartX,sliderStartY+verticalPadding,sliderWidth,sliderHeight);
    gainSlider2.setSliderStyle(juce::Slider::LinearVertical);
    gainSlider2.setValue(audioProcessor.osc2Gain);
    gainSlider2.setRange(0.f,1.f,0.01f);
    gainSlider2.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 35, 25);
    addAndMakeVisible(gainSlider2);
    
    //unison Slider 2
    unisonSlider2.addListener(this);
    unisonSlider2.setBounds(gainSlider2.getRight()+padding,sliderStartY+verticalPadding,sliderWidth,sliderHeight);
    unisonSlider2.setSliderStyle(juce::Slider::LinearVertical);
    unisonSlider2.setValue(audioProcessor.osc2Unison);
    unisonSlider2.setRange(1.f,7.f,1.f);
    unisonSlider2.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 25, 25);
    addAndMakeVisible(unisonSlider2);
    
    //Spread Slider 2
    spreadSlider2.addListener(this);
    spreadSlider2.setBounds(unisonSlider2.getRight()+padding,sliderStartY+verticalPadding,sliderWidth,sliderHeight);
    spreadSlider2.setSliderStyle(juce::Slider::LinearVertical);
    spreadSlider2.setValue(audioProcessor.osc2Spread);
    spreadSlider2.setRange(1.f,14.f,1.f);
    spreadSlider2.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 25, 25);
    addAndMakeVisible(spreadSlider2);
    
    //Tune Slider 2
    tuneSlider2.addListener(this);
    tuneSlider2.setBounds(spreadSlider2.getRight()+padding,sliderStartY+verticalPadding,sliderWidth,sliderHeight);
    tuneSlider2.setSliderStyle(juce::Slider::LinearVertical);
    tuneSlider2.setValue(audioProcessor.osc2Tune);
    tuneSlider2.setRange(-50.f,50.f,1.f);
    tuneSlider2.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 35, 25);
    addAndMakeVisible(tuneSlider2);
    
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
    g.drawFittedText("Oscillator 1", 35, sliderStartY-20, 75, 75, juce::Justification::centredTop, 1);
    
    //Osc 2 Title
    g.setColour(juce::Colours::gold);
    g.setFont(juce::Font ("Helvetica Neue", 15.f, juce::Font::underlined));
    g.drawFittedText("Oscillator 2", 35, sliderStartY-20+verticalPadding, 75, 75, juce::Justification::centredTop, 1);
    
    //Osc1 Level Label
    g.setColour(juce::Colours::gold);
    g.setFont(juce::Font ("Helvetica Neue", 15.f, juce::Font::underlined));
    g.drawFittedText("Level", sliderStartX+25 , sliderStartY-20, 50, 50, juce::Justification::centredTop, 1);

    //Osc1 Unison Label
    g.setColour(juce::Colours::gold);
    g.setFont(juce::Font ("Helvetica Neue", 15.f, juce::Font::underlined));
    g.drawFittedText("Unison", gainSlider1.getRight()+padding+25 , sliderStartY-20, 50, 50, juce::Justification::centredTop, 1);
   
    //Osc1 Spread Label
    g.setColour(juce::Colours::gold);
    g.setFont(juce::Font ("Helvetica Neue", 15.f, juce::Font::underlined));
    g.drawFittedText("Spread", unisonSlider1.getRight()+padding+25 , sliderStartY-20, 50, 50, juce::Justification::centredTop, 1);
    
    //Osc1 Tune Label
    g.setColour(juce::Colours::gold);
    g.setFont(juce::Font ("Helvetica Neue", 15.f, juce::Font::underlined));
    g.drawFittedText("Tune", spreadSlider1.getRight()+padding+25 , sliderStartY-20, 50, 50, juce::Justification::centredTop, 1);
    
    //Osc2 Level Label
    g.setColour(juce::Colours::gold);
    g.setFont(juce::Font ("Helvetica Neue", 15.f, juce::Font::underlined));
    g.drawFittedText("Level", sliderStartX+25 , sliderStartY-20+verticalPadding, 50, 50, juce::Justification::centredTop, 1);
    
    //Osc2 Unison Label
    g.setColour(juce::Colours::gold);
    g.setFont(juce::Font ("Helvetica Neue", 15.f, juce::Font::underlined));
    g.drawFittedText("Unison", gainSlider2.getRight()+padding+25 , sliderStartY-20+verticalPadding, 50, 50, juce::Justification::centredTop, 1);
    
    //Osc2 Spread Label
    g.setColour(juce::Colours::gold);
    g.setFont(juce::Font ("Helvetica Neue", 15.f, juce::Font::underlined));
    g.drawFittedText("Spread", unisonSlider2.getRight()+padding+25 , sliderStartY-20+verticalPadding, 50, 50, juce::Justification::centredTop, 1);
    
    //Osc2 Unison Label
    g.setColour(juce::Colours::gold);
    g.setFont(juce::Font ("Helvetica Neue", 15.f, juce::Font::underlined));
    g.drawFittedText("Tune", spreadSlider2.getRight()+padding+25 , sliderStartY-20+verticalPadding, 50, 50, juce::Justification::centredTop, 1);
    
    //ADSR Envelope Label
    g.setColour(juce::Colours::gold);
    g.setFont(juce::Font ("Helvetica Neue", 15.f, juce::Font::underlined));
    g.drawFittedText("Envelope", 87, 390, 50, 50, juce::Justification::centredTop, 1);
    
}

void SupersawDesignerPrototypeAudioProcessorEditor::resized()
{
    //set osc selector bounds
    osc1.setBounds(25, 75, 100, 100);
    osc2.setBounds(25, 250, 100, 100);

    //set adsr bounds
    adsr.setBounds(0, 380, getWidth()/3, getHeight()/3);
    
    
}

void SupersawDesignerPrototypeAudioProcessorEditor::sliderValueChanged(juce::Slider *slider){
    
    if (slider == &gainSlider1){
        audioProcessor.osc1Gain = gainSlider1.getValue();
    }
    if (slider == &unisonSlider1){
        audioProcessor.osc1Unison = unisonSlider1.getValue();
    }
    if (slider == &spreadSlider1){
        audioProcessor.osc1Spread = spreadSlider1.getValue();
    }
    if (slider == &tuneSlider1){
        audioProcessor.osc1Tune = tuneSlider1.getValue();
    }
    if (slider == &gainSlider2){
        audioProcessor.osc1Gain = gainSlider1.getValue();
    }
    if (slider == &unisonSlider2){
        audioProcessor.osc1Unison = unisonSlider1.getValue();
    }
    if (slider == &spreadSlider2){
        audioProcessor.osc1Spread = spreadSlider1.getValue();
    }
    if (slider == &tuneSlider2){
        audioProcessor.osc1Tune = tuneSlider1.getValue();
    }
}
