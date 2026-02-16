#include "../../../includes/ui/components/TurnableKnob.hpp"
#include "../../../includes/dsp/PluginProcessor.h"

TurnableKnob::TurnableKnob(const std::string& name, AudioPluginAudioProcessor& p)
{
    addAndMakeVisible(this->knob);
    this->knob.setAlpha(0.4f);
	this->knob.setColour(juce::Slider::thumbColourId, juce::Colours::red);
	this->knob.setTitle(name);
	this->knob.setSliderStyle(juce::Slider::SliderStyle::Rotary);
	this->knob.setEnabled(false);
    this->knob.setNumDecimalPlacesToDisplay(1);
    this->knob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);

    this->attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        p.getApvts(),  // The APVTS instance
        name,                // Parameter ID (must match!)
        this->knob             // The slider to attach
    );
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

void TurnableKnob::setCostomTextBoxStyle(juce::Slider::TextEntryBoxPosition newPosition, bool isReadOnly, int textEntryBoxWidth, int textEntryBoxHeight, const juce::String &suffix) {
    this->knob.setTextBoxStyle(newPosition, isReadOnly, textEntryBoxWidth, textEntryBoxHeight);
    this->knob.setTextValueSuffix(suffix);
    this->knob.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colours::black);
    this->knob.setColour(juce::Slider::textBoxTextColourId, juce::Colours::red);
    this->knob.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::red);
}
