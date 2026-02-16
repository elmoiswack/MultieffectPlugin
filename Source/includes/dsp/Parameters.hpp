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

	//juce::AudioParameterFloat& outputGain;
	//juce::AudioParameterBool& outputBypass;

	//juce::AudioParameterBool& tremeloBypass;
	//juce::AudioParameterFloat& tremeloRate;
	//juce::AudioParameterFloat& tremeloDepth;
	//juce::AudioParameterChoice& tremeloWaveform;
public:
	explicit Parameters(juce::AudioProcessor& processorRef);
	~Parameters();

	//juce::AudioParameterBool& initAudioParameterBool(
	//	juce::AudioProcessor& processorRef,
	//	const std::string& paramId,
	//	int versionHint,
	//	const std::string& name,
	//	bool defaultValue
	//);

	//juce::AudioParameterChoice& initAudioParameterChoice(
	//	juce::AudioProcessor& processorRef,
	//	const std::string& paramId,
	//	int versionHint,
	//	const std::string& name,
	//	const juce::StringArray& choices,
	//	int defaultValue
	//);

	//juce::AudioParameterFloat& initAudioParameterFloat(
	//	juce::AudioProcessor& processorRef,
	//	const std::string& paramId,
	//	int versionHint,
	//	const std::string& name,
	//	juce::NormalisableRange<float> range,
	//	float defaultValue,
	//	const std::string& label
	//);

	juce::AudioProcessorValueTreeState::ParameterLayout initApvts();

	juce::AudioProcessorValueTreeState& getApvts();


	//juce::AudioParameterFloat& createOutputGain(juce::AudioProcessor& processorRef);
	//juce::AudioParameterBool& createOutputBypass(juce::AudioProcessor& processorRef);
	float getOutputGaindB() const;
	bool getOutputBypass() const;

	//juce::AudioParameterBool& createTremeloBypass(juce::AudioProcessor& processorRef);
	//juce::AudioParameterFloat& createTremeloRate(juce::AudioProcessor& processorRef);
	//juce::AudioParameterFloat& createTremeloDepth(juce::AudioProcessor& processorRef);
	//juce::AudioParameterChoice& createTremeloWaveform(juce::AudioProcessor& processorRef);
	bool getTremeloBypass() const;
	int getTremeloWaveform() const;
	float getTremeloRate() const;
	float getTremeloDepth() const;

	JUCE_DECLARE_NON_COPYABLE(Parameters)
	JUCE_DECLARE_NON_MOVEABLE(Parameters)
};

#endif