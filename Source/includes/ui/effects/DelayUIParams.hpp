#ifndef DELAYUIPARAMS_HPP
# define DELAYUIPARAMS_HPP

#include <juce_gui_basics/juce_gui_basics.h>

class DelayUIParams : public juce::Component
{
private:
public:
	DelayUIParams();
	~DelayUIParams() override;

	void paint (juce::Graphics&) override;
    void resized() override;
};



#endif