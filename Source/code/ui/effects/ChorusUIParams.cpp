#include "../../../includes/ui/effects/ChorusUIParams.hpp"

ChorusUIParams::ChorusUIParams()
{
}

ChorusUIParams::~ChorusUIParams()
{
}

void ChorusUIParams::paint(juce::Graphics& g) {
    auto localBoundsW = getLocalBounds().getWidth();
    auto x = 0;
    auto y = 10;
    auto w = localBoundsW;
    auto h = 27;

    g.setColour(juce::Colours::red);
    g.setFont(25);
	g.drawText("Chorus", juce::Rectangle<float>(x, y, w, h), juce::Justification::centred, false);
}

void ChorusUIParams::resized() {
	
}