#include "minilogue/Mixer.h"

using namespace minilogue;

Mixer::Mixer(void) :
  mVco1Level(DEFAULT_VCO_LEVEL),
  mVco2Level(DEFAULT_VCO_LEVEL),
  mNoiseLevel(DEFAULT_NOISE_LEVEL)
{}

Mixer::Mixer(
  const float& vco1Level, 
  const float& vco2Level, 
  const float& noiseLevel
) {
  this->setVco1Level(mVco1Level);
  this->setVco2Level(mVco2Level);
  this->setNoiseLevel(noiseLevel);
}

void Mixer::setVco1Level(const float& level) {
  if (level < 0.0f) { mVco1Level = 0.0f; } 
  else if (level > 1.0f) { mVco1Level = 1.0f; }
  else { mVco1Level = level; }
}

void Mixer::setVco2Level(const float& level) {
  if (level < 0.0f) { mVco2Level = 0.0f; }
  else if (level > 1.0f) { mVco2Level = 1.0f; }
  else { mVco2Level = level; }
}

void Mixer::setNoiseLevel(const float& level) {
  if (level < 0.0f) { mNoiseLevel = 0.0f; }
  else if (level > 1.0f) { mNoiseLevel = 1.0f; }
  else { mNoiseLevel = level; }
}

[[nodiscard]] float Mixer::getSample(
  const float& vco1Sample, 
  const float& vco2Sample
) {
  return (
    mVco1Level * vco1Sample +
    mVco2Level * vco2Sample +
    mNoiseLevel * mNoiseGenerator.getSample()
  ) / 3.0f; //normalize to [-1.0f, 1.0f]
}