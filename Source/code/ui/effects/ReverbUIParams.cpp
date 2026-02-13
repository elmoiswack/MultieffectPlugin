#include "../../../includes/ui/effects/ReverbUIParams.hpp"

ReverbUIParams::ReverbUIParams()
{
}

ReverbUIParams::~ReverbUIParams()
{
}

void ReverbUIParams::paint(juce::Graphics& g) {
    auto localBoundsW = getLocalBounds().getWidth();
    auto localBoundsCenterY = getLocalBounds().getCentreY();
    auto localBoundsH = getLocalBounds().getHeight();
    auto x = 0;
    auto y = 10;
    auto w = localBoundsW;
    auto h = 27;

    g.setColour(juce::Colours::red);
    g.setFont(25);
	g.drawText("Reverb", juce::Rectangle<float>(x, y, w, h), juce::Justification::centred, false);
}

void ReverbUIParams::resized() {
	
}