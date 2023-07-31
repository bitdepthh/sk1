/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "ButtonPanel.h"

//==============================================================================
/**
*/
class Sk1AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Sk1AudioProcessorEditor (Sk1AudioProcessor&);
    ~Sk1AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    ButtonPanel mButtonPanel;
    
    Sk1AudioProcessor& audioProcessor;
    
    juce::ImageComponent mLogo;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Sk1AudioProcessorEditor)
};
