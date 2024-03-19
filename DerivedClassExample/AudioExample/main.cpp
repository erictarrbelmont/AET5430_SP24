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
    
    virtual float processSample(float x){
        return x;
    }
    
private:
    float Fs;
};

// Specific/derived class
class DistortionEffect : AudioEffect {
public:
    
    float processSample(float x) override {
        return abs(x);
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
    
    
    vector<float> output (N);
    
    
    std::string outputFilename = "GainFile.wav";
    
    int outNumChannels = 1;
    
    audiowrite(outputFilename, output, Fs, bitDepth, outNumChannels);
    
    return 0;
}


