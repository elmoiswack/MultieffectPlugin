#include "../../includes/dsp/Parameters.hpp"

Parameters::Parameters(juce::AudioProcessor& processorRef) : 
	outputGain{createOutputGain(processorRef)},
    outputBypass{createOutputBypass(processorRef)},
    tremeloBypass{createTremeloBypass(processorRef)},
	tremeloRate{createTremeloRate(processorRef)},
	tremeloDepth{createTremeloDepth(processorRef)},
    tremeloWaveform{createTremeloWaveform(processorRef)}
{
}

Parameters::~Parameters()
{
}

juce::AudioParameterBool& Parameters::initAudioParameterBool(
	juce::AudioProcessor& processorRef,
	const std::string& paramId,
	int versionHint,
	const std::string& name,
	bool defaultValue
) {
    auto parameter = std::make_unique<juce::AudioParameterBool>(
        juce::ParameterID{ paramId, versionHint },
        name,
        defaultValue
    );

    auto& paramRef = *parameter;
    processorRef.addParameter(parameter.release());
    return paramRef;
}

juce::AudioParameterChoice& Parameters::initAudioParameterChoice(
	juce::AudioProcessor& processorRef,
	const std::string& paramId,
	int versionHint,
	const std::string& name,
	const juce::StringArray& choices,
	int defaultValue
) {
    auto parameter = std::make_unique<juce::AudioParameterChoice>(
        juce::ParameterID{ paramId, versionHint },
        name,
        choices,
        defaultValue
    );

    auto& paramRef = *parameter;
    processorRef.addParameter(parameter.release());
    return paramRef;
}

juce::AudioParameterFloat& Parameters::initAudioParameterFloat(
    juce::AudioProcessor& processorRef,
    const std::string& paramId,
    int versionHint,
    const std::string& name,
    juce::NormalisableRange<float> range,
    float defaultValue,
    const std::string& label
) {
    auto parameter = std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ paramId, versionHint },
        name,
        range,
        defaultValue,
        juce::AudioParameterFloatAttributes{}.withLabel(label)
    );

    auto& paramRef = *parameter;
    processorRef.addParameter(parameter.release());
    return paramRef;
}

juce::AudioParameterFloat& Parameters::createOutputGain(juce::AudioProcessor& processorRef) {
    return initAudioParameterFloat(
        processorRef,
        "output.gain",
        1,
        "Output Gain",
        { -12.0f, 12.0f, 0.1f, 0.4f },
        0.0f,
        "dB"
    );
}

juce::AudioParameterBool& Parameters::createOutputBypass(juce::AudioProcessor& processorRef) {
    return initAudioParameterBool(
        processorRef,
        "output.bypass",
        1,
        "Output Bypass",
        false
    );
}

float Parameters::getOutputGaindB() const {
	return this->outputGain.get();
}

juce::AudioParameterBool& Parameters::getOutputBypass() const {
    return this->outputBypass;
}

juce::AudioParameterBool& Parameters::createTremeloBypass(juce::AudioProcessor& processorRef) {
    return initAudioParameterBool(
        processorRef,
        "tremelo.bypass",
        1,
        "Tremelo Bypass",
        false
    );
}

juce::AudioParameterFloat& Parameters::createTremeloRate(juce::AudioProcessor& processorRef) {
	return initAudioParameterFloat(
        processorRef,
        "tremelo.rate",
		1,
        "Tremelo Rate",
        { 0.1f, 20.0f, 0.01f, 0.4f },
        5.0f,
        "Hz"
    );
}

juce::AudioParameterFloat& Parameters::createTremeloDepth(juce::AudioProcessor& processorRef) {
    return initAudioParameterFloat(
        processorRef,
        "tremelo.depth",
        1,
        "Tremelo Depth",
        { 0.1f, 20.0f, 0.01f, 0.4f },
        5.0f,
        "Hz"
    );
}

juce::AudioParameterChoice& Parameters::createTremeloWaveform(juce::AudioProcessor& processorRef) {
    return initAudioParameterChoice(
        processorRef,
        "tremelo.waveform",
        1,
        "Tremelo Waveform",
        {"Sine", "Triangle", "Square", "Saw"},
        0
    );
}

bool Parameters::getTremeloBypass() const {
    return this->tremeloBypass.get();
}

int Parameters::getTremeloWaveform() const {
    return this->tremeloWaveform.getIndex();
}

float Parameters::getTremeloRate() const {
	return this->tremeloRate.get();
}

float Parameters::getTremeloDepth() const {
	return this->tremeloDepth.get();
}