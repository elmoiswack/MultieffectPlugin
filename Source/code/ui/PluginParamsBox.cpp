#include "../../includes/ui/PluginParamsBox.hpp"
#include "../../includes/dsp/PluginProcessor.h"

PluginParamsBox::PluginParamsBox(AudioPluginAudioProcessor& p) : 
    gain("output.gain", p),
    lowcut("output.lowcut", p),
    mid("output.mid", p),
    highcut("output.highcut", p),
    volume("output.volume", p)
{
    addAndMakeVisible(gain);
    this->gain.setAlpha(1.0f);
    this->gain.setEnabled(true);
    this->gain.setCostomTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 60, 20, " dB");
    addAndMakeVisible(lowcut);
    this->lowcut.setAlpha(1.0f);
    this->lowcut.setEnabled(true);
    this->lowcut.setCostomTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 60, 20, " Hz");
    addAndMakeVisible(mid);
    this->mid.setAlpha(1.0f);
    this->mid.setEnabled(true);
    this->mid.setCostomTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 60, 20, " Hz");
    addAndMakeVisible(highcut);
    this->highcut.setAlpha(1.0f);
    this->highcut.setEnabled(true);
    this->highcut.setCostomTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 60, 20, " Hz");
    addAndMakeVisible(volume);
    this->volume.setAlpha(1.0f);
    this->volume.setEnabled(true);
    this->volume.setCostomTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 60, 20, " dB");
  
}

PluginParamsBox::~PluginParamsBox()
{
}

void PluginParamsBox::paint(juce::Graphics& g) {
    g.setColour(juce::Colours::red);
    g.drawRect(getLocalBounds().toFloat(), 2.0f);

    int textYOffset = 20;
    g.setColour(juce::Colours::white);
    g.setFont(18);

    auto boundsGain = this->gain.getBounds().toFloat();
    auto x = boundsGain.getX();
    auto y = boundsGain.getY();
    g.drawText("Gain", juce::Rectangle<float>(x, y - textYOffset, 85, textYOffset), juce::Justification::centred, false);

    auto boundsLowCut = this->lowcut.getBounds().toFloat();
    x = boundsLowCut.getX();
    y = boundsLowCut.getY();
    g.drawText("Lowcut", juce::Rectangle<float>(x, y - textYOffset, 85, textYOffset), juce::Justification::centred, false);

    auto boundsMid = this->mid.getBounds().toFloat();
    x = boundsMid.getX();
    y = boundsMid.getY();
    g.drawText("Mid", juce::Rectangle<float>(x, y - textYOffset, 85, textYOffset), juce::Justification::centred, false);

    auto boundsHighCut = this->highcut.getBounds().toFloat();
    x = boundsHighCut.getX();
    y = boundsHighCut.getY();
    g.drawText("Highcut", juce::Rectangle<float>(x, y - textYOffset, 85, textYOffset), juce::Justification::centred, false);

    auto boundsVolume = this->volume.getBounds().toFloat();
    x = boundsVolume.getX();
    y = boundsVolume.getY();
    g.drawText("Volume", juce::Rectangle<float>(x, y - textYOffset, 85, textYOffset), juce::Justification::centred, false);

}

void PluginParamsBox::resized() {
    int width = getLocalBounds().getWidth();
    int height = getLocalBounds().getHeight();
    int centerX = getLocalBounds().getCentreX();
    int centerY = getLocalBounds().getCentreY();
    int yOffset = 10;
    int buttonHeight = 85;
    int buttonWidht = 85;

    this->gain.setBounds(
        centerX - (buttonWidht * 2.5) - (buttonWidht),
        centerY - (buttonHeight / 2) + yOffset,
        buttonWidht,
        buttonHeight
    );

    this->lowcut.setBounds(
        centerX - (buttonWidht * 1.5) - (buttonWidht / 2),
        centerY - (buttonHeight / 2) + yOffset,
        buttonWidht,
        buttonHeight
    );

    this->mid.setBounds(
        centerX - (buttonWidht / 2),
        centerY - (buttonHeight / 2) + yOffset,
        buttonWidht,
        buttonHeight
    );

    this->highcut.setBounds(
        centerX + buttonWidht,
        centerY - (buttonHeight / 2) + yOffset,
        buttonWidht,
        buttonHeight
    );

    this->volume.setBounds(
        centerX + buttonWidht + (buttonWidht * 1.5),
        centerY - (buttonHeight / 2) + yOffset,
        buttonWidht,
        buttonHeight
    );
}
