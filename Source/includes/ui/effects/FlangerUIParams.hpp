#ifndef FLANGERUIPARAMS_HPP
# define FLANGERUIPARAMS_HPP

#include <juce_gui_basics/juce_gui_basics.h>

class FlangerUIParams : public juce::Component
{
private:
public:
	FlangerUIParams();
	~FlangerUIParams() override;

	void paint (juce::Graphics&) override;
    void resized() override;
};



#endif