#include "../../../includes/ui/effects/TremeloUIParams.hpp"
#include "../../../includes/dsp/PluginProcessor.h"

TremeloUIParams::TremeloUIParams(AudioPluginAudioProcessor& p) : 
    processorRef(p),
    rate("tremelo.rate", p),
    depth("tremelo.depth", p),
    select("tremelo.waveform", juce::StringArray("Sine", "Triangle", "Square", "Saw"), p)
{
    addAndMakeVisible(this->select);
    addAndMakeVisible(this->rate);
    addAndMakeVisible(this->depth);
    
    this->rate.setCostomTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 60, 20, " Hz");
    this->depth.setCostomTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 60, 20, " HZ");

    this->rate.setAlpha(1.0f);
    this->rate.setEnabled(true);
    this->depth.setEnabled(true);
    this->depth.setAlpha(1.0f);
}

TremeloUIParams::~TremeloUIParams()
{
}

void TremeloUIParams::paint(juce::Graphics& g) {
    auto localBoundsW = getLocalBounds().getWidth();
    auto localBoundsCenterY = getLocalBounds().getCentreY();
    auto localBoundsH = getLocalBounds().getHeight();
    auto x = 0;
    auto y = 10;
    auto w = localBoundsW;
    auto h = 27;

    g.setColour(juce::Colours::red);
    g.setFont(25);
	g.drawText("Tremelo", juce::Rectangle<float>(x, y, w, h), juce::Justification::centred, false);

    g.setFont(18);
    auto selectBounds = this->select.getBounds();
    g.drawText("Waveform", juce::Rectangle<float>(selectBounds.getX(), selectBounds.getY() - 40, selectBounds.getWidth(), 40), juce::Justification::centred, false);

    auto rateBounds = this->rate.getBounds();
    g.drawText("Rate", juce::Rectangle<float>(rateBounds.getX(), rateBounds.getY() - 20, rateBounds.getWidth(), 20), juce::Justification::centred, false);

    auto depthBounds = this->depth.getBounds();
    g.drawText("Depth", juce::Rectangle<float>(depthBounds.getX(), depthBounds.getY() - 20, depthBounds.getWidth(), 20), juce::Justification::centred, false);
}

void TremeloUIParams::resized() {
	auto localBoundsW = getLocalBounds().getWidth();
    auto localBoundsCenterY = getLocalBounds().getCentreY();
    auto localBoundsCenterX = getLocalBounds().getCentreX();
    auto localBoundsH = getLocalBounds().getHeight();
    auto buttonWidth = 90;
    auto buttonHeight = 90;

    this->select.setBounds(
        localBoundsCenterX - 50,
        85,
        100,
        30 
    );

    this->rate.setBounds(
        localBoundsCenterX - (buttonWidth / 2),
        localBoundsCenterY - (buttonHeight / 2),
        buttonWidth,
        buttonHeight 
    );

    this->depth.setBounds(
        localBoundsCenterX - (buttonWidth / 2),
        localBoundsH - static_cast<int>(buttonHeight * 1.3),
        buttonWidth,
        buttonHeight
    );
}