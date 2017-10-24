#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class SynthWaveform
{
private:
    enum WaveformTypeIndex {
        kSine, kTriangle, kSquare, kSawtooth,
        kNumberOfWaveformTypes
    } index;
    
    friend class SynthOscillator;

public:
    // default constructor
    SynthWaveform() : index(kSine) {}

    // set to default state after construction
    void setToDefault() { index = kSine; }

    // get index as a 0-based integer
    int getIndex() { return (int)index; }

    // serialize: get human-readable name of this waveform
    String name();

    // deserialize: set index based on given name
    void setFromName(String wfName);

    // convenience funtions to allow selecting SynthWaveform from a juce::comboBox
    static void setupComboBox(ComboBox& cb);
    void fromComboBox(ComboBox& cb);
    void toComboBox(ComboBox& cb);

    // waveform names: ordered list of string literals
    static const StringArray names;
};
