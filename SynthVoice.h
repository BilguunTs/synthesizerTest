/*
  ==============================================================================

    SynthVoice.h
    Created: 11 Jan 2021 2:44:01pm
    Author:  User

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"
using namespace juce;
class SynthVoice : public SynthesiserVoice {
public:
    //==========================================
    bool canPlaySound(SynthesiserSound* sound){}
    //==========================================
    void startNote(int 	midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) {
    
    };
    //==========================================
    void stopNote(float velocity, bool allowTailOff) {
    
    };
    //==========================================
    void pitchWheelMoved(int newPitchWheelValue) {
    
    };
    //==========================================
    void controllerMoved(int controllerNumber, int newControllerValue) {
    
    };
    //==========================================
    void renderNextBlock(AudioBuffer< float >& outputBuffer, int startSample, int numSamples) {
    
    };
private:
};