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


//struct AudioInfo {
//    string filename;
//    int Fs;
//    int bitDepth;
//    int numChannels;
//    int N;
//
//};

class AudioInfo {
    
public:
    string filename;
    int Fs;
    int bitDepth;
    int numChannels;
    int N;
    
};


class GainProcessor {
  
public:
    // make functions public
    void setdBGain(float dB){
        if (dB <= 12.f){
            if (dB >= -96.f){
                dBGain = dB;
                linGain = std::pow(10.f,dB/20.f);
            }
        }
    }
    
    
    void process(vector<float> & input, vector<float> & output){
        int N = input.size();
        for (int n = 0; n < N ; ++n){
            output[n] = input[n] * linGain;
        }
    }
    
    void processInPlace(vector<float> & signal){
        int N = signal.size();
        
        int a = 5;
        float b = 12.f;
        
        for (int n = 0; n < N ; ++n){
            //float x = signal[n];
            //signal[n] = x * linGain;
            signal[n] *= linGain;
        }
    }
    
private:
    // make variables private
    float dBGain = 0.f;
    float linGain = 1.f;
    
};



int main() {
    
    //string filename = "AcGtr.wav";
    //int Fs;
    //int bitDepth;
    //int numChannels;
    
    AudioInfo a;
    a.filename = "AcGtr.wav";
    
    vector<float> signal;
    
    audioread(a.filename, signal, a.Fs, a.bitDepth, a.numChannels);
    
    a.N = signal.size();
    
    //vector<vector<float>> output (2, vector<float> (a.N));
    vector<float> output (a.N);
    
    GainProcessor gain;
    
    gain.setdBGain(-24.f);
    
    gain.process(signal,output);
    
    //float panValue = -100.f;
    
    //stereoPanner(signal, output, panValue);
    
    std::string outputFilename = "GainFile.wav";
    
    int outNumChannels = 1;
    
    audiowrite(outputFilename, output, a.Fs, a.bitDepth, outNumChannels);
    
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





