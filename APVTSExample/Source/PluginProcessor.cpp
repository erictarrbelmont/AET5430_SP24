/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

const juce::StringRef APVTSExampleAudioProcessor::KNOB1 = "KNOB1";
const juce::StringRef APVTSExampleAudioProcessor::BUTTON1 = "BUTTON1";


//==============================================================================
APVTSExampleAudioProcessor::APVTSExampleAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
#endif
apvts(*this,nullptr,"Params",createParams())
{
}

APVTSExampleAudioProcessor::~APVTSExampleAudioProcessor()
{
}

juce::AudioProcessorValueTreeState::ParameterLayout APVTSExampleAudioProcessor::createParams(){
    
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    // ParameterID: tag for DAW
    // String for user/automation lane
    // Min value
    // Max value
    // Starting value
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{KNOB1,ParameterVersionHint},"Gain",-48.f, 6.f, 0.f));
    
    params.push_back(std::make_unique<juce::AudioParameterBool>(juce::ParameterID{BUTTON1,ParameterVersionHint},"Bypass",true));
    
    return {params.begin(),params.end()};
}




//==============================================================================
const juce::String APVTSExampleAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool APVTSExampleAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool APVTSExampleAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool APVTSExampleAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double APVTSExampleAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int APVTSExampleAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int APVTSExampleAudioProcessor::getCurrentProgram()
{
    return 0;
}

void APVTSExampleAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String APVTSExampleAudioProcessor::getProgramName (int index)
{
    return {};
}

void APVTSExampleAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void APVTSExampleAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    alpha = std::exp(-std::log(9.f)/(sampleRate*respTime));
}

void APVTSExampleAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool APVTSExampleAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void APVTSExampleAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    
    //float knobVal = *apvts.getRawParameterValue(KNOB1);
    //bool  buttonVal = *apvts.getRawParameterValue(BUTTON1) > 0.5f ? true : false;
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        for (int n = 0; n < buffer.getNumSamples(); ++n){
            float x = buffer.getWritePointer (channel)[n];
            
            smoothedGain[channel] = alpha * smoothedGain[channel] + (1.f-alpha) * gain;
            
            float y = x * smoothedGain[channel];
            
            buffer.getWritePointer (channel)[n] = y;
        }
        

        // ..do something to the data...
    }
}

//==============================================================================
bool APVTSExampleAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* APVTSExampleAudioProcessor::createEditor()
{
    return new APVTSExampleAudioProcessorEditor (*this);
}

//==============================================================================
void APVTSExampleAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    
    auto currentState = apvts.copyState(); // make a duplicate that won't be updated during write to file
    
    std::unique_ptr<juce::XmlElement> xml (currentState.createXml());
    
    copyXmlToBinary(*xml, destData);
    
}

void APVTSExampleAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    
    std::unique_ptr<juce::XmlElement> xml (getXmlFromBinary(data, sizeInBytes));
    
    juce::ValueTree newTree = juce::ValueTree::fromXml(*xml);
    
    apvts.replaceState(newTree);
}



void APVTSExampleAudioProcessor::slider1Changed(float value){
    
    // do something with value
    gain = std::pow(10.f,value/20.f); // linear gain (not smoothed)
}

void APVTSExampleAudioProcessor::button1Clicked(bool value){
    
    // do something with value
    
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new APVTSExampleAudioProcessor();
}
