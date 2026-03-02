#ifndef FREQUENCYGRAPH_HPP
# define FREQUENCYGRAPH_HPP

#include "./AudioGraph.hpp"
#include <juce_dsp/juce_dsp.h>
#include <vector>
#include <complex>
#include <cmath>

class FrequencyGraph : public AudioGraph
{
public:
	explicit FrequencyGraph(int sampleRate);
	~FrequencyGraph() override;

    void MyFFT(std::vector<std::complex<float>>& input);
	void setBuffer(const juce::AudioBuffer<float>& buffer) override;

protected:
	void drawGraph(juce::Graphics& g) override;
private:
    std::vector<std::complex<float>> fftTmpBuffer;
    std::vector<std::complex<float>> fftInputBuffer;
    std::vector<float> xCoord;
    std::vector<float> yCoord;
    int sampleRate;

};

#endif