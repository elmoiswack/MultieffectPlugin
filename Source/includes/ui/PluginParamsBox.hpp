#ifndef PLUGINPARAMSBOX_HPP
# define PLUGINPARAMSBOX_HPP

#include <juce_gui_basics/juce_gui_basics.h>
#include "components/TurnableKnob.hpp"

class AudioPluginAudioProcessor;

class PluginParamsBox : public juce::Component
{
private:
	TurnableKnob gain;
	TurnableKnob lowcut;
	TurnableKnob mid;
	TurnableKnob highcut;
	TurnableKnob volume;

public:
	explicit PluginParamsBox(AudioPluginAudioProcessor& p);
	~PluginParamsBox() override;

	void paint (juce::Graphics&) override;
    void resized() override;
};


#endif