#include "minilogue/Minilogue.h"

using namespace minilogue;

Minilogue::Minilogue(void) : 
  mVoice(mVco1, mVco2, mMixer) 
{
  mVco2.setOscillatorType(VCO::OSC_TYPE::SQUARE);
  mVco1.setFineTune(0.002f);
}

void Minilogue::noteOn(
  const int& midiNoteNumber, 
  const int& midiNoteVelocity, 
  const int& samplePosition
) {
  mVoice.noteOn(midiNoteNumber);
}

void Minilogue::noteOff(
  const int& midiNoteNumber, 
  const int& midiNoteVelocity, 
  const int& samplePosition
) {
  mVoice.noteOff(midiNoteNumber);
}

void Minilogue::processBlock(
  float* lChannelBuffer, 
  float* rChannelBuffer, 
  const int& bufferSize
) {
  for(int i = 0; i < bufferSize; ++i) {
    lChannelBuffer[i] = rChannelBuffer[i] = this->getSample();
  }
}

float Minilogue::getSample(void) {
  return mVoice.process();
}