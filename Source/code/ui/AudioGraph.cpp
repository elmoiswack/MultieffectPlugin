#include "../../includes/ui/AudioGraph.hpp"

AudioGraph::AudioGraph() {
	setOpaque(true);
}

AudioGraph::~AudioGraph() = default;

void AudioGraph::paint (juce::Graphics& g) 
{
    g.fillAll(juce::Colours::red);
    g.drawRect(getLocalBounds().toFloat(), 2.0f);

    auto numSamples = displayBuffer.getNumSamples();
    if (numSamples < 2)
        return;

    auto* samples = displayBuffer.getReadPointer(0);

    bool hasSignal = false;
    constexpr float silenceThreshold = 1.0e-6f;
    for (int i = 0; i < numSamples; ++i)
    {
        if (std::abs(samples[i]) > silenceThreshold)
        {
            hasSignal = true;
            break;
        }
    }
    if (!hasSignal)
        return;

	this->drawGraph(g);
}

void AudioGraph::resized() {}

void AudioGraph::setBuffer(const juce::AudioBuffer<float>& buffer) 
{
    this->displayBuffer.makeCopyOf(buffer);
    repaint();
}

juce::AudioBuffer<float> AudioGraph::getBuffer() {
	return this->displayBuffer;
}