# juce-AudioParameterTest
This is a very simple [JUCE](https://www.juce.com)-based audio plugin (tested in VST and AU builds only) illustrating one approach to handling parameter automation. It consists of a single oscillator driven by four parameters, accessible either via its own custom GUI, or via the host's (e.g. DAW) generic GUI and automation interface. For simplicity, it ignores MIDI and outputs sound continuously; it is thus a *generator* plugin rather than a *synthesizer*. (For examples of JUCE synthesizers, see my [VanillaJuce](https://github.com/getdunne/VanillaJuce) and [SARAH](https://github.com/getdunne/SARAH) projects.)

As simple as this code may be, it is not a toy example. I have attempted to produce code which can be used as a template for realistic plugin projects with many more parameters. An important aspect of this is that all of the parameter-related code is encapsulated in a single **PluginParameters** class.

# Background #
[JUCE](https://www.juce.com) provides a nice set of classes for handling communication of parameter-value changes between a plugin (VST, AU, etc.) and its host program (e.g. [DAW](https://en.wikipedia.org/wiki/Digital_audio_workstation)). All derive from a common parent **AudioParameter**, and are specialized for the four most common kinds of plugin parameters as follows:
- **AudioParameterFloat** represents a floating-point value, e.g. a value set by a knob or slider. This is the most basic kind of parameter, because floating-point parameters are supported by all plugin hosts, regardless of the specific interface technology.
- **AudioParameterInt** represents an integer value, e.g. something like a MIDI note-number or velocity.
- **AudioParameterBool** represents a logical value (*true* or *false*), e.g. whether a certain effect or function is enabled or not. You could think of this a specialized form of integer parameter where the range is restricted to [0,1].
- **AudioParameterChoice** represents a discrete choice among a defined set of values, e.g. an oscillator waveform type chosen from the set { *sine, triangle, square, sawtooth* }. You could think of this as another specialized form of integer parameter, where the range is restricted to [0, *number_of_choices*-1].

I had difficulty finding code examples showing how all of these classes ought to be used, so as to provide true bi-directional communication of parameter values, i.e.,
- Plugin to host: user manipulates GUI controls, changes are recorded by a host DAW.
- Host to plugin: DAW recreates user's manipulations automatically using playback.

Such bi-directional communication is referred to as *automation* in audio-recording parlance.

# Warning: deprecated approach #
While **AudioParameter** and its descendants are still supported in JUCE 5.1.2, but the critical member function **AudioProcessor::setParameter()** is marked as deprecated, so this approach is likely to become obsolete in some future JUCE release. It's being replaced by a quite different set of classes built around **AudioProcessorValueTreeState**, which offers the possibility of more streamlined code as well as built-in support for *undo* functionality.

I say "offers the possibility", rather than "provides", because as I write this, the documentation and demo code provided for the newer approach is very limited.

I chose to use the older **AudioParameter**-based classes for my first foray into parameter automation, for three reasons:
1. I found it fairly straightforward to understand, unlike the newer approach.
2. Deprecated or not, it works, and should work with at least some older versions of JUCE as well.
3. It supports the four kinds of parameters listed above; **AudioProcessorValueTreeState** seems to support only float parameters at this time.
4. Now that I have something fully working and testable in various DAWs, I have a basis for comparison for when I build an **AudioProcessorValueTreeState**-based version. I am hopeful that at least the overall structure of my code will be useful for this.

# Detailed description coming soon #

I intend to write a more detailed description of this code soon, which will be available at my site http://getdunne.net/wiki.

Note that the **SynthWaveform** and **SynthOscillator** classes are taken directly from my [VanillaJuce](https://github.com/getdunne/VanillaJuce) synthesizer-plugin code; they are not new to this project.
