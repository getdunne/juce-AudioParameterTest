#include "PluginProcessor.h"
#include "PluginEditor.h"

PluginEditor::PluginEditor (PluginProcessor& p)
    : AudioProcessorEditor(&p)
    , processor(p)
    , parameters(p.parameters)
    , waveformLabel(PluginParameters::waveform_Name, PluginParameters::waveform_Label)
    , noteNumberLabel(PluginParameters::midiNoteNumber_Name, PluginParameters::midiNoteNumber_Label)
    , levelLabel(PluginParameters::level_Name, PluginParameters::level_Label)
    , loudLabel(PluginParameters::loud_Name, PluginParameters::loud_Label)
{
    auto initLabel = [this](Label& label)
    {
        addAndMakeVisible(label);
        label.setFont(Font(15.00f, Font::plain).withTypefaceStyle("Regular"));
        label.setJustificationType(Justification::centredRight);
        label.setEditable(false, false, false);
        label.setColour(TextEditor::textColourId, Colours::black);
        label.setColour(TextEditor::backgroundColourId, Colour(0x00000000));
    };

    initLabel(waveformLabel);
    initLabel(noteNumberLabel);
    initLabel(levelLabel);
    initLabel(loudLabel);

    auto initCombo = [this](ComboBox& combo)
    {
        addAndMakeVisible(combo);
        combo.setEditableText(false);
        combo.setJustificationType(Justification::centredLeft);
        combo.setTextWhenNothingSelected("");
        combo.setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
        combo.addListener(&parameters);
    };

    initCombo(waveformCombo);
    SynthWaveform::setupComboBox(waveformCombo);

    auto initSlider = [this](Slider& slider)
    {
        addAndMakeVisible(slider);
        slider.setSliderStyle(Slider::LinearHorizontal);
        slider.setTextBoxStyle(Slider::TextBoxRight, false, 80, 20);
        slider.addListener(&parameters);
    };

    initSlider(noteNumberSlider); noteNumberSlider.setRange(0, 127, 1);
    initSlider(levelSlider); levelSlider.setRange(0, 1, 0);

    auto initToggle = [this](ToggleButton& toggle)
    {
        addAndMakeVisible(toggle);
        toggle.addListener(&parameters);
    };

    initToggle(loudToggle);

    parameters.AttachControls(&waveformCombo, &noteNumberSlider, &levelSlider, &loudToggle);
    parameters.UpdateControlsFromWorkingValues();

    setSize (600, 300);
}

void PluginEditor::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void PluginEditor::resized()
{
    const int labelLeft = 16;
    const int controlLeft = 144;
    const int labelWidth = 120;
    const int cboxWidth = 150;
    const int sliderWidth = 420;
    const int toggleWidth = 24;
    const int controlHeight = 24;
    const int gapHeight = 8;

    int top = 20;
    waveformLabel.setBounds(labelLeft, top, labelWidth, controlHeight);
    waveformCombo.setBounds(controlLeft, top, cboxWidth, controlHeight);
    top += controlHeight + gapHeight;
    noteNumberLabel.setBounds(labelLeft, top, labelWidth, controlHeight);
    noteNumberSlider.setBounds(controlLeft, top, sliderWidth, controlHeight);
    top += controlHeight + gapHeight;
    levelLabel.setBounds(labelLeft, top, labelWidth, controlHeight);
    levelSlider.setBounds(controlLeft, top, sliderWidth, controlHeight);
    top += controlHeight + gapHeight;
    loudLabel.setBounds(labelLeft, top, labelWidth, controlHeight);
    loudToggle.setBounds(controlLeft, top, toggleWidth, controlHeight);
}
