#ifndef DELAYUIPARAMS_HPP
# define DELAYUIPARAMS_HPP

#include <juce_gui_basics/juce_gui_basics.h>
#include "../components/TurnableKnob.hpp"

class AudioPluginAudioProcessor;

class DelayUIParams : public juce::Component
{
private:
	TurnableKnob feedbackGain;
	TurnableKnob time;
public:
	DelayUIParams(AudioPluginAudioProcessor& p);
	~DelayUIParams() override;

	void paint (juce::Graphics&) override;
    void resized() override;
};

#endif