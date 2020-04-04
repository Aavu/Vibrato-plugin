/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VibratoAudioProcessorEditor::VibratoAudioProcessorEditor (VibratoAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    m_pWidthKnob = std::make_unique<Slider>("width");
    m_pFreqKnob = std::make_unique<Slider>("frequency");
    m_pMixKnob = std::make_unique<Slider>("mix");

    m_pWidthKnob->setSliderStyle(Slider::Rotary);
    m_pFreqKnob->setSliderStyle(Slider::Rotary);
    m_pMixKnob->setSliderStyle(Slider::Rotary);

    m_pWidthKnob->setTextBoxStyle(Slider::NoTextBox, false, 100, 100);
    m_pFreqKnob->setTextBoxStyle(Slider::NoTextBox, false, 100, 100);
    m_pMixKnob->setTextBoxStyle(Slider::NoTextBox, false, 100, 100);

    m_pWidthKnobAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getState(), "width", *m_pWidthKnob);
    m_pFreqKnobAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getState(), "frequency", *m_pFreqKnob);
    m_pMixKnobAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getState(), "mix", *m_pMixKnob);

    addAndMakeVisible(m_pWidthKnob.get());
    addAndMakeVisible(m_pFreqKnob.get());
    addAndMakeVisible(m_pMixKnob.get());

    setSize (600, 200);
}

VibratoAudioProcessorEditor::~VibratoAudioProcessorEditor()
{
}

//==============================================================================
void VibratoAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    int width = 100;
    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawText("Width", width, (getHeight() / 2) + 4, width, width, Justification::centred, false);
    g.drawText("LFO Frequency", (getWidth() / 2) - (width/2), (getHeight() / 2) + 4, width, width, Justification::centred, false);
    g.drawText("Mix", getWidth() - (2*width), (getHeight() / 2) + 4, width, width, Justification::centred, false);
}

void VibratoAudioProcessorEditor::resized()
{
    int width = 100;
    m_pWidthKnob->setBounds(width, (getHeight() / 2) - (width / 2), width, width);
    m_pFreqKnob->setBounds((getWidth() / 2) - (width/2), (getHeight() / 2) - (width / 2), width, width);
    m_pMixKnob->setBounds(getWidth() - (2*width), (getHeight() / 2) - (width / 2), width, width);
}