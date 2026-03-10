#ifndef OSCILLOSCOPE_HPP
# define OSCILLOSCOPE_HPP

#include "./AudioGraph.hpp"
#include "../../dsp/AudioAnalyzer.hpp"

class OscilloGraph : public AudioGraph
{
public:
	OscilloGraph(AudioAnalyzer& analyzer);
	~OscilloGraph() override;

protected:
	void drawGraph(juce::Graphics& g) override;
};

#endif