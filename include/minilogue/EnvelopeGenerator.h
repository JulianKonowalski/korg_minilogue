#ifndef ENVELOPE_GENERATOR_H
#define ENVELOPE_GENERATOR_H

namespace minilogue {

class EnvelopeGenerator {
public:

  friend class Minilogue;

  enum ENVELOPE_STATE {
    IDLE,
    ATTACK,
    DECAY,
    SUSTAIN,
    RELEASE
  };

  void noteOn(float& timePoint, ENVELOPE_STATE& envelopeState);
  void noteOff(float& timePoint, ENVELOPE_STATE& envelopeState);

  [[nodiscard]] float getAttack(void) { return mAttack; }
  [[nodiscard]] float getDecay(void) { return mDecay; }
  [[nodiscard]] float getSustain(void) { return mSustain; }
  [[nodiscard]] float getRelease(void) { return mRelease; }

  [[nodiscard]] float getSample(const float& sample, float& timePoint, ENVELOPE_STATE& envelopeState);

private:

  static constexpr float DEFAULT_ATTACK = 0.0f;
  static constexpr float DEFAULT_DECAY = 0.0f; 
  static constexpr float DEFAULT_SUSTAIN = 0.5f;
  static constexpr float DEFAULT_RELEASE = 0.0f;

  static constexpr float MAX_ATTACK_SECONDS = 1.0f;
  static constexpr float MAX_DECAY_SECONDS = 1.0f;
  static constexpr float MAX_RELEASE_SECONDS = 1.0f;

  EnvelopeGenerator(void);
  EnvelopeGenerator(const float& attack, const float& decay, const float& sustain, const float& release);

  void setAttack(const float& attack);
  void setDecay(const float& decay);
  void setSustain(const float& sustain);
  void setRelease(const float& release);

  [[nodiscard]] float attackStage(float sample, float& timePoint, ENVELOPE_STATE& envelopeState);
  [[nodiscard]] float decayStage(float sample, float& timePoint, ENVELOPE_STATE& envelopeState);
  [[nodiscard]] float releaseStage(float sample, float& timePoint, ENVELOPE_STATE& envelopeState);

  float mAttack;
  float mDecay;
  float mSustain;
  float mRelease;

};

};

#endif