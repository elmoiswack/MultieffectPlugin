#ifndef TURNABLEKNOB_HPP
# define TURNABLEKNOB_HPP

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>

class AudioPluginAudioProcessor;

class TurnableKnob : public juce::Component
{
private:
	juce::Slider knob;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachement;
public:
	explicit TurnableKnob(const std::string& name, AudioPluginAudioProcessor& p);
	~TurnableKnob() override;

    void resized() override;
	
	void setEnabled(bool value);
	void setAlpha(float value);
	void setCostomTextBoxStyle(juce::Slider::TextEntryBoxPosition newPosition, bool isReadOnly, int textEntryBoxWidth, int textEntryBoxHeight, const juce::String &suffix);

};

#endif