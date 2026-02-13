#include "../../includes/ui/WaveformGraph.hpp"

WaveformGraph::WaveformGraph() {
    setOpaque(true);
}

WaveformGraph::~WaveformGraph() = default;

void WaveformGraph::setBuffer(const juce::AudioBuffer<float>& buffer) 
{
    this->displayBuffer.makeCopyOf(buffer);
    repaint();
}

void WaveformGraph::resized()
{
    AudioGraph::resized();
}

void WaveformGraph::drawGraph(juce::Graphics& g)
{
    int width  = getWidth();
    int height = getHeight();
    int numSamples = this->displayBuffer.getNumSamples();

    auto* samples = this->displayBuffer.getReadPointer(0);
    float centerY = height / 2.0f;

    float maxSample = 0.0f;
    for (int i = 0; i < numSamples; ++i)
        maxSample = std::max(maxSample, std::abs(samples[i]));

    float scaleY = (height / 2.0f) / maxSample;

    juce::Path waveformPath;
    waveformPath.startNewSubPath(0.0f, centerY - samples[0] * scaleY);

    for (int x = 1; x < width; ++x)
    {
        int sampleIdx = x * numSamples / width;
        float y = centerY - samples[sampleIdx] * scaleY;
        y = juce::jlimit(0.0f, (float)height, y);
        waveformPath.lineTo((float)x, y);
    }

    g.setColour(juce::Colours::black);
    g.strokePath(waveformPath, juce::PathStrokeType(4.0f));

    juce::Path fillPath = waveformPath;
    fillPath.lineTo((float)width - 1, centerY);
    fillPath.lineTo(0.0f, centerY);
    fillPath.closeSubPath();

    g.fillPath(fillPath);
}