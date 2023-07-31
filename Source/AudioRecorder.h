/*
  ==============================================================================

    AudioRecorder.h
    Created: 27 Jul 2023 3:59:04am
    Author:  Russell Pau

  ==============================================================================
*/

#pragma once


#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class AudioRecorder  : public juce::AudioIODeviceCallback
{
public:
    AudioRecorder(Sk1AudioProcessor&);
    ~AudioRecorder() override;
    
    void startRecording (const juce::File&);
    void stop();
    bool isRecording() const;
    void audioDeviceAboutToStart(juce::AudioIODevice*) override;
    void audioDeviceStopped() override;
    void audioDeviceIOCallbackWithContext (const float* const* , int ,
                                           float* const* , int ,
                                           int , const juce::AudioIODeviceCallbackContext&) override;
    


private:
    Sk1AudioProcessor& audioProcessor;
    juce::TimeSliceThread backgroundThread {"Audio Recorder Thread"};
    std::unique_ptr<juce::AudioFormatWriter::ThreadedWriter> threadedWriter;
    double sampleRate = 0.0;
    juce::int64 nextSampleNum = 0;
    int numChannels;
    
    juce::CriticalSection writerLock;
    std::atomic<juce::AudioFormatWriter::ThreadedWriter*> activeWriter {nullptr};
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioRecorder)
};
