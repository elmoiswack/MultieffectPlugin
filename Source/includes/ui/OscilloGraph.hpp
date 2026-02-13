#ifndef OSCILLOSCOPE_HPP
# define OSCILLOSCOPE_HPP

#include "./AudioGraph.hpp"

class OscilloGraph : public AudioGraph
{
public:
	OscilloGraph();
	~OscilloGraph() override;

	void setBuffer(const juce::AudioBuffer<float>& buffer) override;

protected:
	void drawGraph(juce::Graphics& g) override;
};

#endif