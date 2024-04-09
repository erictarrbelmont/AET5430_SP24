/*
  ==============================================================================

    AudioEffect.h
    Created: 21 Mar 2024 1:04:57pm
    Author:  Eric Tarr

  ==============================================================================
*/

#pragma once


class AudioEffect {
public:
  
    virtual ~AudioEffect() {};
    
    virtual void prepare(double sampleRate){
        Fs = sampleRate;
    }
    
    void process(float * buffer, const int N, const int c);
    
    virtual float processSample(float x, const int c){
        return x; 
    }
    
private:
    
    double Fs = 48000.0;
};
