#ifndef PLUGINPARAMSBOX_HPP
# define PLUGINPARAMSBOX_HPP

#include <juce_gui_basics/juce_gui_basics.h>
#include "components/TurnableKnob.hpp"
#include "components/DropDown.hpp"
#include "components/PowerButton.hpp"

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
	PowerButton enableLowCut;
	PowerButton enableMids;
	PowerButton enableHighCut;

public:
	explicit PluginParamsBox(const juce::Image& powerButtonImage, AudioPluginAudioProcessor& p);
	~PluginParamsBox() override;

	void paint (juce::Graphics&) override;
    void resized() override;
};


#endif