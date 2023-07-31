/*
  ==============================================================================

    ButtonPanel.cpp
    Created: 23 Jul 2023 8:49:38pm
    Author:  Russell Pau

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ButtonPanel.h"

//==============================================================================
ButtonPanel::ButtonPanel(Sk1AudioProcessor& p) : audioProcessor(p), samplingButton(p)
{
    setSize(475,200);
    
    addAndMakeVisible(&samplingButton);

    juce::Rectangle<int> rectangle(buttonWidth, buttonHeight);
    juce::Path buttonShape;
    buttonShape.addRoundedRectangle(rectangle, 2.0f);
    
    sampleButton.setShape(buttonShape, 0, 0, 0);
    addAndMakeVisible(&sampleButton);
    sampleButton.onClick = [this] {audioProcessor.changeInst(9);};
    
    portButton.setShape(buttonShape, 0, 0, 0);
    addAndMakeVisible(&portButton);
    
    vibratoButton.setShape(buttonShape, 0, 0, 0);
    addAndMakeVisible(&vibratoButton);
    vibratoButton.onClick = [this] {audioProcessor.mVibState = (audioProcessor.mVibState == 0) ? 1 : 0;};
    
    loopButton.setShape(buttonShape, 0, 0, 0);
    addAndMakeVisible(&loopButton);
    
    envButton.setShape(buttonShape, 0, 0, 0);
    addAndMakeVisible(&envButton);
    envButton.onClick = [this] {
        juce::PopupMenu menu;
        menu.addItem(1, "envelope 1");
        menu.addItem(2, "envelope 2");
        menu.addItem(3, "envelope 3");
        menu.addItem(4, "envelope 4");
        menu.addItem(5, "envelope 5");
        
        menu.showMenuAsync (juce::PopupMenu::Options(), [this] (int result)
        {
            if (result == 1)
                audioProcessor.updateADSR(1);
            else if (result == 2)
                audioProcessor.updateADSR(2);
            else if (result == 3)
                audioProcessor.updateADSR(3);
            else if (result == 4)
                audioProcessor.updateADSR(4);
            else
                audioProcessor.updateADSR(5);
        }
        );};
    
    synthesizingButton.setShape(buttonShape, 0, 0, 0);
    addAndMakeVisible(&synthesizingButton);
    
    //===================
    
    pianoButton.setShape(buttonShape, 0, 0, 0);
    addAndMakeVisible(&pianoButton);
    pianoButton.onClick = [this] {audioProcessor.changeInst(0);};
    
    trumpetButton.setShape(buttonShape, 0, 0, 0);
    addAndMakeVisible(&trumpetButton);
    trumpetButton.onClick = [this] {audioProcessor.changeInst(1);};
    
    humanButton.setShape(buttonShape, 0, 0, 0);
    addAndMakeVisible(&humanButton);
    humanButton.onClick = [this] {audioProcessor.changeInst(2);};
    
    pipeButton.setShape(buttonShape, 0, 0, 0);
    addAndMakeVisible(&pipeButton);
    pipeButton.onClick = [this] {audioProcessor.changeInst(3);};
    
    brassButton.setShape(buttonShape, 0, 0, 0);
    addAndMakeVisible(&brassButton);
    brassButton.onClick = [this] {audioProcessor.changeInst(4);};
    
    fluteButton.setShape(buttonShape, 0, 0, 0);
    addAndMakeVisible(&fluteButton);
    fluteButton.onClick = [this] {audioProcessor.changeInst(5);};
    
    drumsButton.setShape(buttonShape, 0, 0, 0);
    addAndMakeVisible(&drumsButton);
    drumsButton.onClick = [this] {audioProcessor.changeInst(6);};
    
    jazzButton.setShape(buttonShape, 0, 0, 0);
    addAndMakeVisible(&jazzButton);
    jazzButton.onClick = [this] {audioProcessor.changeInst(7);};
    
    synthButton.setShape(buttonShape, 0, 0, 0);
    addAndMakeVisible(&synthButton);
    
    
    auto logo1 = juce::ImageCache::getFromMemory(BinaryData::logo2_jpg, BinaryData::logo2_jpgSize);
    mImageComponent.setImage(logo1, juce::RectanglePlacement::stretchToFit);

    
    addAndMakeVisible(mImageComponent);
}

ButtonPanel::~ButtonPanel()
{
}

void ButtonPanel::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::transparentWhite);
    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    // draw some placeholder text
    
    g.setColour (juce::Colours::white);
    g.drawLine(230, 160, 295, 160, 2.0f);
    
    g.setFont (juce::Font (10.0f));
    
    g.drawText (" vibrato", 75, 150, buttonWidth, buttonHeight, juce::Justification::bottomLeft, true);
    
    g.drawText (" sampling", 182, 90, buttonWidth, buttonHeight, juce::Justification::bottomLeft, true);
    g.drawText (" envelope", 182, 112, buttonWidth, buttonHeight, juce::Justification::bottomLeft, true);
    g.drawText (" select", 182, 120, buttonWidth, buttonHeight, juce::Justification::bottomLeft, true);
    g.drawText (" synthe-", 182, 142, buttonWidth, buttonHeight, juce::Justification::bottomLeft, true);
    g.drawText (" sizing", 182, 150, buttonWidth, buttonHeight, juce::Justification::bottomLeft, true);
    
    g.drawText ("piano ", 250, 30, buttonWidth, buttonHeight, juce::Justification::bottomRight, true);
    g.drawText ("trumpet ", 250, 60, buttonWidth, buttonHeight, juce::Justification::bottomRight, true);
    g.drawText ("human ", 250, 82, buttonWidth, buttonHeight, juce::Justification::bottomRight, true);
    g.drawText ("voice ", 250, 90, buttonWidth, buttonHeight, juce::Justification::bottomRight, true);
    g.drawText ("pipe ", 250, 112, buttonWidth, buttonHeight, juce::Justification::bottomRight, true);
    g.drawText ("organ ", 250, 120, buttonWidth, buttonHeight, juce::Justification::bottomRight, true);
    
    
    g.drawText (" brass", 410, 22, buttonWidth, buttonHeight, juce::Justification::bottomLeft, true);
    g.drawText (" ensemble", 410, 30, buttonWidth, buttonHeight, juce::Justification::bottomLeft, true);
    g.drawText (" flute", 410, 60, buttonWidth, buttonHeight, juce::Justification::bottomLeft, true);
    g.drawText (" synth.", 410, 82, buttonWidth, buttonHeight, juce::Justification::bottomLeft, true);
    g.drawText (" drums", 410, 90, buttonWidth, buttonHeight, juce::Justification::bottomLeft, true);
    g.drawText (" jazz", 410, 112, buttonWidth, buttonHeight, juce::Justification::bottomLeft, true);
    g.drawText (" organ", 410, 120, buttonWidth, buttonHeight, juce::Justification::bottomLeft, true);
    g.drawText (" sample", 410, 150, buttonWidth, buttonHeight, juce::Justification::bottomLeft, true);
    
    g.setFont (juce::Font (14.0));
    g.setColour (juce::Colours::aquamarine);
    g.drawText ("effect", 25, 170, buttonWidth, buttonHeight, juce::Justification::centred, true);
    g.drawText ("tone", 330, 170, buttonWidth, buttonHeight, juce::Justification::centred, true);
    
}

void ButtonPanel::resized()
{

    samplingButton.setBounds(132, 90, buttonWidth, buttonHeight);
    portButton.setBounds(25, 120, buttonWidth, buttonHeight);
    vibratoButton.setBounds(25, 150, buttonWidth, buttonHeight);
    loopButton.setBounds(25, 90, buttonWidth, buttonHeight);
    envButton.setBounds(132, 120, buttonWidth, buttonHeight);
    synthesizingButton.setBounds(132, 150, buttonWidth, buttonHeight);
    
    pianoButton.setBounds(300, 30, buttonWidth, buttonHeight);
    trumpetButton.setBounds(300, 60, buttonWidth, buttonHeight);
    humanButton.setBounds(300, 90, buttonWidth, buttonHeight);
    pipeButton.setBounds(300, 120, buttonWidth, buttonHeight);
    synthButton.setBounds(300, 150, buttonWidth, buttonHeight);
    
    brassButton.setBounds(360, 30, buttonWidth, buttonHeight);
    fluteButton.setBounds(360, 60, buttonWidth, buttonHeight);
    drumsButton.setBounds(360, 90, buttonWidth, buttonHeight);
    jazzButton.setBounds(360, 120, buttonWidth, buttonHeight);
    sampleButton.setBounds(360, 150, buttonWidth, buttonHeight);
    
    mImageComponent.setBounds(5,5, 250, 75);
    
    // This method is where you should set the bounds of any child
    // components that your component contains..
}



