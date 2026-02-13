#ifndef WAVEFORMGRAPH_HPP
# define WAVEFORMGRAPH_HPP

#include "./AudioGraph.hpp"

class WaveformGraph : public AudioGraph
{
private:
public:
    WaveformGraph();
    ~WaveformGraph() override;
    
    void setBuffer(const juce::AudioBuffer<float>& buffer) override;
	void resized() override;
	
protected:
    void drawGraph(juce::Graphics& g) override;
};

#endif
