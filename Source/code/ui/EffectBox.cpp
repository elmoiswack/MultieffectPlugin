#include "../../includes/ui/EffectBox.hpp"

EffectBox::EffectBox(juce::String name, const juce::Image& powerButtonImage) : effectName(name)
{
    this->powerButton.setClickingTogglesState(true);
    this->powerButton.setToggleable(true);
    this->powerButton.setToggleState(false, juce::dontSendNotification);

    this->powerButton.setImages(
        false,   // resizeButtonNowToFitImage =false because of resized
        true,   // preserveProportions
        true,   // opacity
        powerButtonImage,  1.0f, juce::Colours::transparentBlack, // normal
        powerButtonImage,  1.0f, juce::Colours::transparentBlack, // over
        powerButtonImage,  1.0f, juce::Colours::transparentBlack  // down
    );
    
    this->isSelected = false;

	this->powerButton.setAlpha(0.4f);

    this->volumeKnob.setCostomTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);

	addAndMakeVisible(this->powerButton);
	addAndMakeVisible(this->volumeKnob);
    
	this->powerButton.onClick = [this]() {
		bool isOn = this->powerButton.getToggleState();

		this->powerButton.setAlpha(isOn ? 1.0f : 0.4f);
		this->volumeKnob.setAlpha(isOn ? 1.0f : 0.4f);
		this->volumeKnob.setEnabled(isOn);

		repaint();
	};
}

EffectBox::~EffectBox()
{
}


void EffectBox::paint(juce::Graphics& g) 
{
    auto localBoundsW = getLocalBounds().getWidth();
    auto localBoundsCenterY = getLocalBounds().getCentreY();
    auto localBoundsH = getLocalBounds().getHeight();
    auto x = (localBoundsW / 2) - (localBoundsW / 4) + (localBoundsW / 8);
    auto y = (localBoundsCenterY / 2) + (localBoundsCenterY / 4);
    auto w = (localBoundsW / 2) - (localBoundsW / 4);
    auto h =  (localBoundsH / 2) - (localBoundsH / 4);

    if (!this->powerButton.getToggleState())
        g.setColour(OFF);
    else if (this->isSelected)
        g.setColour(SELECTED);
    else
        g.setColour(ON);
    g.drawRect(getLocalBounds().toFloat(), 2.0f);

    g.setColour(juce::Colours::white.withAlpha(this->powerButton.getToggleState() ? 1.0f : 0.4f));
    g.drawText(this->effectName, juce::Rectangle<float>(x, y, w, h), juce::Justification::centred);

    auto sliderBounds = this->volumeKnob.getBounds().toFloat();
    juce::Rectangle<float> mixLabelBounds(
        sliderBounds.getX() - 30.0f,
        y,
        35.0f,
        15.0f
    );

    g.drawText("MIX:", mixLabelBounds, juce::Justification::centred);
}

void EffectBox::resized() {
    int sideMargin   = 10;
    int buttonSize   = 30;
    auto localBoundsCenterY = getLocalBounds().getCentreY();

    this->powerButton.setBounds(
        sideMargin,
        (localBoundsCenterY / 2) - (localBoundsCenterY / 8) - 1,
        buttonSize,
        buttonSize
    );

    this->volumeKnob.setBounds(
        getLocalBounds().getWidth() - sideMargin - buttonSize,
        localBoundsCenterY / 4,
        buttonSize + 10,
        buttonSize + 10
    );
}

const juce::String& EffectBox::getEffectName() const {
    return this->effectName;
}

void EffectBox::mouseUp(const juce::MouseEvent& event)
{
    if (this->getIsActive() && onClicked)
        onClicked();
}

void EffectBox::setSelected(bool shouldBeSelected)
{
    this->isSelected = shouldBeSelected;
    repaint();
}

bool EffectBox::getIsActive() const {
	return this->powerButton.getToggleState();
}

void EffectBox::setIsActive(bool newValue) {
	this->powerButton.setToggleState(newValue, juce::dontSendNotification);
	repaint();
}
