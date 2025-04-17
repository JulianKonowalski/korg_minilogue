#ifndef VCO_H
#define VCO_H

#include <cstdint>

namespace minilogue
{
 
class VCO {
public:

  enum OSC_TYPE {
    SAWTOOTH,
    TRIANGLE,
    SQUARE
  };
  
  static void setSampleRate(const int& sampleRate) { sSampleRate = sampleRate; }

  VCO(void);

  void recalculateDelta(void) { mDeltaTime = 1.0f / sSampleRate; }

  void setOctave(const uint8_t& octave);
  void setOscillatorType(const OSC_TYPE& oscType);
  void setFineTune(const float& fineTune);
  void setShape(const float& shape);

  [[nodiscard]] uint8_t getOctave(void) { return mOctave; }
  [[nodiscard]] OSC_TYPE getOscillatorType(void) { return mOscType; }
  [[nodiscard]] float getFineTune(void) { return mFineTune; }
  [[nodiscard]] float getShape(void) { return mShape; }

  [[nodiscard]] float getSample(float& angle, float frequency);

private:

  static constexpr uint8_t DEFAULT_OCTAVE = 1;
  static constexpr OSC_TYPE DEFAULT_OSC_TYPE = SAWTOOTH;
  static constexpr float DEFAULT_FINE_TUNE = 0.0f;
  static constexpr float DEFAULT_SHAPE = 0.0f;
  static constexpr int DEFAULT_SAMPLE_RATE = 44100;
  static constexpr short FINE_RANGE = 1200;

  inline static int sSampleRate = DEFAULT_SAMPLE_RATE;

  [[nodiscard]] float polyBLEP(float t, float dt);

  [[nodiscard]] float sawWave(const float& angle);
  [[nodiscard]] float triWave(const float& angle);
  [[nodiscard]] float sqrWave(const float& angle);

  uint8_t mOctave;
  OSC_TYPE mOscType;
  float mFineTune;
  float mShape;
  float mDeltaTime;

};
  
}

#endif VCO_H