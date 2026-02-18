#ifndef PLUGINPARAMSBOX_HPP
# define PLUGINPARAMSBOX_HPP

#include <juce_gui_basics/juce_gui_basics.h>
#include "components/TurnableKnob.hpp"
#include "components/DropDown.hpp"

class AudioPluginAudioProcessor;

class PluginParamsBox : public juce::Component
{
private:
	TurnableKnob gain;
	TurnableKnob lowcutFreq;
	DropDown lowcutSlope;
	TurnableKnob midFreq;
	TurnableKnob midGain;
	TurnableKnob midQuality;
	TurnableKnob highcutFreq;
	DropDown highcutSlope;
	TurnableKnob volume;

public:
	explicit PluginParamsBox(AudioPluginAudioProcessor& p);
	~PluginParamsBox() override;

	void paint (juce::Graphics&) override;
    void resized() override;
};


#endif