/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Sk1AudioProcessorEditor::Sk1AudioProcessorEditor (Sk1AudioProcessor& p)
: AudioProcessorEditor (&p), mButtonPanel(p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (mButtonPanel.getWidth()+50, mButtonPanel.getHeight()+50);
    
    addAndMakeVisible(mButtonPanel);
    
    auto logo1 = juce::ImageCache::getFromMemory(BinaryData::logo1_jpg, BinaryData::logo1_jpgSize);
    mLogo.setImage(logo1, juce::RectanglePlacement::stretchToFit);

    
    addAndMakeVisible(mLogo);
    
}

Sk1AudioProcessorEditor::~Sk1AudioProcessorEditor()
{
}

//==============================================================================
void Sk1AudioProcessorEditor::paint (juce::Graphics& g)
{

}

void Sk1AudioProcessorEditor::resized()
{
    juce::Rectangle<int> buttonArea(25, 25, mButtonPanel.getWidth(), mButtonPanel.getHeight());
    
    mButtonPanel.setBounds(buttonArea);
    
    mLogo.setBounds(175 ,0, 175, 25);
}
