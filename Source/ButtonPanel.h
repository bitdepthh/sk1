/*
  ==============================================================================

    ButtonPanel.h
    Created: 23 Jul 2023 8:49:38pm
    Author:  Russell Pau

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "AudioRecordingDemo.h"

//==============================================================================
/*
*/
class ButtonPanel  : public juce::Component
{
public:
    ButtonPanel(Sk1AudioProcessor&);
    ~ButtonPanel() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    const int buttonWidth = 50;
    const int buttonHeight = 12;

private:
    Sk1AudioProcessor& audioProcessor;
    AudioRecordingDemo samplingButton;
    
    juce::ShapeButton sampleButton
    { "sample", juce::Colours::gold, juce::Colours::gold , juce::Colours::gold};
    
    juce::ShapeButton portButton
    { "port", juce::Colours::grey, juce::Colours::grey , juce::Colours::grey};
    
    juce::ShapeButton loopButton
    { "loop", juce::Colours::gold, juce::Colours::gold , juce::Colours::gold};
    
    juce::ShapeButton envButton
    { "envelope", juce::Colours::grey, juce::Colours::grey , juce::Colours::grey};
    
    juce::ShapeButton vibratoButton
    { "vibrato", juce::Colours::grey, juce::Colours::grey , juce::Colours::grey};
    
    juce::ShapeButton synthesizingButton
    { "synthesizing", juce::Colours::cornflowerblue, juce::Colours::cornflowerblue , juce::Colours::cornflowerblue};
    
    //========================================================
    
    juce::ShapeButton pianoButton
    { "piano", juce::Colours::grey, juce::Colours::grey , juce::Colours::grey};
    
    juce::ShapeButton trumpetButton
    { "trumpet", juce::Colours::grey, juce::Colours::grey , juce::Colours::grey};
    
    juce::ShapeButton humanButton
    { "human", juce::Colours::grey, juce::Colours::grey , juce::Colours::grey};
    
    juce::ShapeButton pipeButton
    { "pipe", juce::Colours::grey, juce::Colours::grey , juce::Colours::grey};
    
    juce::ShapeButton brassButton
    { "brass", juce::Colours::grey, juce::Colours::grey , juce::Colours::grey};
    
    juce::ShapeButton fluteButton
    { "flute", juce::Colours::grey, juce::Colours::grey , juce::Colours::grey};
    
    juce::ShapeButton drumsButton
    { "drums", juce::Colours::grey, juce::Colours::grey , juce::Colours::grey};
    
    juce::ShapeButton jazzButton
    { "jazz", juce::Colours::grey, juce::Colours::grey , juce::Colours::grey};
    
    juce::ShapeButton synthButton
    { "synth", juce::Colours::cornflowerblue, juce::Colours::cornflowerblue , juce::Colours::cornflowerblue};
    
    juce::ImageComponent mImageComponent;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ButtonPanel)
};
