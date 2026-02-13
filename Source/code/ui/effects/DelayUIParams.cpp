#include "../../../includes/ui/effects/DelayUIParams.hpp"

DelayUIParams::DelayUIParams()
{
}

DelayUIParams::~DelayUIParams()
{
}

void DelayUIParams::paint(juce::Graphics& g) {
    auto localBoundsW = getLocalBounds().getWidth();
    auto localBoundsCenterY = getLocalBounds().getCentreY();
    auto localBoundsH = getLocalBounds().getHeight();
    auto x = 0;
    auto y = 10;
    auto w = localBoundsW;
    auto h = 27;

    g.setColour(juce::Colours::red);
    g.setFont(25);
	g.drawText("Delay", juce::Rectangle<float>(x, y, w, h), juce::Justification::centred, false);
}

void DelayUIParams::resized() {
	
}