/*
  ==============================================================================

    SignalGenerator.h
    Created: 27 Feb 2024 12:56:55pm
    Author:  Eric Tarr

  ==============================================================================
*/

#pragma once

#import <JuceHeader.h>

class SignalGenerator
{
public:
    
    void prepareToPlay(double sampleRate);
    
    float processSample(float x, int channel);
    
    void process(float * buffer, int numSamples, int channel);
    
    void setFrequency(float freq);
    
private:
    
    float Fs = 1.f;
    float currentAngle[2] = {0.f};
    float angleChange = 1.f;
    
    float freqHz = 100.f;
    
    void setAngleChange();
    
    const float PIx2 = 2.f * M_PI;
};
