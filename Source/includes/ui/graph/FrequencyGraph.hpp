#ifndef FREQUENCYGRAPH_HPP
# define FREQUENCYGRAPH_HPP

#include "./AudioGraph.hpp"
#include "../../dsp/AudioAnalyzer.hpp"
#include <juce_dsp/juce_dsp.h>
#include <vector>
#include <complex>
#include <cmath>

class FrequencyGraph : public AudioGraph, private juce::Timer
{
public:
    FrequencyGraph(AudioAnalyzer& analyzer);
    ~FrequencyGraph() override;

private:
    static constexpr int fftOrder = 11;
    static constexpr int fftSize  = 1 << fftOrder;

    juce::dsp::FFT fft;
    juce::dsp::WindowingFunction<float> window;
    juce::AudioBuffer<float> tempBuffer;

    float fftData[2 * fftSize];
    float spectrum[fftSize / 2] = { 0.0f };
    float smoothing = 0.2f;

    void drawGraph(juce::Graphics& g) override;
    void timerCallback() override;
    void computeFFT();
    float mapFrequencyToX(int bin, int width);
};

#endif