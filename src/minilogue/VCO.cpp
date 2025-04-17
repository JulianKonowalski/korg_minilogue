#include "minilogue/VCO.h"

#include <cmath>

using namespace minilogue;

VCO::VCO(void) :
  mOctave(DEFAULT_OCTAVE),
  mOscType(DEFAULT_OSC_TYPE),
  mFineTune(DEFAULT_FINE_TUNE),
  mShape(DEFAULT_SHAPE)
{
  this->recalculateDelta();
}

void VCO::setOctave(const uint8_t& octave) {
  if (octave > 3) { mOctave = 3; }
  else { mOctave = octave; }
}

void VCO::setOscillatorType(const OSC_TYPE& oscType) {
  mOscType = oscType;
}

void VCO::setFineTune(const float& fineTune) {
  if (fineTune < -1.0f) { mFineTune = -1.0f; }
  else if (fineTune > 1.0f) { mFineTune = 1.0f; }
  else { mFineTune = fineTune; }
}

void VCO::setShape(const float& shape) {
  if (shape < 0.0f) { mShape = 0.0f; }
  else if (shape > 1.0f) { mShape = 1.0f; }
  else { mShape = shape; }
}

[[nodiscard]] float VCO::getSample (float& angle, float frequency) {
  if(mFineTune != 0.0f) { frequency *= std::powf(2, mFineTune); }
  float offset = frequency * mDeltaTime;
  angle += offset;
  angle -= angle > 1.0f ? 1.0f : 0.0f;
  switch (mOscType) {
    case SAWTOOTH: 
      return this->sawWave(angle) - this->polyBLEP(angle, offset);
    case TRIANGLE: 
      return this->triWave(angle);
    case SQUARE: 
      return (
        this->sqrWave(angle) + 
        this->polyBLEP(angle, offset) - 
        this->polyBLEP(std::fmod(angle + 0.5f, 1.0f), offset)
      );
    default: return 0.0f;
  }
}

[[nodiscard]] float VCO::polyBLEP(float t, float dt) {
  if(t < dt) {
    t /= dt;
    return t + t - (t * t) - 1.0f;
  } else if (t > 1.0f - dt) {
    t = (t - 1.0f) / dt;
    return t + t + (t * t) + 1.0f;
  }
  return 0.0f;
}

[[nodiscard]] float VCO::sawWave(const float& angle) { 
  return angle + angle - 1.0f;
}

[[nodiscard]] float VCO::triWave(const float& angle) {
  return 0.0f;
}

[[nodiscard]] float VCO::sqrWave(const float& angle) {
  return angle < 0.5f ? 1.0f : -1.0f;
}