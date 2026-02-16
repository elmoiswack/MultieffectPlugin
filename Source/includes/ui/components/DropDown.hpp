#ifndef DROPDOWN_HPP
# define DROPDOWN_HPP

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>

class AudioPluginAudioProcessor;

class DropDown : public juce::Component
{
private:
	juce::ComboBox box;
	std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> attachement;
	juce::LookAndFeel_V4 customLookAndFeel;
public:
	explicit DropDown(const juce::String& name, const juce::StringArray& options, AudioPluginAudioProcessor& p);
	~DropDown() override;

	void resized() override;
};

#endif