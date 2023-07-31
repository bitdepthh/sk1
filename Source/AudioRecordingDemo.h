/*
  ==============================================================================

    AudioRecordingDemo.h
    Created: 27 Jul 2023 3:58:43am
    Author:  Russell Pau

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "AudioRecorder.h"

//==============================================================================
/*
*/
class AudioRecordingDemo  : public juce::Component, public juce::Timer
{
public:
    Sk1AudioProcessor& audioProcessor;
    AudioRecordingDemo(Sk1AudioProcessor&);
    ~AudioRecordingDemo() override;
    void paint (juce::Graphics&) override;
    void resized() override;
    
    const int buttonWidth = 50;
    const int buttonHeight = 12;
    
    void timerCallback() override;
    


private:
    void startRecording();
    void stopRecording();
    
    juce::AudioDeviceManager audioDeviceManager;
    AudioRecorder recorder;
    juce::ShapeButton recordButton { "sample", juce::Colours::gold, juce::Colours::gold , juce::Colours::gold};
    juce::File lastRecording;
    
    inline juce::Colour getUIColourIfAvailable (juce::LookAndFeel_V4::ColourScheme::UIColour) noexcept;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioRecordingDemo)
};
