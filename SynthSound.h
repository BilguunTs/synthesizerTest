/*
  ==============================================================================

    SynthSound.h
    Created: 11 Jan 2021 2:43:40pm
    Author:  User

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
using namespace juce;
class SynthSound: public SynthesiserSound{
public : 
    bool appliesToNote(int midiNoteNumber) {
        return true;
    };
    bool appliesToChannel(int midiChanel) {
        return true 
    };
};