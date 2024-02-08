//
//  main.cpp
//  Quiz1
//
//  Created by Eric Tarr on 2/8/24.
//

#include <iostream>
#include <cmath>
#include "AudioFile/AudioFile.hpp"
using namespace std;

// Create class here:





//
//
// Demonstrate class in main:
int main(int argc, const char * argv[]) {
    
    string filename = "AcGtr.wav";
    int Fs;
    int bitDepth;
    int numChannels;
    
    vector<float> signal;
    audioread(filename, signal, Fs, bitDepth, numChannels);
    
    
    //
    
    
    //
    
    
    std::string outputFilename = "DistFile.wav";
    
    audiowrite(outputFilename, signal, Fs, bitDepth, numChannels);
    return 0;
}
