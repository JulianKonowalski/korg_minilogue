#ifndef VOICE_H
#define VOICE_H

#include <cmath>

#include "VCO.h"

namespace minilogue
{
  
class Voice {
public:

  Voice(VCO& vco1, VCO& vco2);

  [[nodiscard]] uint8_t getMidiNote(void) { return mMidiNote; }

  void noteOn(const uint8_t& midiNote);
  void noteOff(const uint8_t& midiNote);

  [[nodiscard]] float process(void);

private:

  VCO* mVco1;
  VCO* mVco2;
  /**
  * Mixer mMixer;
  */

  bool mIsActive;
  float mFrequency;
  float mAngle1;
  float mAngle2;

  uint8_t mMidiNote;

};

};

#endif