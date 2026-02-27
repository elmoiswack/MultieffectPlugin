#ifndef POWERBUTTON_HPP
# define POWERBUTTON_HPP

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>

class AudioPluginAudioProcessor;

class PowerButton : public juce::Component
{
private:
	juce::ImageButton button;
	std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> attachement;

public:
	explicit PowerButton(const juce::String& name, const juce::Image& powerButtonImage, AudioPluginAudioProcessor& p);
	~PowerButton() override; 

    void resized() override;

	std::function<void()> onClicked;

	bool getSate();
};



#endif