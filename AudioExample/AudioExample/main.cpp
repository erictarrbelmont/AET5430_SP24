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

float globalVar = 1.0f;

float myFunction(float var1, int var2);

void stereoPanner(vector<float> & input, vector<vector<float>> & output, const float panValue);

void gainChange(vector<float> & signal);
void audioEffect(vector<float> & input, vector<float> & output);


int main() {
    
    string filename = "AcGtr.wav";
    int Fs;
    int bitDepth;
    int numChannels;
    vector<float> signal;
    
    audioread(filename, signal, Fs, bitDepth, numChannels);
    
    int N = signal.size();
    
    vector<vector<float>> output (2, vector<float> (N));
    
    float panValue = -100.f;
    
    stereoPanner(signal, output, panValue);
    
    std::string outputFilename = "PanFile.wav";
    
    int outNumChannels = 2;
    
    audiowrite(outputFilename, output, Fs, bitDepth, outNumChannels);
    
    return 0;
}


float myFunction(float var1, int var2){
    
    int localVar = var2 + 1;
    float localFloatVar = var1 * 0.5f;
    
    return localFloatVar;
    
}


void stereoPanner(vector<float> & input, vector<vector<float>> & output, const float panValue){
    
    // panValue = [-100 to +100]
    
    float p = panValue / 200.f + .5f; // p = [0 - 1]
    float aL = std::powf( (1.f-p) , 0.5f);
    float aR = std::powf( p , 0.5f);
    
    int N = input.size();
    
    for (int n = 0; n < N; n++){
        float x = input[n];
        output[0][n] = x * aL;
        output[1][n] = x * aR;
    }
    
}

void gainChange(vector<float> & signal){
    int N = signal.size();
    for(int n = 0; n < N; ++n){
        float x = signal[n];
        signal[n] = x * 0.5f;
    }
    
}





