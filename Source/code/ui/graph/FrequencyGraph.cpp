#include "../../../includes/ui/graph/FrequencyGraph.hpp"

FrequencyGraph::FrequencyGraph(AudioAnalyzer& analyzer)
: AudioGraph(analyzer),
  fft(this->fftOrder),
  window(this->fftSize, juce::dsp::WindowingFunction<float>::hann)
{
    startTimerHz(60);
}

FrequencyGraph::~FrequencyGraph() = default;

void FrequencyGraph::computeFFT() {
    auto* samples = this->tempBuffer.getReadPointer(0);

    for (int i = 0; i < this->fftSize; ++i)
        this->fftData[i] = samples[i];

    this->window.multiplyWithWindowingTable(this->fftData, this->fftSize);
    this->fft.performFrequencyOnlyForwardTransform(this->fftData);

    const float normFactor = 1.0f / (this->fftSize / 2);
    const float minDB = -90.0f;
    const float maxDB =   0.0f;
    const float dbRange = maxDB - minDB;

    int startBin = std::max(1, (int)std::ceil(20.0f * this->fftSize / 44100.0f));
    for (int i = 0; i < startBin; ++i)
        this->spectrum[i] = 0.0f;

    for (int i = startBin; i < this->fftSize / 2; ++i) {
        float magnitude = this->fftData[i] * normFactor;
        float db = juce::Decibels::gainToDecibels(magnitude, minDB);
        float normalized = juce::jlimit(0.0f, 1.0f, (db - minDB) / dbRange);

        float coeff = normalized > this->spectrum[i] ? 0.7f : 0.85f;
        this->spectrum[i] = coeff * normalized + (1.0f - coeff) * this->spectrum[i];
    }
}

void FrequencyGraph::drawGraph(juce::Graphics& g) {
    analyzer.getRecentSamples(this->tempBuffer, this->fftSize);

    if (this->tempBuffer.getNumSamples() < this->fftSize)
        return;

    float rms = this->tempBuffer.getRMSLevel(0, 0, this->fftSize);
    if (rms < 0.00001f) {
        for (auto& s : this->spectrum)
            s *= 0.9f;
    } else {
        this->computeFFT();
    }

    auto width  = getWidth();
    auto height = getHeight();
    g.setColour(juce::Colours::black);

    int startBin = std::max(1, (int)std::ceil(20.0f * this->fftSize / 44100.0f));

    for (int i = startBin + 1; i < this->fftSize / 2; ++i) {
        auto x1 = mapFrequencyToX(i - 1, width);
        auto x2 = mapFrequencyToX(i, width);
        auto y1 = height * (1.0f - this->spectrum[i - 1]);
        auto y2 = height * (1.0f - this->spectrum[i]);

        g.drawLine(x1, y1, x2, y2, 2.0f);
    }
}

void FrequencyGraph::timerCallback() {
    repaint();
}

float FrequencyGraph::mapFrequencyToX(int bin, int width) {
    float minFreq = 20.0f;
    float maxFreq = 20000.0f;

    float freq = (bin * 44100.0f) / this->fftSize;
    freq = std::max(freq, minFreq);
    float logPos = std::log10(freq / minFreq) / std::log10(maxFreq / minFreq);
    logPos = juce::jlimit(0.0f, 1.0f, logPos);

    return logPos * width;
}

