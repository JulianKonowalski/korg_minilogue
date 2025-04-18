#include "minilogue/Voice.h"

using namespace minilogue;

Voice::Voice(VCO& vco1, VCO& vco2, Mixer& mixer) :
  mVco1(&vco1),
  mVco2(&vco2),
  mMixer(&mixer),
  mIsActive(false),
  mFrequency(440.0f),
  mAngle1(0.0f),
  mAngle2(0.0f),
  mMidiNote(0)
{}

void Voice::noteOn(const uint8_t& midiNote) {
  mMidiNote = midiNote;
  mFrequency = 440.0f * (powf(2, (midiNote - 69)/12.0f));
  mIsActive = true;
}

void Voice::noteOff(const uint8_t& midiNote) {
  if (midiNote != mMidiNote) { return; }
  mIsActive = false;
  mMidiNote = 0;
}

[[nodiscard]] float Voice::process(void) {
  if (!mIsActive) { return 0.0f; }
  float sample = mMixer->getSample(
    mVco1->getSample(mAngle1, mFrequency),
    mVco2->getSample(mAngle2, mFrequency)
  );
  // sample += mVco1->getSample(mAngle1, mFrequency);
  // sample += mVco2->getSample(mAngle2, 0.5f * mFrequency);
  return sample;
}