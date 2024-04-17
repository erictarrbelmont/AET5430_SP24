/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
APVTSExampleAudioProcessorEditor::APVTSExampleAudioProcessorEditor (APVTSExampleAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    
    slider1.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider1.setBounds(10,10,75,75);
    slider1.setTextBoxStyle(juce::Slider::NoTextBox, false, 70, 20);
    slider1.onValueChange = [this](){
        audioProcessor.slider1Changed(slider1.getValue());
    };
    addAndMakeVisible(slider1);
    
    button1.setBounds(100,10,50,20);
    button1.onClick = [this](){
        audioProcessor.button1Clicked(button1.getToggleState());
    };
    addAndMakeVisible(button1);
    
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts,APVTSExampleAudioProcessor::KNOB1,slider1));
    
    buttonAttachments.emplace_back(new ButtonAttachment(audioProcessor.apvts,APVTSExampleAudioProcessor::BUTTON1,button1));
    
    
}

APVTSExampleAudioProcessorEditor::~APVTSExampleAudioProcessorEditor()
{
}

//==============================================================================
void APVTSExampleAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void APVTSExampleAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
