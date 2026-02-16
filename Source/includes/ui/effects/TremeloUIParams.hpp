#ifndef TREMELOUIPARAMS_HPP
# define TREMELOUIPARAMS_HPP

#include <juce_gui_basics/juce_gui_basics.h>
#include "../components/TurnableKnob.hpp"
#include "../components/DropDown.hpp"

class AudioPluginAudioProcessor;

class TremeloUIParams : public juce::Component
{
private:
	TurnableKnob rate;
	TurnableKnob depth;
	DropDown select;

public:
	TremeloUIParams(AudioPluginAudioProcessor& p);
	~TremeloUIParams() override;

	void paint (juce::Graphics&) override;
    void resized() override;
};



#endif