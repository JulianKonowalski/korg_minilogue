#include "minilogue/NoiseGenerator.h"

using namespace minilogue;

NoiseGenerator::NoiseGenerator(void) : 
  mRandomEngine(mRandomDevice()),
  mDistribution(-1.0f, 1.0f)
{}

[[nodiscard]] float NoiseGenerator::getSample(void) {
  return mDistribution(mRandomEngine);
}