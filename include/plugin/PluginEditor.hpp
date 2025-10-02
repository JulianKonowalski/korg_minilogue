#pragma once

#include "plugin/PluginProcessor.hpp"

class PluginEditor final : public juce::AudioProcessorEditor {
public:

    explicit PluginEditor(PluginProcessor& audio_processor);
    ~PluginEditor(void) override = default;

    void paint(juce::Graphics&) override;
    void resized(void) override;

private:

    PluginProcessor& m_audio_processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)

};