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
class PedalBoardAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                        public juce::ComboBox::Listener
{
public:
    PedalBoardAudioProcessorEditor (PedalBoardAudioProcessor&);
    ~PedalBoardAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void comboBoxChanged(juce::ComboBox * comboBox) override;
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PedalBoardAudioProcessor& audioProcessor;
    
    juce::ComboBox selector1;
    juce::ComboBox selector2;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PedalBoardAudioProcessorEditor)
};
