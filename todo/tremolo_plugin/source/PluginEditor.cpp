namespace tremolo {
PluginEditor::PluginEditor(PluginProcessor& p) : AudioProcessorEditor(&p), 
waveformAttachment{p.getParameterRefs().waveform, waveformComboBox},
rateAttachment{p.getParameterRefs().rate, rateSlider}, 
bypassAttachment{p.getParameterRefs().bypassed, bypasssButton} {

  background.setImage(juce::ImageCache::getFromMemory(
      assets::Background_png, assets::Background_pngSize));

  logo.setImage(
      juce::ImageCache::getFromMemory(assets::Logo_png, assets::Logo_pngSize));
    
      
    addAndMakeVisible(background);
    addAndMakeVisible(logo);
    
      
    rateSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    rateSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    rateSlider.setPopupDisplayEnabled(true, true, this);

    rateSlider.setTextValueSuffix(" Hz");

    curveWidthSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    curveWidthSlider.setValue(lfoVisualizer.strokeWidth);
    curveWidthSlider.setRange(1.0f, 20.0f, .3f);

    curveWidthSlider.onValueChange = [this] {
        lfoVisualizer.strokeWidth = static_cast<float>(curveWidthSlider.getValue());
        lfoVisualizer.repaint();
    };

    bypasssButton.onClick = [this] {
        bypasssButton.setButtonText(bypasssButton.getToggleState() ? "Bypassed" : "Off");
    };
    bypasssButton.onClick();

    waveformComboBox.addItemList(p.getParameterRefs().waveform.choices, 1);
    waveformAttachment.sendInitialUpdate();

    addAndMakeVisible(rateSlider);
    addAndMakeVisible(waveformComboBox);
    addAndMakeVisible(lfoVisualizer);
    addAndMakeVisible(curveWidthSlider);
    addAndMakeVisible(bypasssButton);
    addAndMakeVisible(waveformLabel);
    addAndMakeVisible(rateLabel);
    addAndMakeVisible(bypassedLabel);
    bypassedLabel.setFont(CustomLookAndFeel::getSideLabelsFont());
    waveformLabel.setFont(CustomLookAndFeel::getSideLabelsFont());

    setLookAndFeel(&lookAndFeel);

  // Make sure that before the constructor has finished, you've set the
  // editor's size to whatever you need it to be.
    setSize(540, 300);
}

PluginEditor::~PluginEditor() {
    setLookAndFeel(nullptr);
}

void PluginEditor::resized() {
  const auto bounds = getLocalBounds();

  background.setBounds({0, 0, getWidth(), 270});

  logo.setBounds({16, 16, 105, 24});

  auto waveFormComboBoxBounds = bounds;
  waveFormComboBoxBounds.removeFromTop(99);
  waveFormComboBoxBounds.removeFromBottom(176);
  waveFormComboBoxBounds.removeFromLeft(16);
  waveFormComboBoxBounds.removeFromRight(392);

  waveformComboBox.setBounds(waveFormComboBoxBounds);

  const auto waveformLabelBounds = waveFormComboBoxBounds.translated(0, -waveFormComboBoxBounds.getHeight());
  waveformLabel.setBounds(waveformLabelBounds);


  auto curveWidthSliderBounds = bounds;
  curveWidthSliderBounds.removeFromTop(270);
  curveWidthSlider.setBounds(curveWidthSliderBounds);

  auto rateSliderBounds = bounds;
  rateSliderBounds.removeFromBottom(180);
  rateSliderBounds.removeFromTop(40);
  rateSliderBounds.removeFromLeft(230);
  rateSliderBounds.removeFromRight(230);
  rateSlider.setBounds(rateSliderBounds);
  
  rateLabel.setBounds(rateSliderBounds);
  rateLabel.setJustificationType(juce::Justification::centred);
  rateLabel.setInterceptsMouseClicks(false, false);


  lfoVisualizer.setBounds({18, 148, 504, 92});

  auto buttonBounds = bounds;
  buttonBounds.removeFromTop(99);
  buttonBounds.removeFromRight(16);
  buttonBounds.removeFromBottom(176);
  buttonBounds.removeFromLeft(392);
  bypasssButton.setBounds(buttonBounds);
  
  const auto bypassedLabelBounds = buttonBounds.translated(0, -buttonBounds.getHeight());
  bypassedLabel.setBounds(bypassedLabelBounds);

  
}
}  // namespace tremolo
