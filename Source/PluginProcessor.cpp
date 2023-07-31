/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Sk1AudioProcessor::Sk1AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), tree(*this, nullptr, "Parameters", createParameters())
#endif
{
    for (int i = 0; i < mNumVoices; i++)
        mSampledInstrument.addVoice(new juce::SamplerVoice());
    
    mSampledInstrument.clearSounds();
    juce::WavAudioFormat wavFormat;
    
    mAllNotes.setRange(0, 128, true);
    
    auto pianoFile = new juce::MemoryInputStream (BinaryData::piano_wav, BinaryData::piano_wavSize, false);
    auto trumpetFile = new juce::MemoryInputStream (BinaryData::trumpet_wav, BinaryData::trumpet_wavSize, false);
    auto humanFile = new juce::MemoryInputStream (BinaryData::human_wav, BinaryData::human_wavSize, false);
    auto pipeFile = new juce::MemoryInputStream (BinaryData::pipe_wav, BinaryData::pipe_wavSize, false);
    auto brassFile = new juce::MemoryInputStream (BinaryData::brass_wav, BinaryData::brass_wavSize, false);
    auto fluteFile = new juce::MemoryInputStream (BinaryData::flute_wav, BinaryData::flute_wavSize, false);
    auto drumsFile = new juce::MemoryInputStream (BinaryData::drums_wav, BinaryData::drums_wavSize, false);
    auto jazzFile = new juce::MemoryInputStream (BinaryData::jazz_wav, BinaryData::jazz_wavSize, false);
    
    auto pianovibFile = new juce::MemoryInputStream (BinaryData::pianovib_wav, BinaryData::pianovib_wavSize, false);
    auto trumpetvibFile = new juce::MemoryInputStream (BinaryData::trumpetvib_wav, BinaryData::trumpetvib_wavSize, false);
    auto humanvibFile = new juce::MemoryInputStream (BinaryData::humanvib_wav, BinaryData::humanvib_wavSize, false);
    auto pipevibFile = new juce::MemoryInputStream (BinaryData::pipevib_wav, BinaryData::pipevib_wavSize, false);
    auto brassvibFile = new juce::MemoryInputStream (BinaryData::brassvib_wav, BinaryData::brassvib_wavSize, false);
    auto flutevibFile = new juce::MemoryInputStream (BinaryData::flutevib_wav, BinaryData::flutevib_wavSize, false);
    auto drumsvibFile = new juce::MemoryInputStream (BinaryData::drumsvib_wav, BinaryData::drumsvib_wavSize, false);
    auto jazzvibFile = new juce::MemoryInputStream (BinaryData::jazzvib_wav, BinaryData::jazzvib_wavSize, false);
    
    pianoReader = wavFormat.createReaderFor(dynamic_cast <juce::InputStream*> (pianoFile), true);
    trumpetReader = wavFormat.createReaderFor(dynamic_cast <juce::InputStream*> (trumpetFile), true);
    humanReader = wavFormat.createReaderFor(dynamic_cast <juce::InputStream*> (humanFile), true);
    pipeReader = wavFormat.createReaderFor(dynamic_cast <juce::InputStream*> (pipeFile), true);
    brassReader = wavFormat.createReaderFor(dynamic_cast <juce::InputStream*> (brassFile), true);
    fluteReader = wavFormat.createReaderFor(dynamic_cast <juce::InputStream*> (fluteFile), true);
    drumsReader = wavFormat.createReaderFor(dynamic_cast <juce::InputStream*> (drumsFile), true);
    jazzReader = wavFormat.createReaderFor(dynamic_cast <juce::InputStream*> (jazzFile), true);
    
    pianovibReader = wavFormat.createReaderFor(dynamic_cast <juce::InputStream*> (pianovibFile), true);
    trumpetvibReader = wavFormat.createReaderFor(dynamic_cast <juce::InputStream*> (trumpetvibFile), true);
    humanvibReader = wavFormat.createReaderFor(dynamic_cast <juce::InputStream*> (humanvibFile), true);
    pipevibReader = wavFormat.createReaderFor(dynamic_cast <juce::InputStream*> (pipevibFile), true);
    brassvibReader = wavFormat.createReaderFor(dynamic_cast <juce::InputStream*> (brassvibFile), true);
    flutevibReader = wavFormat.createReaderFor(dynamic_cast <juce::InputStream*> (flutevibFile), true);
    drumsvibReader = wavFormat.createReaderFor(dynamic_cast <juce::InputStream*> (drumsvibFile), true);
    jazzvibReader = wavFormat.createReaderFor(dynamic_cast <juce::InputStream*> (jazzvibFile), true);
    
    mSampledInstrument.addSound(new juce::SamplerSound("sound", *pianoReader, mAllNotes,
                                                       81, 0.1, 0.1, 10.0));
}

Sk1AudioProcessor::~Sk1AudioProcessor()
{
    delete pianoReader;
    delete trumpetReader;
    delete humanReader;
    delete pipeReader;
    delete brassReader;
    delete fluteReader;
    delete drumsReader;
    delete jazzReader;
    delete synthReader;
    
    delete pianovibReader;
    delete trumpetvibReader;
    delete humanvibReader;
    delete pipevibReader;
    delete brassvibReader;
    delete flutevibReader;
    delete drumsvibReader;
    delete jazzvibReader;
    
    delete sampleReader;
    
    if (juce::File::getSpecialLocation(juce::File::userDocumentsDirectory).getChildFile("sample.wav").exists())
        juce::File::getSpecialLocation(juce::File::userDocumentsDirectory).getChildFile("sample.wav").deleteFile();
}

//==============================================================================
const juce::String Sk1AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Sk1AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Sk1AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Sk1AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Sk1AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Sk1AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Sk1AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Sk1AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Sk1AudioProcessor::getProgramName (int index)
{
    return {};
}

void Sk1AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Sk1AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    mSampledInstrument.setCurrentPlaybackSampleRate(sampleRate);
    defaultSampleRate = sampleRate;
    updateADSR(1);
}

void Sk1AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Sk1AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Sk1AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    if (mInstrument != mPreviousInstrument || mVibState != mPreviousVibState)
        updateInst();
    
    mSampledInstrument.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool Sk1AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Sk1AudioProcessor::createEditor()
{
    return new Sk1AudioProcessorEditor (*this);
}

//==============================================================================
void Sk1AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Sk1AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Sk1AudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout Sk1AudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;
    return {parameters.begin(), parameters.end()};
}

void Sk1AudioProcessor::changeInst (int instrumentIndex){
    switch (instrumentIndex)
    {
        case 0:
            mInstrument = Instrument::piano;
            break;
        case 1:
            mInstrument = Instrument::trumpet;
            break;
        case 2:
            mInstrument = Instrument::human;
            break;
        case 3:
            mInstrument = Instrument::pipe;
            break;
        case 4:
            mInstrument = Instrument::brass;
            break;
        case 5:
            mInstrument = Instrument::flute;
            break;
        case 6:
            mInstrument = Instrument::drums;
            break;
        case 7:
            mInstrument = Instrument::jazz;
            break;
        case 8:
            mInstrument = Instrument::synth;
            break;
        case 9:
            mInstrument = Instrument::sample;
            break;
    }
}

void Sk1AudioProcessor::updateADSR(int envIndex)
{
    switch (envIndex)
    {
        case 1:
            mADSRParams.attack = 0.1f;
            mADSRParams.decay = 3.0f;
            mADSRParams.sustain = 0.0f;
            mADSRParams.release = 0.5f;
            break;
        case 2:
            mADSRParams.attack = 0.1f;
            mADSRParams.decay = 0.0f;
            mADSRParams.sustain = 1.0f;
            mADSRParams.release = 0.5f;
            break;
        case 3:
            mADSRParams.attack = 0.1f;
            mADSRParams.decay = 1.0f;
            mADSRParams.sustain = 0.0f;
            mADSRParams.release = 0.1f;
            break;
        case 4:
            mADSRParams.attack = 0.1f;
            mADSRParams.decay = 3.0f;
            mADSRParams.sustain = 0.0f;
            mADSRParams.release = 3.0f;
            break;
        case 5:
            mADSRParams.attack = 1.0f;
            mADSRParams.decay = 0.1f;
            mADSRParams.sustain = 1.0f;
            mADSRParams.release = 0.5f;
            break;
    }
    
    if (auto sound = dynamic_cast<juce::SamplerSound*>(mSampledInstrument.getSound(0).get())){
        sound->setEnvelopeParameters(mADSRParams);
    }
    
    mADSRInt = envIndex;
}


void Sk1AudioProcessor::addSample()
{
    if (juce::File::getSpecialLocation(juce::File::userDocumentsDirectory).getChildFile("sample.wav").exists())
    {
        juce::WavAudioFormat wavFormat;
        mAllNotes.setRange(0, 128, true);
        auto sampleFile = juce::File::getSpecialLocation(juce::File::userDocumentsDirectory).getChildFile("sample.wav");
        sampleReader = wavFormat.createReaderFor(sampleFile.createInputStream().release(), true);
    }
}

void Sk1AudioProcessor::updateInst()
{
    mPreviousInstrument = mInstrument;
    mPreviousVibState = mVibState;
    
    mSampledInstrument.clearSounds();
    juce::AudioFormatReader *currentAudioReader;
    
    if (mVibState == 0)
        switch(mInstrument)
        {
            case Instrument::piano:
                currentAudioReader = pianoReader;
                mSampledInstrument.setCurrentPlaybackSampleRate(defaultSampleRate);
                mSampledInstrument.addSound(new juce::SamplerSound("sound", *currentAudioReader, mAllNotes,
                                                                   81, 0.1, 0.1, 10.0));
                break;
            case Instrument::trumpet:
                currentAudioReader = trumpetReader;
                mSampledInstrument.setCurrentPlaybackSampleRate(defaultSampleRate);
                mSampledInstrument.addSound(new juce::SamplerSound("sound", *currentAudioReader, mAllNotes,
                                                                   81, 0.1, 0.1, 10.0));
                break;
            case Instrument::human:
                currentAudioReader = humanReader;
                mSampledInstrument.setCurrentPlaybackSampleRate(defaultSampleRate);
                mSampledInstrument.addSound(new juce::SamplerSound("sound", *currentAudioReader, mAllNotes,
                                                                   81, 0.1, 0.1, 10.0));
                break;
            case Instrument::pipe:
                currentAudioReader = pipeReader;
                mSampledInstrument.setCurrentPlaybackSampleRate(defaultSampleRate);
                mSampledInstrument.addSound(new juce::SamplerSound("sound", *currentAudioReader, mAllNotes,
                                                                   81, 0.1, 0.1, 10.0));
                break;
            case Instrument::brass:
                currentAudioReader = brassReader;
                mSampledInstrument.setCurrentPlaybackSampleRate(defaultSampleRate);
                mSampledInstrument.addSound(new juce::SamplerSound("sound", *currentAudioReader, mAllNotes,
                                                                   81, 0.1, 0.1, 10.0));
                break;
            case Instrument::flute:
                currentAudioReader = fluteReader;
                mSampledInstrument.setCurrentPlaybackSampleRate(defaultSampleRate);
                mSampledInstrument.addSound(new juce::SamplerSound("sound", *currentAudioReader, mAllNotes,
                                                                   81, 0.1, 0.1, 10.0));
                break;
            case Instrument::drums:
                currentAudioReader = drumsReader;
                mSampledInstrument.setCurrentPlaybackSampleRate(defaultSampleRate);
                mSampledInstrument.addSound(new juce::SamplerSound("sound", *currentAudioReader, mAllNotes,
                                                                   81, 0.1, 0.1, 10.0));
                break;
            case Instrument::jazz:
                currentAudioReader = jazzReader;
                mSampledInstrument.setCurrentPlaybackSampleRate(defaultSampleRate);
                mSampledInstrument.addSound(new juce::SamplerSound("sound", *currentAudioReader, mAllNotes,
                                                                   81, 0.1, 0.1, 10.0));
                break;
            case Instrument::synth:
                currentAudioReader = synthReader;
                mSampledInstrument.setCurrentPlaybackSampleRate(defaultSampleRate);
                mSampledInstrument.addSound(new juce::SamplerSound("sound", *currentAudioReader, mAllNotes,
                                                                   81, 0.1, 0.1, 10.0));
                break;
            case Instrument::sample:
                if (juce::File::getSpecialLocation(juce::File::userDocumentsDirectory).getChildFile("sample.wav").exists())
                {
                    addSample();
                    currentAudioReader = sampleReader;
                    mSampledInstrument.setCurrentPlaybackSampleRate(9380);
                    mSampledInstrument.addSound(new juce::SamplerSound("sound", *currentAudioReader, mAllNotes,
                                                                       81, 0.1, 0.1, 10.0));
                }
                break;
        }
    else
        switch(mInstrument)
        {
            case Instrument::piano:
                currentAudioReader = pianovibReader;
                mSampledInstrument.setCurrentPlaybackSampleRate(defaultSampleRate);
                mSampledInstrument.addSound(new juce::SamplerSound("sound", *currentAudioReader, mAllNotes,
                                                                   81, 0.1, 0.1, 10.0));
                break;
            case Instrument::trumpet:
                currentAudioReader = trumpetvibReader;
                mSampledInstrument.setCurrentPlaybackSampleRate(defaultSampleRate);
                mSampledInstrument.addSound(new juce::SamplerSound("sound", *currentAudioReader, mAllNotes,
                                                                   81, 0.1, 0.1, 10.0));
                break;
            case Instrument::human:
                currentAudioReader = humanvibReader;
                mSampledInstrument.setCurrentPlaybackSampleRate(defaultSampleRate);
                mSampledInstrument.addSound(new juce::SamplerSound("sound", *currentAudioReader, mAllNotes,
                                                                   81, 0.1, 0.1, 10.0));
                break;
            case Instrument::pipe:
                currentAudioReader = pipevibReader;
                mSampledInstrument.setCurrentPlaybackSampleRate(defaultSampleRate);
                mSampledInstrument.addSound(new juce::SamplerSound("sound", *currentAudioReader, mAllNotes,
                                                                   81, 0.1, 0.1, 10.0));
                break;
            case Instrument::brass:
                currentAudioReader = brassvibReader;
                mSampledInstrument.setCurrentPlaybackSampleRate(defaultSampleRate);
                mSampledInstrument.addSound(new juce::SamplerSound("sound", *currentAudioReader, mAllNotes,
                                                                   81, 0.1, 0.1, 10.0));
                break;
            case Instrument::flute:
                currentAudioReader = flutevibReader;
                mSampledInstrument.setCurrentPlaybackSampleRate(defaultSampleRate);
                mSampledInstrument.addSound(new juce::SamplerSound("sound", *currentAudioReader, mAllNotes,
                                                                   81, 0.1, 0.1, 10.0));
                break;
            case Instrument::drums:
                currentAudioReader = drumsvibReader;
                mSampledInstrument.setCurrentPlaybackSampleRate(defaultSampleRate);
                mSampledInstrument.addSound(new juce::SamplerSound("sound", *currentAudioReader, mAllNotes,
                                                                   81, 0.1, 0.1, 10.0));
                break;
            case Instrument::jazz:
                currentAudioReader = jazzvibReader;
                mSampledInstrument.setCurrentPlaybackSampleRate(defaultSampleRate);
                mSampledInstrument.addSound(new juce::SamplerSound("sound", *currentAudioReader, mAllNotes,
                                                                   81, 0.1, 0.1, 10.0));
                break;
            case Instrument::synth:
                currentAudioReader = synthvibReader;
                mSampledInstrument.setCurrentPlaybackSampleRate(defaultSampleRate);
                mSampledInstrument.addSound(new juce::SamplerSound("sound", *currentAudioReader, mAllNotes,
                                                                   81, 0.1, 0.1, 10.0));
                break;
            case Instrument::sample:
                if (juce::File::getSpecialLocation(juce::File::userDocumentsDirectory).getChildFile("sample.wav").exists())
                {
                    addSample();
                    currentAudioReader = sampleReader;
                    mSampledInstrument.setCurrentPlaybackSampleRate(9380);
                    mSampledInstrument.addSound(new juce::SamplerSound("sound", *currentAudioReader, mAllNotes,
                                                                       81, 0.1, 0.1, 10.0));
                }
                break;
        }
    updateADSR(mADSRInt);
}
