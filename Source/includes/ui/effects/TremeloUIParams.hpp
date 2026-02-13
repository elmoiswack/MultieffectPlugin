#ifndef TREMELOUIPARAMS_HPP
# define TREMELOUIPARAMS_HPP

#include <juce_gui_basics/juce_gui_basics.h>

class TremeloUIParams : public juce::Component
{
private:
public:
	TremeloUIParams();
	~TremeloUIParams() override;

	void paint (juce::Graphics&) override;
    void resized() override;
};



#endif