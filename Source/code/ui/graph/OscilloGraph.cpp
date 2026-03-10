#include "../../../includes/ui/graph/OscilloGraph.hpp"

OscilloGraph::OscilloGraph(AudioAnalyzer& analyzer) : AudioGraph(analyzer) {
    setOpaque(true);
}

OscilloGraph::~OscilloGraph() = default;

void OscilloGraph::drawGraph(juce::Graphics& g) {
    juce::AudioBuffer<float> buffer;
    this->analyzer.getRecentSamples(buffer, 1024);

    int width = getWidth();
    int height = getHeight();
    int numSamples = buffer.getNumSamples();
    float centerY = height / 2.0f;
    float scaleY = height / 2.0f * 1.2f;

    juce::Path p;

    float firstY = centerY - buffer.getSample(0, 0) * scaleY;
    p.startNewSubPath(0.0f, firstY);

    for (int x = 1; x < width; ++x) {
        int sampleIdx = x * numSamples / width;
        float y = centerY - buffer.getSample(0, sampleIdx) * scaleY;
        
        p.lineTo((float)x, y);
    }

    g.setColour(juce::Colours::black);
    g.strokePath(p, juce::PathStrokeType(2.0f));
}

