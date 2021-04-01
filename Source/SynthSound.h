/*
  ==============================================================================

    SynthSound.h
    Created: 1 Apr 2021 11:42:35am
    Author:  Amanda Barrafato

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
    public:
    bool appliesToNote(int midiNoteNumber) override {return true;};
    bool appliesToChannel(int midiChannel)  override {return true;};
};
