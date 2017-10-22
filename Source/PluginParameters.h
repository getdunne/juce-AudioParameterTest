#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthWaveform.h"

struct PluginParameters :   public Slider::Listener,
                            public ComboBox::Listener,
                            public Button::Listener
{
    PluginParameters();
    void AttachControls(ComboBox* pWaveformCombo,
                        Slider* pNoteNumberSlider,
                        Slider* pLevelSlider,
                        ToggleButton* pLoudToggle);
    void UpdateWorkingValuesFromPluginParameters();
    void UpdateControlsFromWorkingValues();

    // Actual working parameter values
    SynthWaveform waveform;
    int midiNoteNumber;
    float level;
    bool loud;
    
    // Names are symbolic names used to tag AudioParameter objects and XML attributes
    // Labels are human-friendly identifiers for use in GUIs
    static const String waveform_Name, waveform_Label;
    static const String midiNoteNumber_Name, midiNoteNumber_Label;
    static const String level_Name, level_Label;
    static const String loud_Name, loud_Label;

    // AudioParameter objects
    AudioParameterChoice* pWaveformParam;
    AudioParameterInt* pNoteNumberParam;
    AudioParameterFloat* pLevelParam;
    AudioParameterBool* pLoudParam;

    // ComboBox::Listener methods
    void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override;

    // Slider::Listener methods
    void sliderValueChanged(Slider* slider) override;
    void sliderDragStarted(Slider* slider) override;
    void sliderDragEnded(Slider* slider) override;

    // Button::Listener methods
    void buttonClicked(Button*) override {}
    void buttonStateChanged(Button*) override;

    // get/put XML
    void putToXml(XmlElement& xml);
    void getFromXml(XmlElement* xml);

private:
    // References to controls linked to these parameters
    ComboBox* waveformCombo;
    Slider* noteNumberSlider;
    Slider* levelSlider;
    ToggleButton* loudToggle;
};
