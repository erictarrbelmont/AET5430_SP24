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
class APVTSExampleAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    APVTSExampleAudioProcessorEditor (APVTSExampleAudioProcessor&);
    ~APVTSExampleAudioProcessorEditor() override;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
    
    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    APVTSExampleAudioProcessor& audioProcessor;
    
    
    juce::Slider slider1;
    juce::ToggleButton button1;
    
    
    std::vector<std::unique_ptr<SliderAttachment>> sliderAttachments;
    std::vector<std::unique_ptr<ButtonAttachment>> buttonAttachments;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (APVTSExampleAudioProcessorEditor)
};
