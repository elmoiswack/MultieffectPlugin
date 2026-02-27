#include "../../includes/dsp/EQ.hpp"

EQ::EQ()
{
	this->s1 = 0.0f;
	this->s2 = 0.0f;
	this->a0 = 0.0f;
	this->a1 = 0.0f;
	this->a2 = 0.0f;
	this->b0 = 0.0f;
	this->b1 = 0.0f;
	this->b2 = 0.0f;
	this->sampleRate = 0.0;
	this->lowCutSlope = 0;
	this->lowCutCutoffFreq = 0.0f;
	this->enabledLowCut = false;
	this->highCutSlope = 0;
	this->highCutCutoffFreq = 0.0f;
	this->enabledHighCut = false;
}

EQ::~EQ()
{
}


void EQ::computeLowCutCoefficients() {
	float w0 = 2 * M_PI * (this->lowCutCutoffFreq / this->sampleRate);
	float alpha = std::sin(w0) / (2 * (1 / std::sqrt(2)));
	this->a0 = 1 + alpha;
	this->a1 = (-2 * std::cos(w0)) / this->a0;
	this->a2 = (1 - alpha) / this->a0;
	this->b0 = ((1 + std::cos(w0)) / 2) / this->a0;
	this->b1 = -(1 + std::cos(w0)) / this->a0;
	this->b2 = ((1 + std::cos(w0)) / 2) / this->a0;
}

void EQ::computeHighCutCoefficients() {
	float w0 = 2 * M_PI * (this->highCutCutoffFreq / this->sampleRate);
	float alpha = std::sin(w0) / (2 * (1 / std::sqrt(2)));
	this->a0 = 1 + alpha;
	this->a1 = (-2 * std::cos(w0)) / this->a0;
	this->a2 = (1 - alpha) / this->a0;
	this->b0 = ((1 - std::cos(w0)) / 2) / this->a0;
	this->b1 = (1 - std::cos(w0)) / this->a0;
	this->b2 = ((1 - std::cos(w0)) / 2) / this->a0;
}

float EQ::calcOutput(float x) {
	float y = this->b0 * x + this->s1;
	this->s1 = this->b1 * x - this->a1 * y + s2;
	this->s2 = this->b2 * x - this->a2 * y;
	return y;
}

float EQ::computeOutputEQ(float currentSample) {
	float y = currentSample;
	
	if (this->enabledLowCut) {
		this->s1 = 0.0f;
		this->s2 = 0.0f;
		this->computeLowCutCoefficients();
		y = this->calcOutput(y);
		for (int i = 0; i < this->lowCutSlope; i++) {
			y = this->calcOutput(y);
		}
	}
	
	if (this->enabledHighCut) {
		this->s1 = 0.0f;
		this->s2 = 0.0f;
		this->computeHighCutCoefficients();
		y = this->calcOutput(y);
		for (int i = 0; i < this->highCutSlope; i++) {
			y = this->calcOutput(y);
		}
	}

	return y;
}

void EQ::setSampleRate(double sampleRate) {
	this->sampleRate = sampleRate;
}

void EQ::setLowCutSlope(int slope) {
	this->lowCutSlope = slope;
}

void EQ::setEnabledLowCut(bool enabled) {
	this->enabledLowCut = enabled;
}

void EQ::setLowCutCutoffFreq(float cutoffFreq) {
	this->lowCutCutoffFreq = cutoffFreq;
}

void EQ::setHighCutSlope(int slope) {
	this->highCutSlope = slope;
}

void EQ::setEnabledHighCut(bool enabled) {
	this->enabledHighCut = enabled;
}

void EQ::setHighCutCutoffFreq(float cutoffFreq) {
	this->highCutCutoffFreq = cutoffFreq;
}
