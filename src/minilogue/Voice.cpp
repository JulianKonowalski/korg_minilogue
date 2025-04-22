#include "minilogue/Voice.h"

using namespace minilogue;

Voice::Voice(VCO& vco1, VCO& vco2, Mixer& mixer, EnvelopeGenerator& amp) :
  mVco1(&vco1),
  mVco2(&vco2),
  mMixer(&mixer),
  mAmp(&amp),
  mIsActive(false),
  mFrequency(440.0f),
  mAngle1(0.0f),
  mAngle2(0.0f),
  mEnvelopeTimePoint(0.0f),
  mEnvelopeState(EnvelopeGenerator::ENVELOPE_STATE::IDLE),
  mMidiNote(0)
{}

void Voice::noteOn(const uint8_t& midiNote) {
  mAmp->noteOn(mEnvelopeTimePoint, mEnvelopeState);
  mMidiNote = midiNote;
  mFrequency = 440.0f * (powf(2, (midiNote - 69)/12.0f));
  mIsActive = true;
}

void Voice::noteOff(const uint8_t& midiNote) {
  if (midiNote != mMidiNote) { return; }
  mAmp->noteOff(mEnvelopeTimePoint, mEnvelopeState);
  // mIsActive = false;
  // mMidiNote = 0;
}

[[nodiscard]] float Voice::process(void) {
  if (!mIsActive) { return 0.0f; }
  float sample = mMixer->getSample(
    mVco1->getSample(mAngle1, mFrequency),
    mVco2->getSample(mAngle2, mFrequency)
  );
  return mAmp->getSample(sample, mEnvelopeTimePoint, mEnvelopeState);
}