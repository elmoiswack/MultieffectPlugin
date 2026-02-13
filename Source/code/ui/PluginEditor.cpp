#include "../../includes/ui/PluginEditor.h"
#include "../../includes/dsp/PluginProcessor.h"
#include <BinaryData.h>

void AudioPluginAudioProcessorEditor::selectEffect(size_t index)
{
    for (size_t i = 0; i < this->effectBoxes.size(); ++i)
        this->effectBoxes[i]->setSelected(i == index);

    switch (static_cast<EffectTypes>(index)) {
        case REVERB:
            this->effectParamsBox->setSelectedEffect(std::make_unique<ReverbUIParams>());
            break;
        case DISTORTION:
            this->effectParamsBox->setSelectedEffect(std::make_unique<DistortionUIParams>());
            break;
        case DELAY:
            this->effectParamsBox->setSelectedEffect(std::make_unique<DelayUIParams>());
            break;
        case TREMELO:
            this->effectParamsBox->setSelectedEffect(std::make_unique<TremeloUIParams>());
            break;
        case CHORUS:
            this->effectParamsBox->setSelectedEffect(std::make_unique<ChorusUIParams>());
            break;
        case PHASER:
            this->effectParamsBox->setSelectedEffect(std::make_unique<PhaserUIParams>());
            break;
        case FLANGER:
            this->effectParamsBox->setSelectedEffect(std::make_unique<FlangerUIParams>());
            break;
        default:
            this->effectParamsBox->setSelectedEffect(nullptr);
            break;
    }
}

//============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    juce::ignoreUnused (processorRef);

	this->backgroundImage = juce::ImageCache::getFromMemory(
        BinaryData::elmoonfire_png,
        BinaryData::elmoonfire_pngSize
    );
    this->powerButtonImage = juce::ImageCache::getFromMemory(
        BinaryData::powerbutton_png,
        BinaryData::powerbutton_pngSize
    );


    for (std::size_t i = 0; i < this->effects.size(); i++) {
        auto effect = std::make_unique<EffectBox>(this->effects[i], powerButtonImage);
        effect->onClicked = [this, i](void) {
            this->selectEffect(i);
        };
        addAndMakeVisible(*effect);
        this->effectBoxes.push_back(std::move(effect));
    }
    this->effectParamsBox = std::make_unique<EffectParamsBox>();
    addAndMakeVisible(*this->effectParamsBox);

    this->pluginParamsBox = std::make_unique<PluginParamsBox>();
    addAndMakeVisible(*this->pluginParamsBox);

    this->RMSButton.setButtonText("RMS");
    this->RMSButton.setClickingTogglesState(true);
    this->RMSButton.setColour(juce::TextButton::buttonColourId, juce::Colours::red);
    this->RMSButton.setColour(juce::TextButton::buttonOnColourId, juce::Colours::green);
    addAndMakeVisible(this->RMSButton);
    this->RMSButton.onClick = [this]() {
        this->processorRef.useRMS = this->RMSButton.getToggleState();
    };


    this->setGraphType(AudioGraphTypes::WAVEFORM);
    this->graphButton.setButtonText("Waveform");
    this->graphButton.onClick = [this] {
        if (this->currentGraphType == AudioGraphTypes::WAVEFORM) {
            this->setGraphType(AudioGraphTypes::OSCILLOSCOPE);
            this->graphButton.setButtonText("Oscilloscope");
        } else {
            this->setGraphType(AudioGraphTypes::WAVEFORM);
            this->graphButton.setButtonText("Waveform");
        }
    };
    addAndMakeVisible(this->graphButton);

    setSize (1250, 750);
    resized();
	startTimerHz(60);
}


AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor() {}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);

    int w = getWidth() / 4;
    int h = getHeight() / 4;

    if (backgroundImage.isValid())
    {
        g.drawImage(
            backgroundImage,
            juce::Rectangle<float>(w + (w / 2), h + (h / 2), (float)w, (float)h),
            juce::RectanglePlacement::stretchToFit
        );
    }
}

void AudioPluginAudioProcessorEditor::resized()
{
    auto height = getHeight();
    auto width = getWidth();
    this->graph->setBounds(width / 4, 10, width / 2, 60);

    int buttonY = 80;
    int buttonWidth = 100;
    int buttonHeight = 30;
    
    this->graphButton.setBounds(width / 4, buttonY, buttonWidth, buttonHeight);

    this->RMSButton.setBounds(width / 4 + buttonWidth, buttonY, buttonWidth, buttonHeight);

    auto xOffset = width / 32;
    auto widthBox = (width / 4) - 25;
    auto heightBox = height / 16;
    auto yOffset = 15;
    auto beginHeight = (height / 4) - heightBox;

    std::size_t n = this->effectBoxes.size();
    int y = beginHeight;
    for (auto& effectBox : this->effectBoxes) {
        effectBox->setBounds(xOffset, y, widthBox, heightBox);
        y += heightBox + yOffset;
    }
    
    int totalHeight = n * heightBox + (n - 1) * yOffset;
    this->effectParamsBox->setBounds(
        width - (xOffset + widthBox),
        beginHeight,
        widthBox,
        totalHeight
    );

    this->pluginParamsBox->setBounds(
        xOffset,
        y,
        width - (xOffset * 2),
        heightBox * 2
    );
}

void AudioPluginAudioProcessorEditor::setGraphType(AudioGraphTypes type)
{
    this->graph.reset();

    if (type == AudioGraphTypes::WAVEFORM)
        this->graph = std::make_unique<WaveformGraph>();
    else
        this->graph = std::make_unique<OscilloGraph>();

    this->currentGraphType = type;
    addAndMakeVisible(*this->graph);
    resized();
}

void AudioPluginAudioProcessorEditor::timerCallback()
{
    juce::AudioBuffer<float> outputBuffer;
    int numSamplesToShow = (this->currentGraphType == AudioGraphTypes::WAVEFORM) ? this->processorRef.getHistoryBufferSize() : 1024;

    this->processorRef.getBufferForGraph(outputBuffer, numSamplesToShow, this->currentGraphType);
    this->graph->setBuffer(outputBuffer);
}
