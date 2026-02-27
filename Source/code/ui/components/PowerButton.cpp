#include "../../../includes/ui/components/PowerButton.hpp"
#include "../../../includes/dsp/PluginProcessor.h"

PowerButton::PowerButton(const juce::String& name, const juce::Image& powerButtonImage, AudioPluginAudioProcessor& p)
{
    addAndMakeVisible(this->button);
    this->button.setClickingTogglesState(true);
    this->button.setToggleable(true);
    this->button.setImages(
        false,   // resizeButtonNowToFitImage =false because of resized
        true,   // preserveProportions
        true,   // opacity
        powerButtonImage,  1.0f, juce::Colours::transparentBlack, // normal
        powerButtonImage,  1.0f, juce::Colours::transparentBlack, // over
        powerButtonImage,  1.0f, juce::Colours::transparentBlack  // down
    );
    this->attachement = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
        p.getApvts(),
        name,
        this->button
    );
    this->button.setAlpha(0.4f);
	this->button.onStateChange = [this]() {
		bool isOn = this->button.getToggleState();
		this->button.setAlpha(isOn ? 1.0f : 0.4f);
        if (onClicked)
            onClicked();
		repaint();
	};
}

PowerButton::~PowerButton()
{
}

void PowerButton::resized() {
    this->button.setBounds(getLocalBounds());
}

bool PowerButton::getSate() {
	return this->button.getToggleState();
}