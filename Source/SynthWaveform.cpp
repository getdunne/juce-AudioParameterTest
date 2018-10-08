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
