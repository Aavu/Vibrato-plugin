/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VibratoAudioProcessor::VibratoAudioProcessor() :
#ifndef JucePlugin_PreferredChannelConfigurations
     AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
#endif
    m_fMaxModWidthInS(.01), m_fRampLengthInS(3e-3), m_fWidth(0.001), m_fFreq(5), m_bBypass(false),
    m_state(*this, nullptr, "Parameters", {
        std::make_unique<AudioParameterFloat>("width", "Width", NormalisableRange<float>(0, m_fMaxModWidthInS, 0.0001), m_fWidth),
        std::make_unique<AudioParameterFloat>("freq", "LFO Frequency", NormalisableRange<float>(0.1, 20, 0.1), m_fFreq),
        std::make_unique<AudioParameterBool>("bypass", "Bypass", m_bBypass)
    })
{
    m_state.addParameterListener("width", this);
    m_state.addParameterListener("freq", this);
    m_state.addParameterListener("bypass", this);

    CVibrato::createInstance(m_pCVibrato);
}

VibratoAudioProcessor::~VibratoAudioProcessor()
{
    CVibrato::destroyInstance(m_pCVibrato);
}

//==============================================================================
const String VibratoAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool VibratoAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool VibratoAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool VibratoAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double VibratoAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int VibratoAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int VibratoAudioProcessor::getCurrentProgram()
{
    return 0;
}

void VibratoAudioProcessor::setCurrentProgram (int index)
{
}

const String VibratoAudioProcessor::getProgramName (int index)
{
    return {};
}

void VibratoAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void VibratoAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

    m_sfWidth.reset(sampleRate, m_fRampLengthInS);
    m_sfFreq.reset(sampleRate, m_fRampLengthInS);
    m_sfBypass.reset(sampleRate, m_fRampLengthInS);

    m_sfWidth.setCurrentAndTargetValue(m_fWidth);
    m_sfFreq.setCurrentAndTargetValue(m_fFreq);
    m_sfBypass.setCurrentAndTargetValue(1 - m_bBypass);

    m_pCVibrato->initInstance(m_fMaxModWidthInS, (float)sampleRate, getTotalNumInputChannels());
    m_pCVibrato->setParam(CVibrato::kParamModWidthInS, m_sfWidth.getTargetValue());
    m_pCVibrato->setParam(CVibrato::kParamModFreqInHz, m_sfFreq.getTargetValue());
}

void VibratoAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool VibratoAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void VibratoAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.



    m_pCVibrato->setParam(CVibrato::kParamModWidthInS, m_sfWidth.getNextValue() * m_sfBypass.getNextValue());
    m_pCVibrato->setParam(CVibrato::kParamModFreqInHz, m_sfFreq.getNextValue());


//    std::cout << m_pCVibrato->getParam(CVibrato::kParamModWidthInS) << " " << m_pCVibrato->getParam(CVibrato::kParamModFreqInHz) << std::endl;

//    for (int channel = 0; channel < totalNumInputChannels; ++channel)
//    {
//        auto* channelData = buffer.getWritePointer (channel);
//        m_ppfAudioData[channel] = channelData;
//    }

    auto **inputBuffer = (float **)buffer.getArrayOfReadPointers();
    auto **outputBuffer = buffer.getArrayOfWritePointers();

    m_pCVibrato->process(inputBuffer, outputBuffer, buffer.getNumSamples()); // In-place processing
}

//==============================================================================
bool VibratoAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* VibratoAudioProcessor::createEditor()
{
    return new VibratoAudioProcessorEditor (*this);
}

//==============================================================================
void VibratoAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    auto state = m_state.copyState();
    std::unique_ptr<XmlElement> xml (state.createXml());
    copyXmlToBinary(*xml, destData);
}

void VibratoAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

    if (xmlState != nullptr)
        if (xmlState->hasTagName (m_state.state.getType()))
            m_state.replaceState (ValueTree::fromXml (*xmlState));
}

AudioProcessorValueTreeState &VibratoAudioProcessor::getState() {
    return m_state;
}

void VibratoAudioProcessor::parameterChanged (const String& parameterID, float newValue)  {
    if (parameterID == "width") {
        m_sfWidth.setTargetValue(newValue);
    } else if (parameterID == "freq") {
        m_sfFreq.setTargetValue(newValue);
    } else if (parameterID == "bypass") {
        m_sfBypass.setTargetValue(1 - newValue);
    }
}


//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new VibratoAudioProcessor();
}
