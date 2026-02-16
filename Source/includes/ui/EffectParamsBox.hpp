#ifndef EFFECTPARAMSBOX_HPP
# define EFFECTPARAMSBOX_HPP

#include <juce_gui_basics/juce_gui_basics.h>
#include "./components/TurnableKnob.hpp"


class EffectParamsBox : public juce::Component
{
private:
	std::unique_ptr<juce::Component> selectedEffect;
public:
	EffectParamsBox();
    ~EffectParamsBox() override;

	void paint (juce::Graphics& g) override;
    void resized() override;

	void setSelectedEffect(std::unique_ptr<juce::Component> newEffect);
};


#endif 