#ifndef AUDIOGRAPH_HPP
# define AUDIOGRAPH_HPP

#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_audio_basics/juce_audio_basics.h>

enum AudioGraphTypes {
	OSCILLOSCOPE,
	WAVEFORM,
};

class AudioGraph : public juce::Component
{
protected:
    virtual void drawGraph (juce::Graphics& g) = 0;
    juce::AudioBuffer<float> displayBuffer;

public:
	AudioGraph();
	~AudioGraph() override;

	void paint (juce::Graphics& g) override;
    void resized() override;

	virtual void setBuffer(const juce::AudioBuffer<float>& buffer);
	juce::AudioBuffer<float> getBuffer();
};

#endif