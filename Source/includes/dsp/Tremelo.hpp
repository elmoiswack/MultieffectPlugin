#ifndef TREMELO_HPP
# define TREMELO_HPP

#include <juce_dsp/juce_dsp.h>
#include <cmath>

enum WaveformTypes {
	SINE,
	TRIANGLE,
	SQUARE,
	SAW
};

class Tremelo
{
private:
	float rate;
    float depth;
    float t;
	WaveformTypes waveform;
	double sampleRate;
public:
	Tremelo();
	~Tremelo();

	void setSampleRate(double sampleRate);
	void setWaveform(WaveformTypes waveform);
	void setRate(float rate);
	void setDepth(float depth);

	float applySine();
	float applyTriangle();
	float applySquare();
	float applySaw();
	float amplifyModifaction(float currentSample);
};

#endif