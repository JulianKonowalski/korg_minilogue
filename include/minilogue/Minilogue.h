#ifndef MINILOGUE_H
#define MINILOGUE_H

#include <cstdint>

#include "minilogue/VCO.h"
#include "minilogue/Voice.h"
#include "minilogue/Mixer.h"
#include "minilogue/EnvelopeGenerator.h"

namespace minilogue {

class Minilogue {
public:

  static void setSampleRate(const unsigned int& sampleRate) { 
    sSampleRate = sampleRate; 
    sOffset = 1.0f / sSampleRate;
  }

  [[nodiscard]] static float getOffset(void) { return sOffset; }
  [[nodiscard]] static int getSampleRate(void) { return sSampleRate; }

  Minilogue(void);

  /* VCO SETTINGS */
  void setVCO1Octave(const uint8_t& octave) { mVco1.setOctave(octave); }
  void setVCO2Octave(const uint8_t& octave) { mVco2.setOctave(octave); }

  void setVCO1OscType(const VCO::OSC_TYPE& oscType) { mVco1.setOscillatorType(oscType); }
  void setVCO2OscType(const VCO::OSC_TYPE& oscType) { mVco2.setOscillatorType(oscType); }

  void setVCO1FineTune(const float& fineTune) { mVco1.setFineTune(fineTune); }
  void setVCO2FineTune(const float& fineTune) { mVco2.setFineTune(fineTune); }
  
  void setVCO1Shape(const float& shape) { mVco1.setShape(shape); }
  void setVCO2Shape(const float& shape) { mVco2.setShape(shape); }

  /* MIXER SETTINGS */
  void setVCO1Level(const float& level) { mMixer.setVco1Level(level); }
  void setVCO2Level(const float& level) { mMixer.setVco2Level(level); }
  void setNoiseLevel(const float& level) { mMixer.setNoiseLevel(level); }
 
  /* AMP SETTINGS */
  void setAmpAttack(const float& value) { mAmp.setAttack(value); }
  void setAmpDecay(const float& value) { mAmp.setDecay(value); }
  void setAmpSustain(const float& value) { mAmp.setSustain(value); }
  void setAmpRelease(const float& value) { mAmp.setRelease(value); }

  /* NOTE PLAYBACK */
  void noteOn(const int& midiNoteNumber, const int& midiNoteVelocity, const int& samplePosition);
  void noteOff(const int& midiNoteNumber, const int& midiNoteVelocity, const int& samplePosition);
  void processBlock(float* lChannelBuffer, float* rChannelBuffer, const int& bufferSize);

private:

  static constexpr unsigned int DEFAULT_SAMPLE_RATE = 44100;
  inline static unsigned int sSampleRate = DEFAULT_SAMPLE_RATE;
  inline static float sOffset = 1.0f / sSampleRate;

  float getSample(void);

  VCO mVco1;
  VCO mVco2;
  Voice mVoice;
  Mixer mMixer;
  EnvelopeGenerator mAmp;

  /**
   * VCOModulator mVco2Modulator;
   * Filter mFilter;
   * EnvelopeGenerator mEG;
   * Delay mDelay;
   * 
   * Slider mSlider; //pitch slider
  */

};

};


#endif
