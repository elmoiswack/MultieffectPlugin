#include "../../includes/ui/PluginParamsBox.hpp"
#include "../../includes/dsp/PluginProcessor.h"

PluginParamsBox::PluginParamsBox(AudioPluginAudioProcessor& p) : 
    gain("output.gain", p),
    lowcutFreq("output.lowcut.frequency", p),
    lowcutSlope("output.lowcut.slope", juce::StringArray("12 dB/Oct", "24 dB/Oct", "36 dB/Oct", "48 dB/Oct"), p),
    midFreq("output.mid.frequency", p),
    midGain("output.mid.gain", p),
    midQuality("output.mid.quality", p),
    highcutFreq("output.highcut.frequency", p),
    highcutSlope("output.highcut.slope", juce::StringArray("12 dB/Oct", "24 dB/Oct", "36 dB/Oct", "48 dB/Oct"), p),
    volume("output.volume", p)
{
    addAndMakeVisible(this->gain);
    this->gain.setAlpha(1.0f);
    this->gain.setEnabled(true);
    this->gain.setCostomTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 60, 20, " dB");
    addAndMakeVisible(this->volume);
    this->volume.setAlpha(1.0f);
    this->volume.setEnabled(true);
    this->volume.setCostomTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 60, 20, " dB");
  
    addAndMakeVisible(this->lowcutFreq);
    this->lowcutFreq.setAlpha(1.0f);
    this->lowcutFreq.setEnabled(true);
    this->lowcutFreq.setCostomTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 60, 20, " Hz");
    addAndMakeVisible(this->lowcutSlope);
    this->lowcutSlope.setComboboxFont(15);

    addAndMakeVisible(this->midFreq);
    this->midFreq.setAlpha(1.0f);
    this->midFreq.setEnabled(true);
    this->midFreq.setCostomTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 60, 20, " Hz");
    addAndMakeVisible(this->midGain);
    this->midGain.setAlpha(1.0f);
    this->midGain.setEnabled(true);
    this->midGain.setCostomTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 60, 20, " dB");
    addAndMakeVisible(this->midQuality);
    this->midQuality.setAlpha(1.0f);
    this->midQuality.setEnabled(true);
    this->midQuality.setCostomTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 60, 20, " Hz");

    addAndMakeVisible(this->highcutFreq);
    this->highcutFreq.setAlpha(1.0f);
    this->highcutFreq.setEnabled(true);
    this->highcutFreq.setCostomTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 60, 20, " Hz");
    addAndMakeVisible(this->highcutSlope);
    this->highcutSlope.setComboboxFont(15);
}

PluginParamsBox::~PluginParamsBox()
{
}

void PluginParamsBox::paint(juce::Graphics& g) {
    g.setColour(juce::Colours::red);
    g.drawRect(getLocalBounds().toFloat(), 2.0f);

    int textHeight = 20;
    int textWidth = 85;
    g.setColour(juce::Colours::white);
    g.setFont(18);

    auto boundsGain = this->gain.getBounds().toFloat();
    auto x = boundsGain.getX();
    auto y = boundsGain.getY();
    g.drawText("Gain", juce::Rectangle<float>(x, y - textHeight, textWidth, textHeight), juce::Justification::centred, false);
    
    auto boundsVolume = this->volume.getBounds().toFloat();
    x = boundsVolume.getX();
    g.drawText("Volume", juce::Rectangle<float>(x, y - textHeight, textWidth, textHeight), juce::Justification::centred, false);

    x = (getLocalBounds().getCentreX() / 2) + ((getLocalBounds().getCentreX() / 16));
    g.drawText("Lowcut", juce::Rectangle<float>(x, y - textHeight, textWidth, textHeight), juce::Justification::centred, false);

    x = getLocalBounds().getCentreX() - (textWidth / 2);
    g.drawText("Mid", juce::Rectangle<float>(x, y - textHeight, textWidth, textHeight), juce::Justification::centred, false);

    auto boundsHighCut = this->highcutFreq.getBounds().toFloat();
    x = (getLocalBounds().getCentreX() + (getLocalBounds().getCentreX() / 4)) + ((getLocalBounds().getCentreX() / 16));
    g.drawText("Highcut", juce::Rectangle<float>(x, y - textHeight, textWidth, textHeight), juce::Justification::centred, false);


    auto boundsLowCutSlope = this->lowcutSlope.getBounds();
    auto boundsLowCutFreq = this->lowcutFreq.getBounds().toFloat();
    auto boundsMidGain = this->midGain.getBounds().toFloat();
    auto boundsMidFreq = this->midFreq.getBounds().toFloat();
    textHeight = 30;
    textWidth -= 10;
    g.setFont(15);

    x = (boundsLowCutSlope.getX()) + 5;
    y = boundsLowCutSlope.getY() - textHeight;
    g.drawText("Slope", juce::Rectangle<float>(x,  y, textWidth, textHeight), juce::Justification::centred, false);

    x = (boundsLowCutFreq.getX());
    g.drawText("Frequency", juce::Rectangle<float>(x,  y, textWidth, textHeight), juce::Justification::centred, false);
 
}

void PluginParamsBox::resized() {
    int width = getLocalBounds().getWidth();
    int height = getLocalBounds().getHeight();
    int centerX = getLocalBounds().getCentreX();
    int centerY = getLocalBounds().getCentreY();
    int yOffset = 10;
    int yOffsetSlope = 2;
    int buttonHeight = 85;
    int buttonWidht = 85;
    int slopeHeight = 35;
    int yPos = centerY - (buttonHeight / 2) + yOffset;
    int yPosDrop = centerY - (slopeHeight / 2) - yOffsetSlope;
    
    this->gain.setBounds(
        buttonWidht / 2,
        yPos,
        buttonWidht,
        buttonHeight
    );

    this->volume.setBounds(
        buttonWidht + buttonWidht - 20,
        yPos,
        buttonWidht,
        buttonHeight
    );

    int sizeOffset = 10;
    yPos = centerY - (buttonHeight / 2) + yOffset + sizeOffset;
    yPosDrop = centerY - (slopeHeight / 2) - yOffsetSlope + sizeOffset;
    this->lowcutSlope.setBounds(
        (buttonWidht * 3.5) - 10,
        yPosDrop,
        buttonWidht,
        slopeHeight
    );
    this->lowcutFreq.setBounds(
        (buttonWidht * 4) + 30,
        yPos,
        buttonWidht - sizeOffset,
        buttonHeight - sizeOffset
    );


    this->midGain.setBounds(
        centerX - (buttonWidht / 2) - buttonWidht + (sizeOffset * 2),
        yPos,
        buttonWidht - sizeOffset,
        buttonHeight - sizeOffset
    );
    this->midFreq.setBounds(
        centerX - (buttonWidht / 2) + 6,
        yPos,
        buttonWidht - sizeOffset,
        buttonHeight - sizeOffset
    );
    this->midQuality.setBounds(
        centerX + (buttonWidht / 2) - 8,
        yPos,
        buttonWidht - sizeOffset,
        buttonHeight - sizeOffset
    );


    this->highcutFreq.setBounds(
        centerX + buttonWidht + buttonWidht + (buttonWidht / 4) - 27,
        yPos,
        buttonWidht - sizeOffset,
        buttonHeight - sizeOffset
    );
    this->highcutSlope.setBounds(
        centerX + buttonWidht + buttonWidht + (buttonWidht / 2) + 22,
        yPosDrop,
        buttonWidht,
        slopeHeight
    );

}
