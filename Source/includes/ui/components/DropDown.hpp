#ifndef DROPDOWN_HPP
# define DROPDOWN_HPP

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>

class AudioPluginAudioProcessor;

class DropDown : public juce::Component
{
private:
    class CustomLookAndFeel : public juce::LookAndFeel_V4
    {
    public:
        void setFontSize(float size) { fontSize = size; }

        juce::Font getComboBoxFont(juce::ComboBox&) override
        {
            return juce::Font(fontSize);
        }

    private:
        float fontSize = 14.0f;
    };

    juce::ComboBox box;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> attachment;
    CustomLookAndFeel customLookAndFeel;

public:
    explicit DropDown(const juce::String& name,
                      const juce::StringArray& options,
                      AudioPluginAudioProcessor& p);

    ~DropDown() override;

    void resized() override;

    void setComboboxFont(float fontSize);
};

#endif
