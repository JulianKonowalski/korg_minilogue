#include "minilogue/EnvelopeGenerator.h"

#include "minilogue/Minilogue.h"

using namespace minilogue;

EnvelopeGenerator::EnvelopeGenerator(void)
    : mAttack(DEFAULT_ATTACK), mDecay(DEFAULT_DECAY), mSustain(DEFAULT_SUSTAIN),
      mRelease(DEFAULT_RELEASE) {}

EnvelopeGenerator::EnvelopeGenerator(const float &attack, const float &decay,
                                     const float &sustain,
                                     const float &release) {
  this->setAttack(attack);
  this->setDecay(decay);
  this->setSustain(sustain);
  this->setRelease(release);
}

void EnvelopeGenerator::noteOn(float &timePoint,
                               ENVELOPE_STATE &envelopeState) {
  timePoint = 0.0f;
  envelopeState = ENVELOPE_STATE::ATTACK;
}

void EnvelopeGenerator::noteOff(float &timePoint,
                                ENVELOPE_STATE &envelopeState) {
  timePoint = 0.0f;
  envelopeState = ENVELOPE_STATE::RELEASE;
}

[[nodiscard]] float
EnvelopeGenerator::getSample(const float &sample, float &timePoint,
                             ENVELOPE_STATE &envelopeState) {
  float newSample;
  switch (envelopeState) {
  case ENVELOPE_STATE::IDLE:
    return 0.0f;
  case ENVELOPE_STATE::ATTACK:
    return this->attackStage(sample, timePoint, envelopeState);
  case ENVELOPE_STATE::DECAY:
    return this->decayStage(sample, timePoint, envelopeState);
  case ENVELOPE_STATE::SUSTAIN:
    return sample * mSustain;
  case ENVELOPE_STATE::RELEASE:
    return this->releaseStage(sample, timePoint, envelopeState);
  default:
    return 0.0f;
  }
}

void EnvelopeGenerator::setAttack(const float &attack) {
  if (attack < 0.0f) {
    mAttack = 0.0f;
  } else if (attack > 1.0f) {
    mAttack = 1.0f;
  } else {
    mAttack = attack;
  }
}

void EnvelopeGenerator::setDecay(const float &decay) {
  if (decay < 0.0f) {
    mDecay = 0.0f;
  } else if (decay > 1.0f) {
    mDecay = 1.0f;
  } else {
    mDecay = decay;
  }
}

void EnvelopeGenerator::setSustain(const float &sustain) {
  if (sustain < 0.0f) {
    mSustain = 0.0f;
  } else if (sustain > 1.0f) {
    mSustain = 1.0f;
  } else {
    mSustain = sustain;
  }
}

void EnvelopeGenerator::setRelease(const float &release) {
  if (release < 0.0f) {
    mRelease = 0.0f;
  } else if (release > 1.0f) {
    mRelease = 1.0f;
  } else {
    mRelease = release;
  }
}

[[nodiscard]] float
EnvelopeGenerator::attackStage(float sample, float &timePoint,
                               ENVELOPE_STATE &envelopeState) {
  if (!mAttack) {
    envelopeState = ENVELOPE_STATE::DECAY;
    return this->decayStage(sample, timePoint, envelopeState);
  }
  float coeff = std::exp(-timePoint);
  sample *= 1.0f - coeff;
  timePoint += Minilogue::getOffset() / mAttack;
  if (coeff <= 0.001f) {
    envelopeState = ENVELOPE_STATE::DECAY;
    timePoint = 0.0f;
  }
  return sample;
}

[[nodiscard]] float
EnvelopeGenerator::decayStage(float sample, float &timePoint,
                              ENVELOPE_STATE &envelopeState) {
  if (!mDecay) {
    envelopeState = ENVELOPE_STATE::SUSTAIN;
    return sample * mSustain;
  }
  float coeff = std::exp(-timePoint);
  sample *= coeff;
  timePoint += Minilogue::getOffset() / mDecay;
  if (coeff < mSustain) {
    envelopeState = ENVELOPE_STATE::SUSTAIN;
    timePoint = 0.0f;
  }
  return sample;
}

[[nodiscard]] float
EnvelopeGenerator::releaseStage(float sample, float &timePoint,
                                ENVELOPE_STATE &envelopeState) {
  float coeff = std::exp(-timePoint);
  sample *= mSustain * coeff;
  timePoint += Minilogue::getOffset() / mRelease;
  if (coeff < 0.000001) {
    envelopeState = ENVELOPE_STATE::IDLE;
    timePoint = 0.0f;
  }
  return sample;
}
