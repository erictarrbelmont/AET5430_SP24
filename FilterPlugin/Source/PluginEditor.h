/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class FilterPluginAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                            public juce::Slider::Listener,
                                            public juce::ComboBox::Listener
{
public:
    FilterPluginAudioProcessorEditor (FilterPluginAudioProcessor&);
    ~FilterPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void sliderValueChanged(juce::Slider * slider) override;
    void comboBoxChanged(juce::ComboBox * comboBox) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    FilterPluginAudioProcessor& audioProcessor;
    
    juce::Slider freqSlider;
    juce::Slider resSlider;
    juce::Slider ampSlider;
    
    juce::ComboBox filterSelection;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterPluginAudioProcessorEditor)
};
