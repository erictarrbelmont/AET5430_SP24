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


int main() {
    
    string filename = "AcGtr.wav";
    int Fs;
    int bitDepth;
    int numChannels;
    vector<float> signal;
    
    audioread(filename, signal, Fs, bitDepth, numChannels);
    
    int N = signal.size();
    
    for (int n = 0; n < N ; n++){
        float x = signal[n];
        float y = x * 0.25;
        signal[n] = y;
    }
    
    std::string outputFilename = "NewFile.wav";
    
    audiowrite(outputFilename, signal, Fs, bitDepth, numChannels);
    
    return 0;
}

