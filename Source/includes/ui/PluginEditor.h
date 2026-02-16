#pragma once

#include "../dsp/PluginProcessor.h"
#include "EffectBox.hpp"
#include "EffectParamsBox.hpp"
#include "PluginParamsBox.hpp"
#include "AudioGraph.hpp"
#include "OscilloGraph.hpp"
#include "effects/ReverbUIParams.hpp"
#include "effects/DistortionUIParams.hpp"
#include "effects/DelayUIParams.hpp"
#include "effects/TremeloUIParams.hpp"
#include "effects/ChorusUIParams.hpp"
#include "effects/PhaserUIParams.hpp"
#include "effects/FlangerUIParams.hpp"

enum EffectTypes {
    REVERB,
    DISTORTION,
    DELAY,
    TREMELO,
    CHORUS,
    PHASER,
    FLANGER
};

//==============================================================================
class AudioPluginAudioProcessorEditor : public juce::AudioProcessorEditor, private juce::Timer
{
public:
    explicit AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor&);
    ~AudioPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void timerCallback() override;

    void selectEffect(size_t index);

private:
    juce::TextButton graphButton;
    std::unique_ptr<AudioGraph> graph;
    AudioGraphTypes currentGraphType;

    juce::Image backgroundImage;
    
    juce::Image powerButtonImage;
    std::vector<juce::String> effects { "Reverb", "Distortion", "Delay", "Tremelo", "Chorus", "Phaser", "Flanger"};
    std::vector<std::unique_ptr<EffectBox>> effectBoxes;
    std::unique_ptr<EffectParamsBox> effectParamsBox;
    std::unique_ptr<PluginParamsBox> pluginParamsBox;

    AudioPluginAudioProcessor& processorRef;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessorEditor)
};
