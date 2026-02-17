#ifndef PARAMETERS_HPP
# define PARAMETERS_HPP

#include <juce_dsp/juce_dsp.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include <memory>

class Parameters
{
private:
	juce::AudioProcessorValueTreeState apvts;
public:
	explicit Parameters(juce::AudioProcessor& processorRef);
	~Parameters();

	juce::AudioProcessorValueTreeState::ParameterLayout initApvts();
	juce::AudioProcessorValueTreeState& getApvts();

	void initOutput(juce::AudioProcessorValueTreeState::ParameterLayout& layout);
	float getOutputGaindB() const;
	float getOutputLowCutdB() const;
	float getOutputMiddB() const;
	float getOutputHighCutdB() const;
	float getOutputVolumedB() const;
	bool getOutputEnabled() const;

	void initReverb(juce::AudioProcessorValueTreeState::ParameterLayout& layout);
	bool getReverbEnabled() const;

	void initDistortion(juce::AudioProcessorValueTreeState::ParameterLayout& layout);
	bool getDistortionEnabled() const;
	
	void initDelay(juce::AudioProcessorValueTreeState::ParameterLayout& layout);	
	bool getDelayEnabled() const;
	
	void initTremelo(juce::AudioProcessorValueTreeState::ParameterLayout& layout);
	bool getTremeloEnabled() const;
	int getTremeloWaveform() const;
	float getTremeloRate() const;
	float getTremeloDepth() const;

	void initChorus(juce::AudioProcessorValueTreeState::ParameterLayout& layout);
	bool getChorusEnabled() const;

	void initPhaser(juce::AudioProcessorValueTreeState::ParameterLayout& layout);
	bool getPhaserEnabled() const;

	void initFlanger(juce::AudioProcessorValueTreeState::ParameterLayout& layout);
	bool getFlangerEnabled() const;

	JUCE_DECLARE_NON_COPYABLE(Parameters)
	JUCE_DECLARE_NON_MOVEABLE(Parameters)
};

#endif