#ifndef DELAY_HPP
#define DELAY_HPP

#include <juce_audio_basics/juce_audio_basics.h>

class Delay
{
private:
    juce::AudioBuffer<float> delayBuffer;
	int writingPos = {0};

	int delayTime = 250;
	float feedbackGain = 0.6f;

public:
	Delay();
    Delay(double sampleRate, int samplesPerBlock, int numChannels);
	~Delay();

	void copyBufferIntoDelay(const int& channel, const float* bufferData, const int& bufferLenght);
	void copyDelayBufferIntoBuffer(const int& channel, juce::AudioBuffer<float>& buffer, const int& bufferLenght, const double sampleRate);
	void feedbackDelay(const int& channel, const float* bufferData, const int& bufferLenght);
	void computeWritingPos(const int& bufferLenght);

	void resetDelay();

	int getBufferLenght();
	int getWritingPos();
};

#endif
