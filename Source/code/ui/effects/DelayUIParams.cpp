#include "../../../includes/ui/effects/DelayUIParams.hpp"

DelayUIParams::DelayUIParams(AudioPluginAudioProcessor& p) :
    feedbackGain("delay.feedbackGain", p),
    time("delay.time", p)
{
    addAndMakeVisible(this->time);
    addAndMakeVisible(this->feedbackGain);
    
    this->time.setCostomTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 60, 20, " ms");
    this->feedbackGain.setCostomTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 60, 20, " HZ");

    this->time.setAlpha(1.0f);
    this->time.setEnabled(true);
    this->feedbackGain.setEnabled(true);
    this->feedbackGain.setAlpha(1.0f);
}

DelayUIParams::~DelayUIParams() {}

void DelayUIParams::paint(juce::Graphics& g) {
    auto localBoundsW = getLocalBounds().getWidth();
    auto x = 0;
    auto y = 10;
    auto w = localBoundsW;
    auto h = 27;

    g.setColour(juce::Colours::red);
    g.setFont(25);
	g.drawText("Delay", juce::Rectangle<float>(x, y, w, h), juce::Justification::centred, false);

    g.setFont(18);
    auto feedbackGainBounds = this->feedbackGain.getBounds();
    g.drawText("Feedback Gain", juce::Rectangle<float>(feedbackGainBounds.getX() - 10, feedbackGainBounds.getY() - 20, feedbackGainBounds.getWidth() + 20, 20), juce::Justification::centred, false);

    auto timeBounds = this->time.getBounds();
    g.drawText("Time", juce::Rectangle<float>(timeBounds.getX(), timeBounds.getY() - 20, timeBounds.getWidth(), 20), juce::Justification::centred, false);

}

void DelayUIParams::resized() {
    auto localBoundsCenterY = getLocalBounds().getCentreY();
    auto localBoundsCenterX = getLocalBounds().getCentreX();
    auto localBoundsH = getLocalBounds().getHeight();
    auto buttonWidth = 90;
    auto buttonHeight = 90;

    this->feedbackGain.setBounds(
        localBoundsCenterX - (buttonWidth / 2),
        localBoundsCenterY - (buttonHeight / 2),
        buttonWidth,
        buttonHeight 
    );

    this->time.setBounds(
        localBoundsCenterX - (buttonWidth / 2),
        localBoundsH - static_cast<int>(buttonHeight * 1.3),
        buttonWidth,
        buttonHeight
    );	
}