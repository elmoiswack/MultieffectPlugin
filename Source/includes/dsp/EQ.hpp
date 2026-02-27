#ifndef EQ_HPP
# define EQ_HPP

#include <cmath>

class EQ
{
private:
	float s1;
	float s2;

	float a0;
	float a1;
	float a2;
	float b0;
	float b1;
	float b2;

	double sampleRate;
	
	int lowCutSlope;
	bool enabledLowCut;
	float lowCutCutoffFreq;
	int highCutSlope;
	bool enabledHighCut;
	float highCutCutoffFreq;

public:
	EQ();
	~EQ();

	void computeLowCutCoefficients();
	void computeHighCutCoefficients();
	float calcOutput(float x);

	float computeOutputEQ(float currentSample);

	void setSampleRate(double sampleRate);
	void setLowCutSlope(int slope);
	void setEnabledLowCut(bool enabled);
	void setLowCutCutoffFreq(float cutoffFreq);
	void setHighCutSlope(int slope);
	void setEnabledHighCut(bool enabled);
	void setHighCutCutoffFreq(float cutoffFreq);
};

#endif