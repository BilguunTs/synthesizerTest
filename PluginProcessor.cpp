/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SynthesizerDemoAudioProcessor::SynthesizerDemoAudioProcessor()
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
    mysynth.clearVoices();
    for (int i = 0; i < 5; i++) {
        mysynth.addVoice(new SynthVoice());
    }
    mysynth.clearSounds();
    mysynth.addSound(new SynthSound());
}

SynthesizerDemoAudioProcessor::~SynthesizerDemoAudioProcessor()
{
}

//==============================================================================
const juce::String SynthesizerDemoAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SynthesizerDemoAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SynthesizerDemoAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SynthesizerDemoAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SynthesizerDemoAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SynthesizerDemoAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SynthesizerDemoAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SynthesizerDemoAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SynthesizerDemoAudioProcessor::getProgramName (int index)
{
    return {};
}

void SynthesizerDemoAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SynthesizerDemoAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    ignoreUnused(samplesPerBlock);
    lastSampleRate = sampleRate;
    mysynth.setCurrentPlaybackSampleRate(lastSampleRate);
}

void SynthesizerDemoAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SynthesizerDemoAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{   
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
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

void SynthesizerDemoAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    buffer.clear();
    mysynth.renderNextBlock(buffer,midiMessages,0,buffer.getNumSamples());
}

//==============================================================================
bool SynthesizerDemoAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SynthesizerDemoAudioProcessor::createEditor()
{
    return new SynthesizerDemoAudioProcessorEditor (*this);
}

//==============================================================================
void SynthesizerDemoAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SynthesizerDemoAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SynthesizerDemoAudioProcessor();
}
