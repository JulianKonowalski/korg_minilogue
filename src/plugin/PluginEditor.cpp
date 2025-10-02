#include "plugin/PluginProcessor.hpp"
#include "plugin/PluginEditor.hpp"

PluginEditor::PluginEditor(
    PluginProcessor& audio_processor
) : juce::AudioProcessorEditor::AudioProcessorEditor(&audio_processor), 
    m_audio_processor(audio_processor)
{
    juce::ignoreUnused(m_audio_processor);
    setSize(800, 500);
}

void PluginEditor::paint(juce::Graphics& graphics) {
    graphics.fillAll(juce::Colours::lightblue);
    graphics.setColour(juce::Colours::darkblue);
    graphics.setFont(20.0f);
    graphics.drawText("Hello World!", getLocalBounds(), juce::Justification::centred, true);
}

void PluginEditor::resized(void) {

}