#include "../../../includes/ui/graph/AudioGraph.hpp"

AudioGraph::AudioGraph(AudioAnalyzer& analyzer) : analyzer(analyzer) {
	setOpaque(true);
}

AudioGraph::~AudioGraph() = default;

void AudioGraph::paint (juce::Graphics& g) {
    g.fillAll(juce::Colours::red);
    g.drawRect(getLocalBounds().toFloat(), 2.0f);
	this->drawGraph(g);
}
