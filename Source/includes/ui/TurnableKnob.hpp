#ifndef TURNABLEKNOB_HPP
# define TURNABLEKNOB_HPP

#include <juce_gui_basics/juce_gui_basics.h>

class TurnableKnob : public juce::Component
{
private:
	juce::Slider knob;
public:
	explicit TurnableKnob(const std::string& name);
	~TurnableKnob() override;

    void resized() override;
	
	void setEnabled(bool value);
	void setAlpha(float value);
	void setCostomTextBoxStyle(juce::Slider::TextEntryBoxPosition newPosition, bool isReadOnly, int textEntryBoxWidth, int textEntryBoxHeight);
};

#endif