#ifndef REVERBUIPARAMS_HPP
# define REVERBUIPARAMS_HPP

#include <juce_gui_basics/juce_gui_basics.h>

class ReverbUIParams : public juce::Component
{
private:
public:
	ReverbUIParams();
	~ReverbUIParams() override;

	void paint (juce::Graphics&) override;
    void resized() override;
};



#endif