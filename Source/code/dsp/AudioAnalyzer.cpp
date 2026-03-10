#include "../../includes/dsp/AudioAnalyzer.hpp"

AudioAnalyzer::AudioAnalyzer() {}

AudioAnalyzer::~AudioAnalyzer() {}

void AudioAnalyzer::prepare(double sampleRate) {
    this->historySize = static_cast<int>(sampleRate * 5);
    this->historyBuffer.setSize(1, this->historySize);
    this->historyBuffer.clear();
	this->writePos = 0;
}

void AudioAnalyzer::pushSamples(const juce::AudioBuffer<float>& buffer)
{
    int numSamples = buffer.getNumSamples();
    int numChannels = buffer.getNumChannels();
    
	for (int i = 0; i < numSamples; ++i) {
        float maxSample = 0.0f;
        
		for (int ch = 0; ch < numChannels; ++ch)
            maxSample = std::max(maxSample, std::abs(buffer.getSample(ch, i)));
        
		this->historyBuffer.setSample(0, this->writePos, maxSample);
        this->writePos = (this->writePos + 1) % this->historySize;
    }
}

void AudioAnalyzer::getRecentSamples(juce::AudioBuffer<float>& out, int size) {
    size = std::min(size, this->historySize);
    out.setSize(1, size);

    int start = this->writePos - size;
    if (start < 0)
        start += this->historySize;
    
	for (int i = 0; i < size; ++i) {
        int idx = (start + i) % this->historySize;
        out.setSample(0, i, this->historyBuffer.getSample(0, idx));
    }
}