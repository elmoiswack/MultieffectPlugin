#include "../../includes/ui/PluginParamsBox.hpp"

PluginParamsBox::PluginParamsBox()
{
}

PluginParamsBox::~PluginParamsBox()
{
}

void PluginParamsBox::paint(juce::Graphics& g) {
    g.setColour(juce::Colours::red);
    g.drawRect(getLocalBounds().toFloat(), 2.0f);
}

void PluginParamsBox::resized() {

}
