//
//  main.cpp
//  AudioExample
//
//  Created by Hack Audio on 10/5/19.
//  Copyright © 2019 Eric Tarr. All rights reserved.
//

#include <iostream>
#include <cmath>
#include "AudioFile/AudioFile.hpp"
using namespace std;

// Generic base class
class AudioEffect {
public:
    
    virtual ~AudioEffect() {};
    
    void prepare(float sampleRate){
        Fs = sampleRate;
    }
    
    void processSignal(vector<float> & signal){
        int N = signal.size();
        
        for (int n = 0; n < N; n++){
            float x = signal[n];
            float y = processSample(x);
            signal[n] = y;
        }
    }
    
    // "Regular" virtual virtual function.
    // Can be overriden
    // Has an implementation that can also be used
    
    //virtual float processSample(float x){
    //    return x;
    //}
    
    // "Pure" virtual function
    // Must be overriden
    // Has no implementation
    virtual float processSample(float x) = 0;
    
    
private:
    float Fs;
};

// Specific/derived class
class FullWaveEffect : public AudioEffect {
public:
    
    float processSample(float x) override {
        return abs(x);
    }
    
private:
    
};

class HalfWaveEffect : public AudioEffect {
public:
    
    float processSample(float x) override {
       if (x < 0.f)
           x = 0.f;
           
        return x;
    }
    
private:
    
};


int main() {
    
    
    vector<float> signal;
    
    std::string filename = "AcGtr.wav";
    int Fs;
    int bitDepth;
    int numChannels;
    
    audioread(filename, signal, Fs, bitDepth, numChannels);
    
    int N = signal.size();
    
    
    {
        AudioEffect * effect[2];
    
        effect[0] = new FullWaveEffect;
        effect[1] = new HalfWaveEffect;
    
        for (int n = 0; n < 2; n++){
            float x = effect[n]->processSample(-1.f);
            int test = 1;
        }
        
        // Replace effect[0] with HalfWaveRect
        delete effect[0];
        effect[0] = new HalfWaveEffect;
        
        for (int n = 0; n < 2; n++){
            float x = effect[n]->processSample(-1.f);
            int test = 1;
        }
        
        delete effect[0];
        delete effect[1];
    }
    
    vector<float> output (N);
    
    
    std::string outputFilename = "GainFile.wav";
    
    int outNumChannels = 1;
    
    audiowrite(outputFilename, output, Fs, bitDepth, outNumChannels);
    
    return 0;
}


