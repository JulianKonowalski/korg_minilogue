#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

#ifndef JucePlugin_Name
    #define JucePlugin_Name "Minilogue"
#endif

class PluginProcessor final : public juce::AudioProcessor {
public:

    //==============================================================================
    PluginProcessor(void);
    ~PluginProcessor(void) override = default;

    //==============================================================================
    inline void prepareToPlay(double sampleRate, int samplesPerBlock) override { juce::ignoreUnused (sampleRate, samplesPerBlock); }
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    inline void releaseResources(void) override {}

    //==============================================================================
    inline bool isBusesLayoutSupported(const BusesLayout& layouts) const override {
        return !(layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
            && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo());
    }

    //==============================================================================
    inline bool hasEditor(void) const override { return true; }
    inline juce::AudioProcessorEditor* createEditor(void) override;

    //==============================================================================
    inline bool acceptsMidi(void) const override { return true; }
    inline bool producesMidi(void) const override { return false; }
    inline bool isMidiEffect(void) const override { return false; }
    inline double getTailLengthSeconds(void) const override { return 0.0; }

    //==============================================================================
    inline const juce::String getName(void) const override { return JucePlugin_Name; }
    inline const juce::String getProgramName(int index) override { juce::ignoreUnused(index); return {}; }
    inline void changeProgramName(int index, const juce::String& newName) override { juce::ignoreUnused (index, newName); }
    
    //==============================================================================
    inline int getNumPrograms(void) override { return 1; }
    inline int getCurrentProgram(void) override { return 0; }
    inline void setCurrentProgram(int index) override { juce::ignoreUnused(index); }

    //==============================================================================
    inline void getStateInformation(juce::MemoryBlock& destData) override { juce::ignoreUnused(destData); }
    inline void setStateInformation(const void* data, int sizeInBytes) override { juce::ignoreUnused(data, sizeInBytes); }
    
private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginProcessor)

};