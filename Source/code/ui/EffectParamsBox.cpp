#include "../../includes/ui/EffectParamsBox.hpp"

EffectParamsBox::EffectParamsBox() : selectedEffect(nullptr)
{
}

EffectParamsBox::~EffectParamsBox()
{
    if (selectedEffect != nullptr)
    {
        removeChildComponent(this->selectedEffect.get());
        this->selectedEffect = nullptr;
    }
}


void EffectParamsBox::paint(juce::Graphics& g) {
    g.setColour(juce::Colours::red);
    g.drawRect(getLocalBounds().toFloat(), 2.0f);
}

void EffectParamsBox::resized() {
    if (this->selectedEffect != nullptr)
        this->selectedEffect->setBounds(getLocalBounds());
}

void EffectParamsBox::setSelectedEffect(std::unique_ptr<juce::Component> newEffect) {
    if (this->selectedEffect != nullptr)
        removeChildComponent(this->selectedEffect.get());

    this->selectedEffect = std::move(newEffect);

    if (this->selectedEffect != nullptr)
    {
        addAndMakeVisible(this->selectedEffect.get());
        resized();
    }
}