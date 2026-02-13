#ifndef CHORUSUIPARAMS_HPP
# define CHORUSUIPARAMS_HPP

#include <juce_gui_basics/juce_gui_basics.h>

class ChorusUIParams : public juce::Component
{
private:
public:
	ChorusUIParams();
	~ChorusUIParams() override;

	void paint (juce::Graphics&) override;
    void resized() override;
};

#endif