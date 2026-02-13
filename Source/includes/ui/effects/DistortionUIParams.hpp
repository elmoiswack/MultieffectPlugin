#ifndef DISTORTIONUIPARAMS_HPP
# define DISTORTIONUIPARAMS_HPP

#include <juce_gui_basics/juce_gui_basics.h>

class DistortionUIParams : public juce::Component
{
private:
public:
	DistortionUIParams();
	~DistortionUIParams() override;

	void paint (juce::Graphics&) override;
    void resized() override;
};

#endif