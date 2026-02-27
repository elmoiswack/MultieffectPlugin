#include "../../includes/ui/PluginParamsBox.hpp"
#include "../../includes/dsp/PluginProcessor.h"

PluginParamsBox::PluginParamsBox(const juce::Image& powerButtonImage, AudioPluginAudioProcessor& p) : 
    gain("output.gain", p),
    lowcutFreq("output.lowcut.frequency", p),
    lowcutSlope("output.lowcut.slope", juce::StringArray("12 dB/Oct", "24 dB/Oct", "36 dB/Oct", "48 dB/Oct"), p),
    midFreq("output.mid.frequency", p),
    midGain("output.mid.gain", p),
    midQuality("output.mid.quality", p),
    highcutFreq("output.highcut.frequency", p),
    highcutSlope("output.highcut.slope", juce::StringArray("12 dB/Oct", "24 dB/Oct", "36 dB/Oct", "48 dB/Oct"), p),
    volume("output.volume", p),
    enableLowCut("output.lowcut.enabled", powerButtonImage, p),
    enableMids("output.mid.enabled", powerButtonImage, p),
    enableHighCut("output.highcut.enabled", powerButtonImage, p)
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
    this->lowcutFreq.setEnabled(false);
    this->lowcutFreq.setCostomTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 60, 20, " Hz");
    addAndMakeVisible(this->lowcutSlope);
    this->lowcutSlope.setEnabled(false);
    this->lowcutSlope.setComboboxFont(15);

    addAndMakeVisible(this->midFreq);
    this->midFreq.setEnabled(false);
    this->midFreq.setCostomTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 60, 20, " Hz");
    addAndMakeVisible(this->midGain);
    this->midGain.setEnabled(false);
    this->midGain.setCostomTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 60, 20, " dB");
    addAndMakeVisible(this->midQuality);
    this->midQuality.setEnabled(false);
    this->midQuality.setCostomTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 60, 20, " Hz");

    addAndMakeVisible(this->highcutFreq);
    this->highcutFreq.setEnabled(false);
    this->highcutFreq.setCostomTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 60, 20, " Hz");
    addAndMakeVisible(this->highcutSlope);
    this->highcutSlope.setEnabled(false);
    this->highcutSlope.setComboboxFont(15);

    addAndMakeVisible(this->enableLowCut);
    addAndMakeVisible(this->enableMids);
    addAndMakeVisible(this->enableHighCut);
    this->enableLowCut.onClicked = [this]() { repaint(); };
    this->enableMids.onClicked = [this]() { repaint(); };
    this->enableHighCut.onClicked = [this]() { repaint(); };
}

PluginParamsBox::~PluginParamsBox()
{
}

void PluginParamsBox::paint(juce::Graphics& g) {
    g.setColour(juce::Colours::red);
    g.drawRect(getLocalBounds().toFloat(), 2.0f);

    this->lowcutFreq.setEnabled(this->enableLowCut.getSate());
    this->lowcutFreq.setAlpha(this->enableLowCut.getSate() ? 1.0f : 0.4f);
    this->lowcutSlope.setEnabled(this->enableLowCut.getSate());
    this->midGain.setEnabled(this->enableMids.getSate());
    this->midGain.setAlpha(this->enableMids.getSate() ? 1.0f : 0.4f);
    this->midFreq.setEnabled(this->enableMids.getSate());
    this->midFreq.setAlpha(this->enableMids.getSate() ? 1.0f : 0.4f);
    this->midQuality.setEnabled(this->enableMids.getSate());
    this->midQuality.setAlpha(this->enableMids.getSate() ? 1.0f : 0.4f);
    this->highcutFreq.setEnabled(this->enableHighCut.getSate());
    this->highcutFreq.setAlpha(this->enableHighCut.getSate() ? 1.0f : 0.4f);
    this->highcutSlope.setEnabled(this->enableHighCut.getSate());

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

    g.setColour(juce::Colours::white.withAlpha(this->enableLowCut.getSate() ? 1.0f : 0.4f));
    x = (getLocalBounds().getCentreX() / 2) + ((getLocalBounds().getCentreX() / 16));
    g.drawText("Lowcut", juce::Rectangle<float>(x, y - textHeight, textWidth, textHeight), juce::Justification::centred, false);

    g.setColour(juce::Colours::white.withAlpha(this->enableMids.getSate() ? 1.0f : 0.4f));
    x = getLocalBounds().getCentreX() - (textWidth / 2);
    g.drawText("Mid", juce::Rectangle<float>(x, y - textHeight, textWidth, textHeight), juce::Justification::centred, false);

    g.setColour(juce::Colours::white.withAlpha(this->enableHighCut.getSate() ? 1.0f : 0.4f));
    x = (getLocalBounds().getCentreX() + (getLocalBounds().getCentreX() / 4)) + ((getLocalBounds().getCentreX() / 16));
    g.drawText("Highcut", juce::Rectangle<float>(x, y - textHeight, textWidth, textHeight), juce::Justification::centred, false);

    g.setColour(juce::Colours::white.withAlpha(1.0f));
    x = getWidth() - (getWidth() / 8) - (textWidth / 2);
    g.drawText("Enable", juce::Rectangle<float>(x, y - textHeight, textWidth, textHeight), juce::Justification::centred, false);

    textHeight = 33;
    textWidth -= 10;
    g.setFont(13);

    g.setColour(juce::Colours::white.withAlpha(this->enableLowCut.getSate() ? 1.0f : 0.4f));
    auto boundsLowCutSlope = this->lowcutSlope.getBounds().toFloat();
    auto boundsLowCutFreq = this->lowcutFreq.getBounds().toFloat();
    y = boundsLowCutSlope.getY() - textHeight;
    g.drawText("Slope", juce::Rectangle<float>(boundsLowCutSlope.getX() + 5, y, textWidth, textHeight), juce::Justification::centred, false);
    g.drawText("Frequency", juce::Rectangle<float>(boundsLowCutFreq.getX(), y, textWidth, textHeight), juce::Justification::centred, false);

    g.setColour(juce::Colours::white.withAlpha(this->enableMids.getSate() ? 1.0f : 0.4f));
    auto boundsMidGain = this->midGain.getBounds().toFloat();
    auto boundsMidFreq = this->midFreq.getBounds().toFloat();
    auto boundsMidQuality = this->midQuality.getBounds().toFloat();
    g.drawText("Gain", juce::Rectangle<float>(boundsMidGain.getX(), y, textWidth, textHeight), juce::Justification::centred, false);
    g.drawText("Frequency", juce::Rectangle<float>(boundsMidFreq.getX(), y, textWidth, textHeight), juce::Justification::centred, false);
    g.drawText("Quality", juce::Rectangle<float>(boundsMidQuality.getX(), y, textWidth, textHeight), juce::Justification::centred, false);

    g.setColour(juce::Colours::white.withAlpha(this->enableHighCut.getSate() ? 1.0f : 0.4f));
    auto boundsHighCutFreq = this->highcutFreq.getBounds().toFloat();
    auto boundsHighCutSlope = this->highcutSlope.getBounds().toFloat();
    g.drawText("Frequency", juce::Rectangle<float>(boundsHighCutFreq.getX(), y, textWidth, textHeight), juce::Justification::centred, false);
    g.drawText("Slope", juce::Rectangle<float>(boundsHighCutSlope.getX() + 5, y, textWidth, textHeight), juce::Justification::centred, false);

    g.setColour(juce::Colours::white.withAlpha(1.0f));
    auto boundsEnableLow = this->enableLowCut.getBounds().toFloat();
    auto boundsEnableMid = this->enableMids.getBounds().toFloat();
    auto boundsEnableHigh = this->enableHighCut.getBounds().toFloat();
    g.drawText("LowCut", juce::Rectangle<float>(boundsEnableLow.getX() - (textWidth / 4), y, textWidth, textHeight), juce::Justification::centred, false);
    g.drawText("Mids", juce::Rectangle<float>(boundsEnableMid.getX()  - (textWidth / 4), y, textWidth, textHeight), juce::Justification::centred, false);
    g.drawText("HighCut", juce::Rectangle<float>(boundsEnableHigh.getX()  - (textWidth / 4), y, textWidth, textHeight), juce::Justification::centred, false);

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


    this->enableLowCut.setBounds(
        width - (buttonWidht * 2) - (buttonWidht / 2),
        yPosDrop,
        30,
        30
    );
    this->enableMids.setBounds(
        width - (buttonWidht * 2) + (buttonWidht / 8),
        yPosDrop,
        30,
        30
    );
    this->enableHighCut.setBounds(
        width - (buttonWidht * 2) + (buttonWidht / 4) + (buttonWidht / 2),
        yPosDrop,
        30,
        30
    );

}
