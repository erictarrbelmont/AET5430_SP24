/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PedalBoardAudioProcessorEditor::PedalBoardAudioProcessorEditor (PedalBoardAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    selector1.addListener(this);
    selector1.setBounds(20, 50, 120, 30);
    selector1.addItem("Empty",1);
    selector1.addItem("Full-wave",2);
    selector1.addItem("Half-wave",3);
    addAndMakeVisible(selector1);
    
    selector2.addListener(this);
    selector2.setBounds(180, 50, 120, 30);
    selector2.addItem("Empty",1);
    selector2.addItem("Full-wave",2);
    selector2.addItem("Half-wave",3);
    addAndMakeVisible(selector2);
}

PedalBoardAudioProcessorEditor::~PedalBoardAudioProcessorEditor()
{
}

//==============================================================================
void PedalBoardAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void PedalBoardAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}


void PedalBoardAudioProcessorEditor::comboBoxChanged(juce::ComboBox *comboBox){
    if (comboBox == &selector1){
        audioProcessor.setPedal(0, selector1.getSelectedId());
    }
    if (comboBox == &selector2){
        audioProcessor.setPedal(1, selector2.getSelectedId());
    }
}
