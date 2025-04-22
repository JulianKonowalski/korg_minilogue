#ifndef MIXER_H
#define MIXER_H

#include "minilogue/NoiseGenerator.h"

namespace minilogue {

class Mixer {
public:

  friend class Minilogue;

  static constexpr float DEFAULT_VCO_LEVEL = 1.0f;
  static constexpr float DEFAULT_NOISE_LEVEL = 0.0f;

  [[nodiscard]] float getVco1Level(void) { return mVco1Level; }
  [[nodiscard]] float getVco2Level(void) { return mVco2Level; }
  [[nodiscard]] float getNoiseLevel(void) { return mNoiseLevel; }

  [[nodiscard]] float getSample(const float& vco1Sample, const float& vco2Sample);

private:

  Mixer(void);
  Mixer(const float& vco1Level, const float& vco2Level, const float& noiseLevel);
  
  void setVco1Level(const float& level);
  void setVco2Level(const float& level);
  void setNoiseLevel(const float& level);
  
  NoiseGenerator mNoiseGenerator;

  float mVco1Level;
  float mVco2Level;
  float mNoiseLevel;

};


};

#endif