#include "plugin/PluginProcessor.hpp"
#include "plugin/PluginEditor.hpp"

PluginProcessor::PluginProcessor(
    void
) : AudioProcessor (BusesProperties().withOutput("Output", juce::AudioChannelSet::stereo(), true))
{}

void PluginProcessor::processBlock(
    juce::AudioBuffer<float>& buffer,
    juce::MidiBuffer& midiMessages
) {
    juce::ignoreUnused(midiMessages);

    const int num_input_channels = getTotalNumInputChannels();
    const int num_output_channels = getTotalNumOutputChannels();
    
    for (auto i = num_input_channels; i < num_output_channels; ++i) {
        buffer.clear(i, 0, buffer.getNumSamples());
    }
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter(void) { return new PluginProcessor(); }
inline juce::AudioProcessorEditor* PluginProcessor::createEditor(void) { return new PluginEditor(*this); }