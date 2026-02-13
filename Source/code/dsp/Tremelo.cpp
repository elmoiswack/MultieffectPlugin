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

void Tremelo::setSampleRate(double sampleRate) {
	this->sampleRate = sampleRate;
}

void Tremelo::setWaveform(WaveformTypes waveform) {
	this->waveform = waveform;
}

void Tremelo::setRate(float rate) {
	this->rate = rate;
}

void Tremelo::setDepth(float depth) {
	this->depth = depth;
}

float Tremelo::applySine() {
    return std::sinf(2.0f * M_PI * this->rate * this->t);
}

float Tremelo::applyTriangle() {
	float phase = this->rate * this->t;
	return (4 * fabs(phase - floor(phase + 0.5)) - 1);
}

float Tremelo::applySquare() {
	float tremFactor = this->depth * std::sinf(2.0f * M_PI * this->rate * this->t);
	
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

    this->t += (2.0f * M_PI * this->rate) / this->sampleRate;
    if (this->t >= 2.0f * M_PI)
        this->t -= 2.0f * M_PI;

	return (tremFactor * currentSample);
}