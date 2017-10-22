#include "PluginProcessor.h"

// Factory function
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}


// PluginProcessor class
PluginProcessor::PluginProcessor() : AudioProcessor (BusesProperties()
                                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                                       )
{
    addParameter(parameters.pWaveformParam);
    addParameter(parameters.pNoteNumberParam);
    addParameter(parameters.pLevelParam);
    addParameter(parameters.pLoudParam);
}

// Handling parameter automation changes requires that we overload AudioProcessor::setParameter(),
// which is about to be deprecated.
void PluginProcessor::setParameter(int parameterIndex, float newValue)
{
    AudioProcessor::setParameter(parameterIndex, newValue);

    parameters.UpdateWorkingValuesFromPluginParameters();
    oscillator.setWaveform(parameters.waveform);

    PluginEditor* pEditor = (PluginEditor*)getActiveEditor();
    if (pEditor) pEditor->update();
}

PluginProcessor::~PluginProcessor()
{
}

void PluginProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    oscillator.setFrequency(MidiMessage::getMidiNoteInHertz(parameters.midiNoteNumber) / sampleRate);
}

void PluginProcessor::releaseResources()
{
}

bool PluginProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;

    return true;
}

void PluginProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    oscillator.setFrequency(MidiMessage::getMidiNoteInHertz(parameters.midiNoteNumber) / getSampleRate());

    float level = parameters.level;
    if (parameters.loud) level *= 2.0f;
    
    if (buffer.getNumChannels() == 1)
    {
        float* pLeft = buffer.getWritePointer(0);
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            *pLeft++ = oscillator.getSample() * level;
        }
    }
    else
    {
        float* pLeft = buffer.getWritePointer(0);
        float* pRight = buffer.getWritePointer(1);
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            *pLeft++ = *pRight++ = oscillator.getSample() * level;
        }
    }
}

void PluginProcessor::getStateInformation (MemoryBlock& destData)
{
    XmlElement xml = XmlElement(JucePlugin_Name);
    parameters.putToXml(xml);
    copyXmlToBinary(xml, destData);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> pXml = getXmlFromBinary(data, sizeInBytes);
    parameters.getFromXml(pXml);
}
