#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "PluginParameters.h"

class PluginProcessor;

class PluginEditor  : public AudioProcessorEditor
{
public:
    PluginEditor (PluginProcessor&);

    void paint (Graphics&) override;
    void resized() override;

    void update() { parameters.UpdateControlsFromWorkingValues(); }

private:
    PluginProcessor& processor;
    PluginParameters& parameters;

    Label waveformLabel;
    ComboBox waveformCombo;
    Label noteNumberLabel;
    Slider noteNumberSlider;

    Label levelLabel;
    Slider levelSlider;
    Label loudLabel;
    ToggleButton loudToggle;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};
