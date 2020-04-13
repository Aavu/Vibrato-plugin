/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Vibrato.h"

//==============================================================================
/**
*/
class VibratoAudioProcessor  : public AudioProcessor,
                               public AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    VibratoAudioProcessor();
    ~VibratoAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    AudioProcessorValueTreeState& getState();
private:
    void parameterChanged (const String& parameterID, float newValue) override;

    const float m_fMaxModWidthInS;
    const float m_fWidthRampLengthInS;
    const float m_fBypassRampLengthInS;

    SmoothedValue<float, ValueSmoothingTypes::Linear>           m_sfWidth;
    SmoothedValue<float, ValueSmoothingTypes::Multiplicative>   m_sfFreq;
    SmoothedValue<float, ValueSmoothingTypes::Linear>           m_sfBypass;

    std::atomic<float>  m_fWidth;
    std::atomic<float>  m_fFreq;
    std::atomic<bool>   m_bBypass;

    AudioProcessorValueTreeState m_state;

    CVibrato* m_pCVibrato = nullptr;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VibratoAudioProcessor)
};
