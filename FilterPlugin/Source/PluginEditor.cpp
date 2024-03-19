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
    
    resSlider.setBounds(350, 60, 100, 100);
    resSlider.setRange(.1, 10.f);
    resSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    resSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    addAndMakeVisible(resSlider);
    resSlider.addListener(this);
    
    ampSlider.setBounds(10, 200, 100, 100);
    ampSlider.setRange(-15.f, 15.f);
    ampSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    ampSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    addAndMakeVisible(ampSlider);
    ampSlider.addListener(this);
    ampSlider.setEnabled(false);
    
    // Combo Box
    filterSelection.setBounds(350, 200, 100, 40);
    filterSelection.addItem("LPF",1);
    filterSelection.addItem("HPF",2);
    filterSelection.addItem("BPF",3);
    filterSelection.addItem("High Shelf",4);
    filterSelection.addItem("Low Shelf",5);
    filterSelection.addItem("Peak/Bell",6);
    filterSelection.setText("Select Type...");
    addAndMakeVisible(filterSelection);
    filterSelection.addListener(this);
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
    g.drawText ("Resonance", 350, 10, 100, 40,
                juce::Justification::left, false);
    g.drawText ("Amplitude", 10, 170, 100, 40,
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
    
    if (slider == &resSlider){
        audioProcessor.filterResonance = resSlider.getValue();
    }
    
    if (slider == &ampSlider){
        audioProcessor.filterAmp = ampSlider.getValue();
    }
}

void FilterPluginAudioProcessorEditor::comboBoxChanged(juce::ComboBox *comboBox){
    
    if (comboBox == &filterSelection){
        if (filterSelection.getSelectedId() == 1){
            audioProcessor.filterType = Biquad::FilterType::LPF;
            ampSlider.setEnabled(false);
        }
        if (filterSelection.getSelectedId() == 2){
            audioProcessor.filterType = Biquad::FilterType::HPF;
            ampSlider.setEnabled(false);
        }
        if (filterSelection.getSelectedId() == 3){
            audioProcessor.filterType = Biquad::FilterType::BPF1;
            ampSlider.setEnabled(false);
        }
        if (filterSelection.getSelectedId() == 4){
            audioProcessor.filterType = Biquad::FilterType::HSHELF;
            ampSlider.setEnabled(true);
        }
        if (filterSelection.getSelectedId() == 5){
            audioProcessor.filterType = Biquad::FilterType::LSHELF;
            ampSlider.setEnabled(true);
        }
        if (filterSelection.getSelectedId() == 6){
            audioProcessor.filterType = Biquad::FilterType::PEAK;
            ampSlider.setEnabled(true);
        }
    }
    
}
