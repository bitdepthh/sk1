/*
  ==============================================================================

    AudioRecorder.cpp
    Created: 27 Jul 2023 3:59:04am
    Author:  Russell Pau

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AudioRecorder.h"
//==============================================================================
AudioRecorder::AudioRecorder(Sk1AudioProcessor& p) : audioProcessor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    backgroundThread.startThread();
}

AudioRecorder::~AudioRecorder()
{
    stop();
}

void AudioRecorder::startRecording (const juce::File& file)
{
    stop();

    if (sampleRate > 0)
    {
        // Create an OutputStream to write to our destination file...
        file.deleteFile();

        if (auto fileStream = std::unique_ptr<juce::FileOutputStream> (file.createOutputStream()))
        {
            // Now create a WAV writer object that writes to our output stream...
            juce::WavAudioFormat wavFormat;

            if (auto writer = wavFormat.createWriterFor (fileStream.get(), sampleRate, 1, 8, {}, 0))
            {
                fileStream.release(); // (passes responsibility for deleting the stream to the writer object that is now using it)

                // Now we'll create one of these helper objects which will act as a FIFO buffer, and will
                // write the data to disk on our background thread.
                threadedWriter.reset (new juce::AudioFormatWriter::ThreadedWriter (writer, backgroundThread, 32768));

                numChannels = writer -> getNumChannels();
                nextSampleNum = 0;

                // And now, swap over our active writer pointer so that the audio callback will start using it..
                const juce::ScopedLock sl (writerLock);
                activeWriter = threadedWriter.get();
            }
        }
    }
}

void AudioRecorder::stop()
{
    // First, clear this pointer to stop the audio callback from using our writer object..
    {
        const juce::ScopedLock sl (writerLock);
        activeWriter = nullptr;
    }

    // Now we can delete the writer object. It's done in this order because the deletion could
    // take a little time while remaining data gets flushed to disk, so it's best to avoid blocking
    // the audio callback while this happens.
    threadedWriter.reset();
}

bool AudioRecorder::isRecording() const
{
    return activeWriter.load() != nullptr;
}

void AudioRecorder::audioDeviceAboutToStart(juce::AudioIODevice* device)
{
    //sampleRate = device->getCurrentSampleRate();
    sampleRate = 9380;
}

void AudioRecorder::audioDeviceStopped()
{
    sampleRate = 0;
}

void AudioRecorder::audioDeviceIOCallbackWithContext (const float* const* inputChannelData, int numInputChannels,
                                       float* const* outputChannelData, int numOutputChannels,
                                       int numSamples, const juce::AudioIODeviceCallbackContext& context)
{
    ignoreUnused (context);

    const juce::ScopedLock sl (writerLock);

    if (activeWriter.load() != nullptr && numInputChannels >= numChannels)
    {
        activeWriter.load()->write (inputChannelData, numSamples);

        // Create an AudioBuffer to wrap our incoming data, note that this does no allocations or copies, it simply references our input data
        juce::AudioBuffer<float> buffer (const_cast<float**> (inputChannelData), numChannels, numSamples);
        nextSampleNum += numSamples;
    }

    // We need to clear the output buffers, in case they're full of junk..
    for (int i = 0; i < numOutputChannels; ++i)
        if (outputChannelData[i] != nullptr)
            juce::FloatVectorOperations::clear (outputChannelData[i], numSamples);
}


