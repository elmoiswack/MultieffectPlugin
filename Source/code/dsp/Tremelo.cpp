#include "../../includes/dsp/Tremelo.hpp"

Tremelo::Tremelo()
{
	this->rate = 0.1f;
    this->depth = 0.1f;
    this->t = 0.0f;
	this->sampleRate = 0.0;
}

Tremelo::~Tremelo()
{
}

void Tremelo::setSampleRate(double newSampleRate) {
	this->sampleRate = newSampleRate;
}

void Tremelo::setWaveform(WaveformTypes newWaveform) {
	this->waveform = newWaveform;
}

void Tremelo::setRate(float newRate) {
	this->rate = newRate;
}

void Tremelo::setDepth(float newDepth) {
	this->depth = newDepth;
}

float Tremelo::applySine() {
    return std::sinf(static_cast<float>(2.0f * M_PI * this->rate * this->t));
}

float Tremelo::applyTriangle() {
	float phase = this->rate * this->t;
    const auto offsetPhase = phase - juce::MathConstants<float>::halfPi;
    const auto ft = offsetPhase / juce::MathConstants<float>::twoPi;
    return 4.f * std::abs(ft - std::floor(ft + 0.5f)) - 1.f;
}

float Tremelo::applySquare() {
	float tremFactor = this->depth * std::sinf(static_cast<float>(2.0f * M_PI * this->rate * this->t));
	
	if (tremFactor >= 1)
		return 1.0f;
	else if (tremFactor <= -1)
		return -1.0f;
	return 0.0f;
}

float Tremelo::applySaw() {
	float a = 1 / this->rate;
	float tmp = static_cast<int>(this->t) % static_cast<int>(a);
	return (2 * tmp * this->rate - 1);
}

float Tremelo::amplifyModifaction(float currentSample) {
	float tremFactor = 0.0f;

	switch (this->waveform)
	{
	case WaveformTypes::SINE:
		tremFactor = this->applySine();
		break;
	case WaveformTypes::TRIANGLE:
		tremFactor = this->applyTriangle();
		break ;
	case WaveformTypes::SQUARE:
		tremFactor = this->applySquare();
		break ;
	case WaveformTypes::SAW:
		tremFactor = this->applySaw();
		break ;
	default:
		break;
	}

    this->t += static_cast<float>(2.0f * M_PI * this->rate) / static_cast<float>(this->sampleRate);
    if (this->t >= static_cast<float>(2.0f * M_PI))
        this->t -= static_cast<float>(2.0f * M_PI);

	return (tremFactor * currentSample);
}