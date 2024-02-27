/*
  ==============================================================================

    DIstortionProcessor.h
    Created: 22 Feb 2024 12:48:10pm
    Author:  Eric Tarr

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class DistortionProcessor
{
    
public:
    void setDrive (float d){
        drive = d;
    }
    
    float processSample (float x);
    
    void processBlock(juce::AudioBuffer<float> & buffer);
    
    void process(float * buffer, int numSamples);
    
private:
    float drive = 1.f;
};
