#include "../../../includes/ui/effects/DistortionUIParams.hpp"

DistortionUIParams::DistortionUIParams()
{
}

DistortionUIParams::~DistortionUIParams()
{
}

void DistortionUIParams::paint(juce::Graphics& g) {
    auto localBoundsW = getLocalBounds().getWidth();
    auto x = 0;
    auto y = 10;
    auto w = localBoundsW;
    auto h = 27;

    g.setColour(juce::Colours::red);
    g.setFont(25);
	g.drawText("Distortion", juce::Rectangle<float>(x, y, w, h), juce::Justification::centred, false);
}

void DistortionUIParams::resized() {
	
}