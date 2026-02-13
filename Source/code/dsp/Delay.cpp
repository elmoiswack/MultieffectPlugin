#include "../../includes/dsp/Delay.hpp"

Delay::Delay() : delayBuffer(0.0f, 0.0f)
{
}

Delay::Delay(double sampleRate, int samplesPerBlock, int numChannels)
    : delayBuffer(numChannels,
                  static_cast<int>(2 * sampleRate * samplesPerBlock))
{
}

Delay::~Delay()
{
}

void Delay::copyBufferIntoDelay(const int& channel, const float* bufferData, const int& bufferLenght) {

    const int delayBufferLenght = this->delayBuffer.getNumSamples();

    if (delayBufferLenght > bufferLenght + this->writingPos) {
		this->delayBuffer.copyFromWithRamp(channel, this->writingPos, bufferData, bufferLenght, this->feedbackGain / 2, this->feedbackGain / 2);
	} else {
        const int bufferRemainder = delayBufferLenght - this->writingPos;

        this->delayBuffer.copyFromWithRamp(channel, this->writingPos, bufferData, bufferRemainder, this->feedbackGain / 2, this->feedbackGain / 2);
		this->delayBuffer.copyFromWithRamp(channel, 0, bufferData, bufferLenght - bufferRemainder, this->feedbackGain / 2, this->feedbackGain / 2);
	}	
}

void Delay::copyDelayBufferIntoBuffer(const int& channel, juce::AudioBuffer<float>& buffer, const int& bufferLenght, const double sampleRate) {
    
	const int delayBufferLenght = this->delayBuffer.getNumSamples();
	auto delayBufferData = this->delayBuffer.getWritePointer(channel);
	
    const int readPos = static_cast<int> (delayBufferLenght + this->writingPos - (sampleRate * this->delayTime / 1000)) % delayBufferLenght;

    if (delayBufferLenght > bufferLenght + readPos) {
        buffer.addFrom(channel, 0, delayBufferData + readPos, bufferLenght);
    } else {
        const int bufferRemainder = delayBufferLenght - readPos;

        buffer.addFrom(channel, 0, delayBufferData + readPos, bufferRemainder);
        buffer.addFrom(channel, bufferRemainder, delayBufferData, bufferLenght - bufferRemainder);
    }
}

void Delay::feedbackDelay(const int& channel, const float* dryBufferData, const int& bufferLenght) {

    const int delayBufferLenght = this->delayBuffer.getNumSamples();

    if (delayBufferLenght > bufferLenght + this->writingPos) {
		this->delayBuffer.addFromWithRamp(channel, this->writingPos, dryBufferData, bufferLenght, this->feedbackGain, this->feedbackGain);
	} else {
        const int bufferRemainder = delayBufferLenght - this->writingPos;

        this->delayBuffer.copyFromWithRamp(channel, bufferRemainder, dryBufferData, bufferRemainder, this->feedbackGain, this->feedbackGain);
		this->delayBuffer.copyFromWithRamp(channel, 0, dryBufferData, bufferLenght - bufferRemainder, this->feedbackGain, this->feedbackGain);
	}	
}


void Delay::computeWritingPos(const int& bufferlengt) {
	this->writingPos += bufferlengt;
	this->writingPos %= this->delayBuffer.getNumSamples();
}

void Delay::resetDelay() {
	this->delayBuffer.clear();
	this->writingPos = {0};
}

int Delay::getBufferLenght() {
	return this->delayBuffer.getNumSamples();
}

int Delay::getWritingPos() {
	return this->writingPos;
}