/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <memory>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class VibratoAudioProcessorEditor  :    public AudioProcessorEditor
{
public:
    VibratoAudioProcessorEditor (VibratoAudioProcessor&);
    ~VibratoAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    std::unique_ptr<Slider> m_pWidthKnob;
    std::unique_ptr<Slider> m_pFreqKnob;
    std::unique_ptr<ToggleButton> m_pBypassBtn;

    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> m_pWidthKnobAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> m_pFreqKnobAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> m_pBypassBtnAttachment;
    VibratoAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VibratoAudioProcessorEditor)
};
