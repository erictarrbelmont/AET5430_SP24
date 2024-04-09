/*
  ==============================================================================

    FullWaveEffect.h
    Created: 21 Mar 2024 1:05:39pm
    Author:  Eric Tarr

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "AudioEffect.h"

class FullWaveEffect : public AudioEffect
{
public:
    
    float processSample(float x, const int c) override {
        return std::abs(x);
    }
    
};
