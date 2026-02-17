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

//==============================================================================
//                              APVTS
juce::AudioProcessorValueTreeState::ParameterLayout Parameters::initApvts() {
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

   this->initOutput(layout);
   this->initTremelo(layout);


    return layout;
}

juce::AudioProcessorValueTreeState& Parameters::getApvts() {
    return this->apvts;
}

//==============================================================================
//                              OUTPUT
void Parameters::initOutput(juce::AudioProcessorValueTreeState::ParameterLayout& layout) {
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        "output.gain",
        "Output Gain",
        juce::NormalisableRange<float>(-24.0f, 24.0f, 0.5f, 1.f),
        0.0f
        ) //dB
    );
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        "output.lowcut",
        "Output LowCut",
        juce::NormalisableRange<float>(20.0f, 20000.0f, 1.f, 1.f),
        20.0f
        ) //Hz
    );
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        "output.mid",
        "Output Mid",
        juce::NormalisableRange<float>(20.0f, 20000.0f, 1.f, 1.f),
        750.0f
        ) //Hz
    );
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        "output.highcut",
        "Output HighCut",
        juce::NormalisableRange<float>(20.0f, 20000.0f, 1.f, 1.f),
        20000.0f
        ) //Hz
    );
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        "output.volume",
        "Output Volume",
        juce::NormalisableRange<float>(-12.0f, 12.0f, 0.1f),
        0.0f
        ) //dB
    );
    layout.add(std::make_unique<juce::AudioParameterBool>(
        "output.enabled",
        "Output Enabled",
        true
        ) //bool
    );
}

float Parameters::getOutputGaindB() const {
	return this->apvts.getRawParameterValue("output.gain")->load();
}

float Parameters::getOutputLowCutdB() const {
	return this->apvts.getRawParameterValue("output.lowcut")->load();
}

float Parameters::getOutputMiddB() const {
	return this->apvts.getRawParameterValue("output.mid")->load();
}

float Parameters::getOutputHighCutdB() const {
	return this->apvts.getRawParameterValue("output.highcut")->load();
}

float Parameters::getOutputVolumedB() const {
	return this->apvts.getRawParameterValue("output.volume")->load();
}

bool Parameters::getOutputEnabled() const {
    return this->apvts.getRawParameterValue("output.enabled")->load() > 0.5;
}

//==============================================================================
//                              REVERB
void Parameters::initReverb(juce::AudioProcessorValueTreeState::ParameterLayout& layout) {
    layout.add(std::make_unique<juce::AudioParameterBool>(
        "reverb.enabled",
        "Reverb Byapss",
        false
        ) //bool
    );
}

bool Parameters::getReverbEnabled() const {
    return this->apvts.getRawParameterValue("reverb.enabled")->load() > 0.5;
}

//==============================================================================
//                              DISTORTION
void Parameters::initDistortion(juce::AudioProcessorValueTreeState::ParameterLayout& layout) {
    layout.add(std::make_unique<juce::AudioParameterBool>(
        "distortion.enabled",
        "Distortion Byapss",
        true
        ) //bool
    );
}

bool Parameters::getDistortionEnabled() const {
    return this->apvts.getRawParameterValue("distortion.enabled")->load() > 0.5;
}

//==============================================================================
//                              DELAY
void Parameters::initDelay(juce::AudioProcessorValueTreeState::ParameterLayout& layout) {
    layout.add(std::make_unique<juce::AudioParameterBool>(
        "delay.enabled",
        "Delay Byapss",
        false
        ) //bool
    );
}

bool Parameters::getDelayEnabled() const {
    return this->apvts.getRawParameterValue("delay.enabled")->load() > 0.5;
}

//==============================================================================
//                              TREMELO
void Parameters::initTremelo(juce::AudioProcessorValueTreeState::ParameterLayout& layout) {
    layout.add(std::make_unique<juce::AudioParameterBool>(
        "tremelo.enabled",
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
}

bool Parameters::getTremeloEnabled() const {
    return this->apvts.getRawParameterValue("tremelo.enabled")->load() > 0.5;
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

//==============================================================================
//                              CHORUS
void Parameters::initChorus(juce::AudioProcessorValueTreeState::ParameterLayout& layout) {
    layout.add(std::make_unique<juce::AudioParameterBool>(
        "chorus.enabled",
        "Chorus Byapss",
        false
        ) //bool
    );
}

bool Parameters::getChorusEnabled() const {
    return this->apvts.getRawParameterValue("chorus.enabled")->load() > 0.5;
}

//==============================================================================
//                              PHASER
void Parameters::initPhaser(juce::AudioProcessorValueTreeState::ParameterLayout& layout) {
    layout.add(std::make_unique<juce::AudioParameterBool>(
        "phaser.enabled",
        "Phaser Byapss",
        false
        ) //bool
    );
}

bool Parameters::getPhaserEnabled() const {
    return this->apvts.getRawParameterValue("phaser.enabled")->load() > 0.5;
}

//==============================================================================
//                              FLANGER
void Parameters::initFlanger(juce::AudioProcessorValueTreeState::ParameterLayout& layout) {
    layout.add(std::make_unique<juce::AudioParameterBool>(
        "flanger.enabled",
        "Flanger Byapss",
        false
        ) //bool
    );
}

bool Parameters::getFlangerEnabled() const {
    return this->apvts.getRawParameterValue("flanger.enabled")->load() > 0.5;
}