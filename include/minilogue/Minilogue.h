#ifndef MINILOGUE_H
#define MINILOGUE_H

#include <cstdint>

#include "VCO.h"
#include "Voice.h"

namespace minilogue {

class Minilogue {
public:
  Minilogue(void);
 
  void playNote(const uint8_t& midiNote) { mVoice.noteOn(midiNote); }
  void stopNote(const uint8_t& midiNote) { mVoice.noteOff(midiNote); }
  void setOscType(const VCO::OSC_TYPE& oscType) { mVco1.setOscillatorType(oscType); }
  void update(void* buffer, unsigned int frames);
  
private:

  static constexpr uint8_t NUM_VOICES = 1;

  float getSample(void);

  VCO mVco1;
  VCO mVco2;

  Voice mVoice;

  /**
   * VCO mVco1;
   * VCO mVco2;
   * Mixer mMixer;
   * Filter mFilter;
   * Amp mAmp;
   * Delay mDelay;
   * 
   * Slider mSlider; //pitch slider
  */

};

};


#endif