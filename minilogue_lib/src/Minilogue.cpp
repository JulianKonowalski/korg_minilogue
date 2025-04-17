#include "Minilogue.h"

using namespace minilogue;

Minilogue::Minilogue(void) : 
  mVoice(mVco1, mVco2) 
{
  mVco2.setOscillatorType(VCO::OSC_TYPE::SQUARE);
  mVco1.setFineTune(0.002f);
}

void Minilogue::update(void* buffer, unsigned int frames) {
  short* d = (short*)buffer;
  for(unsigned int i = 0; i < frames; ++i) {
    d[i] = (short)(32000.0f * this->getSample());
  }
}

float Minilogue::getSample(void) {
  return mVoice.process();
}