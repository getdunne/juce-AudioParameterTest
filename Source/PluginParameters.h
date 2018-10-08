/* Copyright (c) 2017-2018 Shane D. Dunne

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
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
