/*
  ==============================================================================

    AudioRecordingDemo.cpp
    Created: 27 Jul 2023 3:58:43am
    Author:  Russell Pau

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AudioRecordingDemo.h"

//==============================================================================
AudioRecordingDemo::AudioRecordingDemo(Sk1AudioProcessor& p) : audioProcessor(p), recorder(p)
{
    setOpaque(true);
    
    juce::Rectangle<int> rectangle(buttonWidth, buttonHeight);
    juce::Path buttonShape;
    buttonShape.addRoundedRectangle(rectangle, 2.0f);

    recordButton.setShape(buttonShape, 0, 0, 0);
    addAndMakeVisible (recordButton);
    recordButton.onClick = [this]
    {
        if (recorder.isRecording())
            return;
        else
            if (juce::File::getSpecialLocation(juce::File::userDocumentsDirectory).getChildFile("sample.wav").exists()){
                juce::File::getSpecialLocation(juce::File::userDocumentsDirectory).getChildFile("sample.wav").deleteFile();
            }
            startRecording();
            Timer::startTimer(1400);
    };

    juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                 [this] (bool granted)
                                 {
                                     int numInputChannels = granted ? 2 : 0;
                                     audioDeviceManager.initialise (numInputChannels, 2, nullptr, true, {}, nullptr);
                                 });
    
    audioDeviceManager.addAudioCallback (&recorder);

    setSize (buttonWidth, buttonHeight);
}

AudioRecordingDemo::~AudioRecordingDemo()
{
    audioDeviceManager.removeAudioCallback (&recorder);
}

void AudioRecordingDemo::paint (juce::Graphics& g)
{
    g.fillAll (getUIColourIfAvailable (juce::LookAndFeel_V4::ColourScheme::UIColour::windowBackground));
}

void AudioRecordingDemo::resized()
{
    recordButton.setBounds(0,0,buttonWidth, buttonHeight);
}

void AudioRecordingDemo::startRecording()
{
    if (! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::writeExternalStorage))
    {
        SafePointer<AudioRecordingDemo> safeThis (this);

        juce::RuntimePermissions::request (juce::RuntimePermissions::writeExternalStorage,
                                     [safeThis] (bool granted) mutable
                                     {
                                         if (granted)
                                             safeThis->startRecording();
                                     });
        return;
    }


    auto parentDir = juce::File::getSpecialLocation (juce::File::userDocumentsDirectory);

    lastRecording = parentDir.getNonexistentChildFile ("sample", ".wav");

    recorder.startRecording (lastRecording);

    recordButton.setButtonText ("Stop");
}

void AudioRecordingDemo::stopRecording()
{
    recorder.stop();

   #if JUCE_CONTENT_SHARING
    SafePointer<AudioRecordingDemo> safeThis (this);
    juce::File fileToShare = lastRecording;

    juce::ContentSharer::getInstance()->shareFiles (juce::Array<juce::URL> ({juce::URL (fileToShare)}),
                                              [safeThis, fileToShare] (bool success, const juce::String& error)
                                              {
                                                  if (fileToShare.existsAsFile())
                                                      fileToShare.deleteFile();

                                                  if (! success && error.isNotEmpty())
                                                      juce::NativeMessageBox::showAsync (juce::MessageBoxOptions()
                                                                                     .withIconType (juce::MessageBoxIconType::WarningIcon)
                                                                                     .withTitle ("Sharing Error")
                                                                                     .withMessage (error),
                                                                                   nullptr);
                                              });
   #endif

    lastRecording = juce::File();
}

inline juce::Colour AudioRecordingDemo::getUIColourIfAvailable (juce::LookAndFeel_V4::ColourScheme::UIColour uiColour) noexcept
{
    if (auto* v4 = dynamic_cast<juce::LookAndFeel_V4*> (&juce::LookAndFeel::getDefaultLookAndFeel()))
        return v4->getCurrentColourScheme().getUIColour (uiColour);

    return juce::Colour (0xff4d4d4d);
}

void AudioRecordingDemo::timerCallback()
{
    Timer::stopTimer();
    stopRecording();
}
