#ifndef AUDIOGRAPH_HPP
# define AUDIOGRAPH_HPP

#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_audio_basics/juce_audio_basics.h>
#include "../../dsp/AudioAnalyzer.hpp"

enum AudioGraphTypes {
	OSCILLOSCOPE,
	FREQUENCY,
};

class AudioGraph : public juce::Component
{
protected:
	AudioAnalyzer& analyzer;
	
    virtual void drawGraph (juce::Graphics& g) = 0;
	void paint (juce::Graphics& g) override;

public:
	AudioGraph(AudioAnalyzer& analyzer);
	~AudioGraph() override;
};

#endif