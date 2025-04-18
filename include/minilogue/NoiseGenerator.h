#ifndef NOISE_GENERATOR_H
#define NOISE_GENERATOR_H

#include <random>

namespace minilogue {

class NoiseGenerator {
public:

  NoiseGenerator(void);

  [[nodiscard]] float getSample(void);

private:
  std::random_device mRandomDevice;
  std::default_random_engine mRandomEngine;
  std::uniform_real_distribution<> mDistribution;
};

};

#endif