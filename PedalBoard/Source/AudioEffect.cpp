/*
  ==============================================================================

    AudioEffect.cpp
    Created: 21 Mar 2024 1:04:57pm
    Author:  Eric Tarr

  ==============================================================================
*/

#include "AudioEffect.h"


void AudioEffect::process(float *buffer, const int N, const int c){
    
    for (int n = 0; n < N; n++){
        float x = buffer[n];
        float y = processSample(x, c);
        buffer[n] = y;
    }
    
}
