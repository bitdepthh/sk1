/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class Sk1AudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    Sk1AudioProcessor();
    ~Sk1AudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    void updateADSR (int);
    void updateInst ();
    
    enum class Instrument{
        piano,
        trumpet,
        human,
        pipe,
        brass,
        flute,
        drums,
        jazz,
        synth,
        sample
    };
    
    void changeInst(int);
    
    void addSample();
    
    Instrument mInstrument {Instrument::piano};
    Instrument mPreviousInstrument {Instrument::piano};
    
    juce::AudioProcessorValueTreeState tree;
    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();
    
    juce::BigInteger mAllNotes;
    
    int defaultSampleRate;
    double rawVolume {0.1};
    
    int mADSRInt {1};
    int mVibState {0};
    int mPreviousVibState {0};
    

private:
    
    juce::ADSR::Parameters mADSRParams;
    
    const int mNumVoices {4};
    juce::Synthesiser mSampledInstrument;
    juce::Synthesiser mSampledInstrument2;

    
    juce::AudioFormatReader *pianoReader {nullptr};
    juce::AudioFormatReader *trumpetReader {nullptr};
    juce::AudioFormatReader *humanReader {nullptr};
    juce::AudioFormatReader *pipeReader {nullptr};
    juce::AudioFormatReader *brassReader {nullptr};
    juce::AudioFormatReader *fluteReader {nullptr};
    juce::AudioFormatReader *drumsReader {nullptr};
    juce::AudioFormatReader *jazzReader {nullptr};
    juce::AudioFormatReader *synthReader {nullptr};
    juce::AudioFormatReader *sampleReader {nullptr};
    
    juce::AudioFormatReader *pianovibReader {nullptr};
    juce::AudioFormatReader *trumpetvibReader {nullptr};
    juce::AudioFormatReader *humanvibReader {nullptr};
    juce::AudioFormatReader *pipevibReader {nullptr};
    juce::AudioFormatReader *brassvibReader {nullptr};
    juce::AudioFormatReader *flutevibReader {nullptr};
    juce::AudioFormatReader *drumsvibReader {nullptr};
    juce::AudioFormatReader *jazzvibReader {nullptr};
    juce::AudioFormatReader *synthvibReader {nullptr};
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Sk1AudioProcessor)
};
