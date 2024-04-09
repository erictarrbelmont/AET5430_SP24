/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "FullWaveEffect.h"
#include "HalfWaveEffect.h"

//==============================================================================
PedalBoardAudioProcessor::PedalBoardAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

PedalBoardAudioProcessor::~PedalBoardAudioProcessor()
{
    // Release memory
    for (int i = 0; i < NUM_PEDALS; i++){
        delete effect[i];
    }
    
}

//==============================================================================
const juce::String PedalBoardAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PedalBoardAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PedalBoardAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PedalBoardAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PedalBoardAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PedalBoardAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PedalBoardAudioProcessor::getCurrentProgram()
{
    return 0;
}

void PedalBoardAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String PedalBoardAudioProcessor::getProgramName (int index)
{
    return {};
}

void PedalBoardAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void PedalBoardAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    for (int i = 0; i < NUM_PEDALS; i++){
        effect[i] = new AudioEffect;
        effect[i]->prepare(sampleRate);
    }
    
    Fs = sampleRate;
}

void PedalBoardAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PedalBoardAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void PedalBoardAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    int N = buffer.getNumSamples();
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        for (int i = 0; i < NUM_PEDALS; i++){
            effect[i]->process(channelData,N,channel);
        }
    }
}

//==============================================================================
bool PedalBoardAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* PedalBoardAudioProcessor::createEditor()
{
    return new PedalBoardAudioProcessorEditor (*this);
}

//==============================================================================
void PedalBoardAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void PedalBoardAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}


void PedalBoardAudioProcessor::setPedal(int pedalNum, int selection){
    // First pedal = 0
    // Second pedal = 1
    
    // Empty = 1
    // Full-wave = 2
    // Half-wave = 3
    
    delete effect[pedalNum];
    
    if (selection == 1)
        effect[pedalNum] = new AudioEffect;
    
    if (selection == 2)
        effect[pedalNum] = new FullWaveEffect;
    
    if (selection == 3)
        effect[pedalNum] = new HalfWaveEffect;
    
    effect[pedalNum]->prepare(Fs);
}



//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PedalBoardAudioProcessor();
}
