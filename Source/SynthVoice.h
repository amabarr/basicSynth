/*
  ==============================================================================

    SynthVoice.h
    Created: 1 Apr 2021 11:42:03am
    Author:  Amanda Barrafato

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved (int newPitchWheelValue) override;
    void prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock (juce::AudioBuffer <float> &outputBuffer, int startSample, int numSamples) override;
    
private:
    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParams;
    
    juce::dsp::Oscillator<float> osc{ [](float x) {return x < 0.0f ? -1.0f : 1.0f;}, 200};
    juce::dsp::Gain <float> gain;
    
    bool isPrepared {false};
    
//    sine wave: return std::sin(x);
//    saw wave: return x/juce::MathConstants<float>::pi;
//    square wave:return x < 0.0f ? -1.0f : 1.0f;
    
    
};
