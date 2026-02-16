#ifndef PLUGINPARAMSBOX_HPP
# define PLUGINPARAMSBOX_HPP

#include <juce_gui_basics/juce_gui_basics.h>


class PluginParamsBox : public juce::Component
{
private:
	
public:
	PluginParamsBox();
	~PluginParamsBox() override;

	void paint (juce::Graphics&) override;
    void resized() override;
};


#endif