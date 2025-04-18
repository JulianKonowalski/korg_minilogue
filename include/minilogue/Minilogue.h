#ifndef MINILOGUE_H
#define MINILOGUE_H

#include <cstdint>

#include "minilogue/VCO.h"
#include "minilogue/Voice.h"
#include "minilogue/Mixer.h"

namespace minilogue {

class Minilogue {
public:
  Minilogue(void);

  void setOscType(const VCO::OSC_TYPE& oscType) { mVco1.setOscillatorType(oscType); }
  void setVCO1FineTune(const float& fineTune) { mVco1.setFineTune(fineTune); }
 
  void noteOn(const int& midiNoteNumber, const int& midiNoteVelocity, const int& samplePosition);
  void noteOff(const int& midiNoteNumber, const int& midiNoteVelocity, const int& samplePosition);
  void processBlock(float* lChannelBuffer, float* rChannelBuffer, const int& bufferSize);

private:

  float getSample(void);

  VCO mVco1;
  VCO mVco2;
  Voice mVoice;
  Mixer mMixer;

  /**
   * Filter mFilter;
   * Amp mAmp;
   * Delay mDelay;
   * 
   * Slider mSlider; //pitch slider
  */

};

};


#endif