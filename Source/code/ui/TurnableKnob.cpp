#include "../../includes/ui/TurnableKnob.hpp"

TurnableKnob::TurnableKnob(const std::string& name)
{
    addAndMakeVisible(this->knob);
    this->knob.setAlpha(0.4f);
	this->knob.setColour(juce::Slider::thumbColourId, juce::Colours::red);
	this->knob.setTitle(name);
	this->knob.setSliderStyle(juce::Slider::SliderStyle::Rotary);
	this->knob.setEnabled(false);
}

TurnableKnob::~TurnableKnob()
{
}

void TurnableKnob::resized() 
{
    this->knob.setBounds(getLocalBounds());
}

void TurnableKnob::setEnabled(bool value) {
    this->knob.setEnabled(value);
}

void TurnableKnob::setAlpha(float value) {
    this->knob.setAlpha(value);
}

void TurnableKnob::setCostomTextBoxStyle(juce::Slider::TextEntryBoxPosition newPosition, bool isReadOnly, int textEntryBoxWidth, int textEntryBoxHeight) {
    this->knob.setTextBoxStyle(newPosition, isReadOnly, textEntryBoxWidth, textEntryBoxHeight);
}
