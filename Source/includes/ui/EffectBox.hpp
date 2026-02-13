#ifndef EFFECTBOX_HPP
# define EFFECTBOX_HPP

#include <juce_gui_basics/juce_gui_basics.h>
#include "./TurnableKnob.hpp"

class EffectBox : public juce::Component
{
private:
	juce::ImageButton powerButton;
	const juce::String effectName;
	TurnableKnob volumeKnob{"MIX"};
	juce::Slider mixFader;
	bool isSelected;

	const juce::Colour ON = juce::Colours::green;
	const juce::Colour OFF = juce::Colours::red;
	const juce::Colour SELECTED = juce::Colours::blue;

public:
	EffectBox(juce::String name, const juce::Image& powerButtonImage);
	~EffectBox() override;

	void paint (juce::Graphics&) override;
    void resized() override;
    void mouseUp (const juce::MouseEvent& event) override;
	std::function<void()> onClicked;

	void setSelected(bool shouldBeSelected);
	const juce::String& getEffectName() const;

	bool getIsActive() const;
	void setIsActive(bool newValue);
};


#endif 