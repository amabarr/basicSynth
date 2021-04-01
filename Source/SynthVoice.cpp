/*
  ==============================================================================

    SynthVoice.cpp
    Created: 1 Apr 2021 11:42:03am
    Author:  Amanda Barrafato

  ==============================================================================
*/

#include "SynthVoice.h"


bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
};

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    //sets frequency to the MIDI note number
    osc.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    adsr.noteOn();
};


void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
   
    adsr.noteOff();
};


void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue)
{
    
};

void SynthVoice::pitchWheelMoved (int newPitchWheelValue)
{
    
};

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    adsr.setSampleRate(sampleRate);
    
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;
    
    osc.prepare(spec);
    gain.prepare(spec);
    
    
    //Set gain linear: float between 0 - 1
    gain.setGainLinear(0.01f);
    
    
    isPrepared = true;
    
};

void SynthVoice::renderNextBlock (juce::AudioBuffer <float> &outputBuffer, int startSample, int numSamples)
{
    jassert (isPrepared);
    juce::dsp::AudioBlock<float> audioBlock { outputBuffer };
    osc.process(juce::dsp::ProcessContextReplacing<float> (audioBlock));
    
    gain.process(juce::dsp::ProcessContextReplacing<float> (audioBlock));
    
    adsr.applyEnvelopeToBuffer(outputBuffer, startSample, numSamples);
};
