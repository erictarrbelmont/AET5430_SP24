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

class DistortionProcessor {
public:
    enum Type {FULLWAVE, HALFWAVE, CUBIC, HARDCLIP};
    
    DistortionProcessor(Type t) : distType(t){
        
    }
    
    void process (vector<float> & signal)
    {
    
        if (distType == Type::CUBIC){
            processCubic(signal);
        }
        else if (distType == Type::HARDCLIP){
            // hc code
        }
        // ...
    }
    
    
private:
    
    void processCubic (vector<float> & signal){
        int N = signal.size();
        for (int n = 0; n < N ; n++){
            // cubic code
        }
    }
    
    Type distType;
};



class GainProcessor {
  
public:
    
    GainProcessor(){
        initializeVariables();
        setdBGain(0.f);
    }
    
    GainProcessor(float dB) : dBGain(dB)
    {
        setdBGain(dB);
    }
    
    GainProcessor(float dB, float lg) : dBGain(dB), linGain(lg)
    {
        setdBGain(dB);
    }
    
    ~GainProcessor(){
        cout<<"All done!" << endl;
    }
    
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
    
    
    float getMaxValue(){
        return maxValue;
    }
    
private:
    // make variables private
    float dBGain;
    float linGain;
    
    float maxValue;
    
    void initializeVariables(){
        dBGain = 0.f;
        linGain = 1.f;
    }
};


class AudioBuffer
{
  // This class is a fancy "audio" version of a
    // primative array
    
public:
    void setBufferSize(int size){
        bufferSize = size;
    }
    
    int getBufferSize() {
        return bufferSize;
    }
    
    void fillChannelOfBuffer(vector<float> signal, int channel, int & sigIndex){
        int N = signal.size();
        for (int n = 0; n < bufferSize ; n++){
            if (sigIndex < N){
                buffer[channel][n] = signal[sigIndex];
                sigIndex++;
            }
            buffer[channel][n] = 0.f;
        }
    }
    
    float getSample( int channel, int sampleNumber){
        return buffer[channel][sampleNumber];
    }
    
    void setSample(float value, int channel, int sampleNumber){
        buffer[channel][sampleNumber] = value;
    }
    
private:
    
    int bufferSize = 512; // could be 32, 64, 128, ... , 1024
    
    float buffer[2][1024] = {0.f}; // stereo with 1024 samples
};



int main() {
    
    
    float x = 5.f;
    float * p_x;
    p_x = &x;
    
    cout << x << endl; // value from x
    cout << &x << endl; // reference hash of x
    cout << p_x << endl; // reference hash stored in p_x variable
    cout << *p_x << endl; // value from this reference hash block of memory
    
    
    
    //string filename = "AcGtr.wav";
    //int Fs;
    //int bitDepth;
    //int numChannels;
    
    AudioInfo a;
    a.filename = "AcGtr.wav";
    
    vector<float> signal;
    
    audioread(a.filename, signal, a.Fs, a.bitDepth, a.numChannels);
    
    a.N = signal.size();
    
    {
        AudioBuffer myBuffer;
        myBuffer.setBufferSize(64);
        int sigIndex = 0;
        while (sigIndex < a.N){
            myBuffer.fillChannelOfBuffer(signal, 0, sigIndex);
        }
        
    }
    
    //vector<vector<float>> output (2, vector<float> (a.N));
    vector<float> output (a.N);
    
    {
        GainProcessor * gain;
        //GainProcessor gain = GainProcessor(-12.f);
    
        gain->setdBGain(-24.f);
    
        gain->process(signal,output);
        
        DistortionProcessor distortion {DistortionProcessor::Type::CUBIC};
        
        
    }
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





