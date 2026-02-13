#include "../../includes/ui/OscilloGraph.hpp"

OscilloGraph::OscilloGraph() {
    setOpaque(true);
}

OscilloGraph::~OscilloGraph() = default;

void OscilloGraph::setBuffer(const juce::AudioBuffer<float>& buffer) 
{
    this->displayBuffer.makeCopyOf(buffer);
    repaint();
}

void OscilloGraph::drawGraph(juce::Graphics& g)
{
    int width = getWidth();
    int height = getHeight();
    int numSamples = this->displayBuffer.getNumSamples();
    float centerY = height / 2.0f;
    float scaleY = height / 2.0f * 1.2f;

    juce::Path p;

    float firstY = centerY - this->displayBuffer.getSample(0, 0) * scaleY;
    p.startNewSubPath(0.0f, firstY);

    for (int x = 1; x < width; ++x)
    {
        int sampleIdx = x * numSamples / width;
        float y = centerY - this->displayBuffer.getSample(0, sampleIdx) * scaleY;
        p.lineTo((float)x, y);
    }

    g.setColour(juce::Colours::black);
    g.strokePath(p, juce::PathStrokeType(2.0f));
}

