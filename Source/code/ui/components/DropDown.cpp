#include "../../../includes/ui/components/DropDown.hpp"
#include "../../../includes/dsp/PluginProcessor.h"

DropDown::DropDown(const juce::String& name, const juce::StringArray& options, AudioPluginAudioProcessor& p) : box{name}
{
	addAndMakeVisible(box);
	this->box.setEditableText(false);
	this->box.addItemList(options, 1);

    this->customLookAndFeel.setColour(juce::ComboBox::textColourId, juce::Colours::red);
    this->customLookAndFeel.setColour(juce::ComboBox::backgroundColourId, juce::Colours::black);
    this->customLookAndFeel.setColour(juce::ComboBox::outlineColourId, juce::Colours::red);
    this->customLookAndFeel.setColour(juce::ComboBox::buttonColourId, juce::Colours::red);
    this->customLookAndFeel.setColour(juce::ComboBox::arrowColourId, juce::Colours::red);
    this->customLookAndFeel.setColour(juce::ComboBox::focusedOutlineColourId, juce::Colours::red);
    
    this->customLookAndFeel.setColour(juce::PopupMenu::textColourId, juce::Colours::red);
    this->customLookAndFeel.setColour(juce::PopupMenu::backgroundColourId, juce::Colours::black);
    this->customLookAndFeel.setColour(juce::PopupMenu::highlightedTextColourId, juce::Colours::red);
    this->customLookAndFeel.setColour(juce::PopupMenu::highlightedBackgroundColourId, juce::Colours::darkgrey);
    
	this->setLookAndFeel(&this->customLookAndFeel);
	this->box.setSelectedItemIndex(0);

    this->attachement = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(
        p.getApvts(),
        name,
        this->box
    );
}

DropDown::~DropDown()
{
	box.setLookAndFeel(nullptr);
}

void DropDown::resized() {
	this->box.setBounds(getLocalBounds());
}
