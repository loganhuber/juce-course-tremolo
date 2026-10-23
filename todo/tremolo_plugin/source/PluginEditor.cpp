namespace tremolo {
PluginEditor::PluginEditor(PluginProcessor& p) : AudioProcessorEditor(&p) {
  background.setImage(juce::ImageCache::getFromMemory(
      assets::Background_png, assets::Background_pngSize));

  logo.setImage(
      juce::ImageCache::getFromMemory(assets::Logo_png, assets::Logo_pngSize));
    
  logo2.setImage(
      juce::ImageCache::getFromMemory(assets::Logo_png, assets::Logo_pngSize));

  logo3.setImage(
      juce::ImageCache::getFromMemory(assets::Logo_png, assets::Logo_pngSize));
    
      
    addAndMakeVisible(background);
    addAndMakeVisible(logo);
    addAndMakeVisible(logo2);
    addAndMakeVisible(logo3);
      
    rateSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    rateSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    rateSlider.setPopupDisplayEnabled(true, true, this);
    rateSlider.setRange(1, 30, 0.5f);
    rateSlider.onValueChange = [this] {
        DBG("Rate slider value: " << rateSlider.getValue());
    };
    rateSlider.setTextValueSuffix(" Hz");

    curveWidthSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    curveWidthSlider.setValue(lfoVisualizer.strokeWidth);
    curveWidthSlider.setRange(1.0f, 20.0f, .3f);

    curveWidthSlider.onValueChange = [this] {
        lfoVisualizer.strokeWidth = static_cast<float>(curveWidthSlider.getValue());
        lfoVisualizer.repaint();
    };


    addAndMakeVisible(rateSlider);
    addAndMakeVisible(lfoVisualizer);
    addAndMakeVisible(curveWidthSlider);

  // Make sure that before the constructor has finished, you've set the
  // editor's size to whatever you need it to be.
    setSize(540, 300);
}

void PluginEditor::resized() {
  const auto bounds = getLocalBounds();

  background.setBounds({0, 0, getWidth(), 270});

  logo.setBounds({16, 16, 105, 24});
  logo2.setBounds({200, 16, 105, 24});
  logo3.setBounds({419, 16, 105, 24});

  auto curveWidthSliderBounds = bounds;
  curveWidthSliderBounds.removeFromTop(270);
  curveWidthSlider.setBounds(curveWidthSliderBounds);

  auto rateSliderBounds = bounds;
  rateSliderBounds.removeFromBottom(150);
  rateSliderBounds.removeFromTop(40);
  rateSliderBounds.removeFromLeft(230);
  rateSliderBounds.removeFromRight(230);
  rateSlider.setBounds(rateSliderBounds);

  lfoVisualizer.setBounds({18, 148, 504, 92});
}
}  // namespace tremolo
