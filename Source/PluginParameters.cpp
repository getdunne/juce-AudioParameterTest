#include "PluginParameters.h"

// Names are symbolic names used to tag AudioParameter objects and XML attributes
// Labels are human-friendly identifiers for use in GUIs
const String PluginParameters::waveform_Name = "waveform";
const String PluginParameters::waveform_Label = TRANS("Waveform");
const String PluginParameters::midiNoteNumber_Name = "midiNoteNumber";
const String PluginParameters::midiNoteNumber_Label = TRANS("Midi Note Number");
const String PluginParameters::level_Name = "level";
const String PluginParameters::level_Label = TRANS("Level");
const String PluginParameters::loud_Name = "loud";
const String PluginParameters::loud_Label = TRANS("Loud");

PluginParameters::PluginParameters()
{
    // Set default values. waveform already defaults to "Sine"
    level = 0.5f;
    loud = false;
    midiNoteNumber = 60;
    
    // Create parameter objects. The plugin processor will take ownership of these, so this
    // object need not worry about deleting them later.
    pWaveformParam = new AudioParameterChoice(waveform_Name, waveform_Label, SynthWaveform::names, 0);
    pNoteNumberParam = new AudioParameterInt(midiNoteNumber_Name, midiNoteNumber_Label, 0, 127, midiNoteNumber);
    pLevelParam = new AudioParameterFloat(level_Name, level_Label, 0.0f, 1.0f, level);
    pLoudParam = new AudioParameterBool(loud_Name, loud_Label, loud);
}

void PluginParameters::AttachControls(  ComboBox* pWaveformCombo,
                                        Slider* pNoteNumberSlider,
                                        Slider* pLevelSlider,
                                        ToggleButton* pLoudToggle)
{
    waveformCombo = pWaveformCombo;
    noteNumberSlider = pNoteNumberSlider;
    levelSlider = pLevelSlider;
    loudToggle = pLoudToggle;
}

void PluginParameters::UpdateWorkingValuesFromPluginParameters()
{
    waveform.setFromName(pWaveformParam->getCurrentChoiceName());
    midiNoteNumber = pNoteNumberParam->get();
    level = *pLevelParam;
    loud = pLoudParam->get();
}

void PluginParameters::UpdateControlsFromWorkingValues()
{
    waveform.toComboBox(*waveformCombo);
    noteNumberSlider->setValue(midiNoteNumber);
    levelSlider->setValue(level);
    loudToggle->setToggleState(loud, sendNotification);
}

void PluginParameters::comboBoxChanged(ComboBox* combo)
{
    pWaveformParam->beginChangeGesture();
    *pWaveformParam = combo->getSelectedItemIndex();
    pWaveformParam->endChangeGesture();
}

void PluginParameters::sliderValueChanged(Slider* slider)
{
    float newValue = (float)slider->getValue();
    if (slider == noteNumberSlider)
    {
        *pNoteNumberParam = (int)newValue;
    }
    else if (slider == levelSlider)
    {
        *pLevelParam = newValue;
    }
}

void PluginParameters::sliderDragStarted(Slider* slider)
{
    if (slider == noteNumberSlider)
    {
        pNoteNumberParam->beginChangeGesture();
    }
    else if (slider == levelSlider)
    {
        pLevelParam->beginChangeGesture();
    }
}

void PluginParameters::sliderDragEnded(Slider* slider)
{
    if (slider == noteNumberSlider)
    {
        pNoteNumberParam->endChangeGesture();
    }
    else if (slider == levelSlider)
    {
        pLevelParam->endChangeGesture();
    }
}

void PluginParameters::buttonStateChanged(Button* button)
{
    pLoudParam->beginChangeGesture();
    *pLoudParam = button->getToggleState();
    pLoudParam->endChangeGesture();
}

void PluginParameters::putToXml(XmlElement& xml)
{
    xml.setAttribute(waveform_Name, waveform.name());
    xml.setAttribute(midiNoteNumber_Name, midiNoteNumber);
    xml.setAttribute(level_Name, level);
    xml.setAttribute(loud_Name, loud);
}

void PluginParameters::getFromXml(XmlElement* pXml)
{
    SynthWaveform wf;
    wf.setFromName(pXml->getStringAttribute(waveform_Name));
    *pWaveformParam = wf.getIndex();
    *pNoteNumberParam = pXml->getIntAttribute(midiNoteNumber_Name);
    *pLevelParam = (float)pXml->getDoubleAttribute(level_Name);
    *pLoudParam = pXml->getBoolAttribute(loud_Name);
}
