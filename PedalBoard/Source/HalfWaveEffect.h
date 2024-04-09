/*
  ==============================================================================

    HalfWaveEffect.h
    Created: 21 Mar 2024 1:05:54pm
    Author:  Eric Tarr

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "AudioEffect.h"

class HalfWaveEffect : public AudioEffect
{
public:
    
    float processSample(float x, const int c) override {
        if (x < 0.f)
            x = 0.f;
        
        return x;
    }
    
};
