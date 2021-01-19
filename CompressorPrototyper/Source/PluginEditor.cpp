/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CompressorPrototyperAudioProcessorEditor::CompressorPrototyperAudioProcessorEditor (CompressorPrototyperAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    int leftMargin = 32;
    int topMargin = 64;
    
    shadowProperties.radius = 15;
    shadowProperties.offset = juce::Point<int> (-2, 6);
    dialShadow.setShadowProperties (shadowProperties);
    
    sliders.reserve(6);
    sliders = {
        &inputSlider, &ratioSlider, &threshSlider, &attackSlider, &releaseSlider, &trimSlider
    };
    
    labels.reserve(6);
    labels = {
             &inputLabel, &ratioLabel, &threshLabel, &attackLabel, &releaseLabel, &trimLabel
        };
        
    labelTexts.reserve(6);
    labelTexts = {
        inputSliderLabelText, ratioSliderLabelText, threshSliderLabelText, attackSliderLabelText, releaseSliderLabelText, trimSliderLabelText
    };
        
    
    for (auto i = 0; i < sliders.size(); i++) {
        addAndMakeVisible(sliders[i]);
        sliders[i]->setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
        sliders[i]->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 64, 32);
        sliders[i]->setColour(0x1001400, juce::Colour::fromFloatRGBA(1, 1, 1, 0.5f));
        sliders[i]->setColour(0x1001700, juce::Colour::fromFloatRGBA(1, 1, 1, 0.0f));
        sliders[i]->setColour(0x1001500, juce::Colour::fromFloatRGBA(0, 0, 0, 0.25f));
        sliders[i]->setLookAndFeel(&customDial);
        sliders[i]->setComponentEffect(&dialShadow);
        
        if (sliders[i] == &inputSlider) {
            sliders[i]->setBounds(leftMargin, topMargin * 1.25, 172, 172);
        } else {
            sliders[i]->setBounds(sliders[i - 1]->getX() + sliders[i - 1]->getWidth(), topMargin * 1.25f, 172, 172);
        }
    }
    
    inputSlider.setRange(-36, 36, 0.5f);
    ratioSlider.setRange(1, 30, 1);
    threshSlider.setRange(-96, 0, 0.5f);
    attackSlider.setRange(1, 1000, 1);
    releaseSlider.setRange(1, 1000, 1);
    trimSlider.setRange(-36, 36, 0.5f);

    
    for (auto i = 0; i < labels.size(); i++) {
            addAndMakeVisible(labels[i]);
            labels[i]->setText(labelTexts[i], juce::dontSendNotification);
            labels[i]->setJustificationType(juce::Justification::centred);
            labels[i]->setColour(0x1000281, juce::Colour::fromFloatRGBA(1, 1, 1, 0.25f));
            labels[i]->attachToComponent(sliders[i], false);
        }
    
    addAndMakeVisible(windowBorder);
    windowBorder.setText("Compressor");
    windowBorder.setColour(0x1005400, juce::Colour::fromFloatRGBA(1, 1, 1, 0.25f));
    windowBorder.setColour(0x1005410, juce::Colour::fromFloatRGBA(1, 1, 1, 0.25f));
    windowBorder.setBounds(16, 16, 1068, 296);
    
    setSize (1100, 328);
}

CompressorPrototyperAudioProcessorEditor::~CompressorPrototyperAudioProcessorEditor()
{
}

//==============================================================================
void CompressorPrototyperAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colour::fromFloatRGBA(0.1f, 0.12f, 0.16f, 1.0));
        
    juce::Rectangle<int> background = AudioProcessorEditor::getLocalBounds();
    g.setGradientFill(juce::ColourGradient::vertical(juce::Colour::fromFloatRGBA(0.18f, 0.20f, 0.24f, 1.0), 300 * .01, juce::Colour::fromFloatRGBA(0.12f, 0.14f, 0.18f, 1.0), 300 * .99));
    g.fillRect(background);
}

void CompressorPrototyperAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
