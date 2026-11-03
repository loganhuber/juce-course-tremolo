#pragma once

namespace tremolo {
class PluginEditor : public juce::AudioProcessorEditor {
public:
  explicit PluginEditor(PluginProcessor&);

  void resized() override;

private:
  juce::ImageComponent background;
  juce::ImageComponent logo;
  juce::ImageComponent logo2;
  juce::ImageComponent logo3;

  // RateSlider rateSlider;
  juce::Slider rateSlider;
  juce::SliderParameterAttachment rateAttachment;

  juce::ToggleButton bypasssButton{"BYPASEED"};
  juce::ButtonParameterAttachment bypassAttachment;
  

  juce::Slider curveWidthSlider;

  LfoVisualizer lfoVisualizer;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
}  // namespace tremolo
