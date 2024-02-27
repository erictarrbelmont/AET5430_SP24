/*
  ==============================================================================

    DIstortionProcessor.cpp
    Created: 22 Feb 2024 12:48:10pm
    Author:  Eric Tarr

  ==============================================================================
*/

#include "DIstortionProcessor.h"

float DistortionProcessor::processSample(float x){
    
    x *= drive;
    
    if (x > 1.f){
        x = 1.f;
    }
    else if(x < -1.f){
        x = -1.f;
    }
    
    return x;
}


void DistortionProcessor::processBlock(juce::AudioBuffer<float> & buffer)
{
    auto N = buffer.getNumSamples();
    auto numChannels = buffer.getNumChannels();
    
    for (auto c = 0 ; c < numChannels; c++){
        for (auto n = 0; n < N; n++){
            float x = buffer.getWritePointer(c)[n];
            x = processSample(x);
            buffer.getWritePointer(c)[n] = x;
        }
    }
}


void DistortionProcessor::process(float * buffer, int numSamples){
    
    for (auto n = 0; n < numSamples; n++){
        float x = buffer[n];
        x = processSample(x);
        buffer[n] = x;
    }
}
