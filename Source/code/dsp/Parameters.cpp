#include "../../includes/dsp/Parameters.hpp"

Parameters::Parameters(juce::AudioProcessor& processorRef) : 
    apvts{processorRef, nullptr, "Parameters", initApvts()}
{
}

Parameters::~Parameters()
{
}

//// Float parameter (continuous values)
//std::make_unique<juce::AudioParameterFloat>("id", "Name", min, max, default);

//// Int parameter (discrete values)
//std::make_unique<juce::AudioParameterInt>("id", "Name", minInt, maxInt, defaultInt);

//// Bool parameter (on/off)
//std::make_unique<juce::AudioParameterBool>("id", "Name", defaultBool);

//// Choice parameter (dropdown)
//std::make_unique<juce::AudioParameterChoice>("id", "Name", choices, defaultIndex);

juce::AudioProcessorValueTreeState::ParameterLayout Parameters::initApvts() {
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        "output.gain",
        "Output Gain",
        juce::NormalisableRange<float>(-12.0f, 12.0f, 0.1f),
        0.0f
        ) //dB
    );
    layout.add(std::make_unique<juce::AudioParameterBool>(
        "output.bypass",
        "Output Bypass",
        false
        ) //bool
    );

    layout.add(std::make_unique<juce::AudioParameterBool>(
        "tremelo.bypass",
        "Tremelo Byapss",
        false
        ) //bool
    );
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        "tremelo.rate",
        "Tremelo Rate",
        juce::NormalisableRange<float>(0.1f, 20.0f, 0.01f, 0.3f),
        5.0f
        ) //Hz
    );
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        "tremelo.depth",
        "Tremelo Depth",
        juce::NormalisableRange<float>(0.1f, 20.0f, 0.01f, 0.3f),
        5.0f
        ) //Hz
    );
    layout.add(std::make_unique<juce::AudioParameterChoice>(
        "tremelo.waveform",
        "Tremelo Waveform",
        juce::StringArray("Sine", "Triangle", "Square", "Saw"),
        0
        ) //for enum WaveformTypes
    );

    return layout;
}

juce::AudioProcessorValueTreeState& Parameters::getApvts() {
    return this->apvts;
}

float Parameters::getOutputGaindB() const {
	return this->apvts.getRawParameterValue("output.gain")->load();
}

bool Parameters::getOutputBypass() const {
    return this->apvts.getRawParameterValue("output.bypass")->load() > 0.5;
}


bool Parameters::getTremeloBypass() const {
    return this->apvts.getRawParameterValue("tremelo.bypass")->load() > 0.5;
}

int Parameters::getTremeloWaveform() const {
    return static_cast<int>(this->apvts.getRawParameterValue("tremelo.waveform")->load());
}

float Parameters::getTremeloRate() const {
	return this->apvts.getRawParameterValue("tremelo.rate")->load();
}

float Parameters::getTremeloDepth() const {
	return this->apvts.getRawParameterValue("tremelo.depth")->load();
}
