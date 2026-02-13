#ifndef PHASERUIPARAMS_HPP
# define PHASERUIPARAMS_HPP

#include <juce_gui_basics/juce_gui_basics.h>

class PhaserUIParams : public juce::Component
{
private:
public:
	PhaserUIParams();
	~PhaserUIParams() override;

	void paint (juce::Graphics&) override;
    void resized() override;
};



#endif