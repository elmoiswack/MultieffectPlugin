#ifndef AUDIOANALYZER_HPP
# define AUDIOANALYZER_HPP

#include <juce_audio_basics/juce_audio_basics.h>

class AudioAnalyzer
{
private:
    juce::AudioBuffer<float> historyBuffer = {};
    int historySize = 0;
    int writePos = 0;

public:
	AudioAnalyzer();
	~AudioAnalyzer();

	void prepare(double sampleRate);
	void pushSamples(const juce::AudioBuffer<float>& buffer);
	void getRecentSamples(juce::AudioBuffer<float>& out, int size);

};

#endif