#include "plugin/PluginProcessor.h"
#include "plugin/PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessor::AudioPluginAudioProcessor()
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
{
    /* VCO SETTINGS */
    this->attachListener("vco1Fine", [&](const float& value){ this->getSynth().setVCO1FineTune(value); });
    this->attachListener("vco2Fine", [&](const float& value){ this->getSynth().setVCO2FineTune(value); });

    /* MIXER SETTINGS */
    this->attachListener("vco1Volume", [&](const float& value){ this->getSynth().setVCO1Level(value); });
    this->attachListener("vco2Volume", [&](const float& value){ this->getSynth().setVCO2Level(value); });
    this->attachListener("noiseVolume", [&](const float& value){ this->getSynth().setNoiseLevel(value); });
}

AudioPluginAudioProcessor::~AudioPluginAudioProcessor()
{
    for(auto listener : mOwnedListeners) { delete(listener); }
}

//==============================================================================
const juce::String AudioPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AudioPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool AudioPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool AudioPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double AudioPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AudioPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int AudioPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AudioPluginAudioProcessor::setCurrentProgram (int index)
{
    juce::ignoreUnused (index);
}

const juce::String AudioPluginAudioProcessor::getProgramName (int index)
{
    juce::ignoreUnused (index);
    return {};
}

void AudioPluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
    juce::ignoreUnused (index, newName);
}

//==============================================================================
void AudioPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    juce::ignoreUnused (sampleRate, samplesPerBlock);
}

void AudioPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool AudioPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}

void AudioPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer,
                                              juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused (midiMessages);

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    //update state
    // mMinilogue.setVCO1Fine()

    //process midi
    for(const juce::MidiMessageMetadata& metadata : midiMessages) {
        juce::MidiMessage message = metadata.getMessage();
        if(message.isNoteOn()) {
            mMinilogue.noteOn(
                message.getNoteNumber(), 
                message.getVelocity(), 
                metadata.samplePosition
            );
        } else if (message.isNoteOff()) {
            mMinilogue.noteOff(
                message.getNoteNumber(), 
                message.getVelocity(), 
                metadata.samplePosition
            );
        } else if (message.isPitchWheel()) {
            //for now ignore
        }
    }

    //process audio
    mMinilogue.processBlock(
        buffer.getWritePointer(0),
        buffer.getWritePointer(1),
        buffer.getNumSamples()
    );

}

//==============================================================================
bool AudioPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* AudioPluginAudioProcessor::createEditor()
{
    // return new AudioPluginAudioProcessorEditor (*this);
    return new juce::GenericAudioProcessorEditor(*this);
}

juce::AudioProcessorValueTreeState::ParameterLayout 
AudioPluginAudioProcessor::createParameterLayout(void) {
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    /* VCO SETTINGS */
    this->attachParameter(layout, "vco1Fine", "VCO1 Fine Tune", juce::NormalisableRange(-1.0f, 1.0f, 0.001f, 0.5f, true), 0.0f);
    this->attachParameter(layout, "vco2Fine", "VCO2 Fine Tune", juce::NormalisableRange(-1.0f, 1.0f, 0.001f, 0.5f, true), 0.0f);

    /* MIXER SETTINGS */
    this->attachParameter(layout, "vco1Volume", "VCO1 Volume", juce::NormalisableRange(0.0f, 1.0f, 0.01f), 1.0f);
    this->attachParameter(layout, "vco2Volume", "VCO2 Volume", juce::NormalisableRange(0.0f, 1.0f, 0.01f), 1.0f);
    this->attachParameter(layout, "noiseVolume", "Noise Volume", juce::NormalisableRange(0.0f, 1.0f, 0.01f), 0.0f);

    return layout;
}

void AudioPluginAudioProcessor::attachParameter(
    juce::AudioProcessorValueTreeState::ParameterLayout& layout,
    const juce::String& id, 
    const juce::String& name, 
    const juce::NormalisableRange<float>& range, 
    const float& defaultValue
) {
    layout.add(
        std::make_unique<juce::AudioParameterFloat>(
            id,
            name,
            range,
            defaultValue
        )
    );
}

void AudioPluginAudioProcessor::attachListener(
    const juce::String& id, 
    const std::function<void(const float&)>& callback
) {
    ParameterListener* newListener = new ParameterListener(callback);
    mOwnedListeners.push_back(newListener);
    mParameters.addParameterListener(id, newListener);
}

//==============================================================================
void AudioPluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    juce::ignoreUnused (destData);
}

void AudioPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    juce::ignoreUnused (data, sizeInBytes);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AudioPluginAudioProcessor();
}