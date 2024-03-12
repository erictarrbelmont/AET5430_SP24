/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FilterPluginAudioProcessorEditor::FilterPluginAudioProcessorEditor (FilterPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500, 300);
    
    freqSlider.setBounds(10, 60, 100, 100);
    freqSlider.setRange(20, 20000.f);
    freqSlider.setSkewFactorFromMidPoint(1000.f);
    freqSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    freqSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    addAndMakeVisible(freqSlider);
    freqSlider.addListener(this);
    
    
}

FilterPluginAudioProcessorEditor::~FilterPluginAudioProcessorEditor()
{
}

//==============================================================================
void FilterPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::gainsboro);
    g.setFont (25.0f);
    g.drawFittedText ("My Filter Plugin", getLocalBounds(), juce::Justification::centred, 1);
    
    g.setFont (20.0f);
    g.drawText ("Frequency", 10, 10, 100, 40,
                juce::Justification::left, false);
}

void FilterPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}


void FilterPluginAudioProcessorEditor::sliderValueChanged(juce::Slider *slider){
 
    if (slider == &freqSlider){
        audioProcessor.filterFrequency = freqSlider.getValue();
    }
}
