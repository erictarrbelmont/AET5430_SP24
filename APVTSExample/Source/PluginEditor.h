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

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    APVTSExampleAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (APVTSExampleAudioProcessorEditor)
};
