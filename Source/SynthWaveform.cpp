#include "SynthWaveform.h"

const StringArray SynthWaveform::names = { "Sine", "Triangle", "Square", "Sawtooth" };

void SynthWaveform::setFromName(String wfName)
{
    for (int i = 0; i < kNumberOfWaveformTypes; i++)
    {
        if (wfName == names[i])
        {
            index = (WaveformTypeIndex)i;
            return;
        }
    }

    // Were we given an invalid waveform name?
    jassertfalse;
}

String SynthWaveform::name()
{
    return names[index];
}

void SynthWaveform::setupComboBox(ComboBox& cb)
{
    for (int i = 0; i < kNumberOfWaveformTypes; i++)
        cb.addItem(names[i], i + 1);
}

void SynthWaveform::fromComboBox(ComboBox& cb)
{
    index = (WaveformTypeIndex)(cb.getSelectedItemIndex());
}

void SynthWaveform::toComboBox(ComboBox& cb)
{
    cb.setSelectedItemIndex((int)index);
}
