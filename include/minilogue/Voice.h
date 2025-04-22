#ifndef VOICE_H
#define VOICE_H

#include <cmath>

#include "minilogue/VCO.h"
#include "minilogue/Mixer.h"
#include "minilogue/EnvelopeGenerator.h"

namespace minilogue
{
  
class Voice {
public:

  Voice(VCO& vco1, VCO& vco2, Mixer& mixer, EnvelopeGenerator& amp);

  [[nodiscard]] uint8_t getMidiNote(void) { return mMidiNote; }

  void noteOn(const uint8_t& midiNote);
  void noteOff(const uint8_t& midiNote);

  [[nodiscard]] float process(void);

private:

  VCO* mVco1;
  VCO* mVco2;
  Mixer* mMixer;
  EnvelopeGenerator* mAmp;

  bool mIsActive;
  float mFrequency;
  float mAngle1;
  float mAngle2;
  float mEnvelopeTimePoint;
  EnvelopeGenerator::ENVELOPE_STATE mEnvelopeState;

  uint8_t mMidiNote;

};

};

#endif