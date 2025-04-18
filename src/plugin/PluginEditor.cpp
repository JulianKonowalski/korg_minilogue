#include "plugin/PluginProcessor.h"
#include "plugin/PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (
    AudioPluginAudioProcessor& p
) : AudioProcessorEditor (&p), 
    processorRef (p)
{
    juce::ignoreUnused (processorRef);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    mFineTuneSlider.addListener(this);

    mFineTuneSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    mFineTuneSlider.setRange(-1.0f, 1.0f, 0.001f);
    mFineTuneSlider.setValue(0.0f);
    addAndMakeVisible(mFineTuneSlider);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void AudioPluginAudioProcessorEditor::resized()
{
    mFineTuneSlider.setBounds(getLocalBounds());
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void AudioPluginAudioProcessorEditor::sliderValueChanged(juce::Slider* slider) {
    if(slider == &mFineTuneSlider) {
        processorRef.mMinilogue.setVCO1FineTune((float)mFineTuneSlider.getValue());
    }
}