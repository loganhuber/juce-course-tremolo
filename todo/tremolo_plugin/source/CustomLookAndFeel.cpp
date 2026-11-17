namespace tremolo {
    void CustomLookAndFeel::drawToggleButton(juce::Graphics& g, 
                                    juce::ToggleButton& button, 
                                    bool shouldDrawButtonAsHighlighted,
                                    bool shouldDrawButtonAsDown) 
    {
        juce::ignoreUnused(shouldDrawButtonAsDown);

        const auto backgroundBounds = button.getLocalBounds();

        auto backgroundGradient = juce::ColourGradient::vertical(
            juce::Colour{0xFF22232C},
            juce::Colour{0xFF303538},
            backgroundBounds
        );
        g.setGradientFill(backgroundGradient);
        g.fillRoundedRectangle(backgroundBounds.toFloat(), 4.f);

        const auto bounds = backgroundBounds.reduced(3, 3);


        if (button.getToggleState()) {
            auto buttonGradient = shouldDrawButtonAsHighlighted ?
            juce::ColourGradient::vertical(juce::Colour{0xAAFF901A},
                                            juce::Colour{0xAAFFC300},
                                            bounds) :
            juce::ColourGradient::vertical(juce::Colour{0xFFFF901A},
                                            juce::Colour{0xFFFF901A},
                                        bounds);

            g.setGradientFill(buttonGradient);
            g.fillRoundedRectangle(bounds.toFloat(), 4.f);
    
            g.setColour(juce::Colour{0xFF501A0B});
        } 
        else {
            auto buttonGradient = shouldDrawButtonAsHighlighted ? 
            juce::ColourGradient::vertical(
                                        juce::Colour{0xAA4A0970},
                                        juce::Colour{0xAA324588},
                                        bounds) :
            juce::ColourGradient::vertical(
                                        juce::Colour{0xFF4A0970},
                                        juce::Colour{0xFF324588},
                                        bounds);
            buttonGradient.addColour(0.73, juce::Colour{0xFF315160});
            g.setGradientFill(buttonGradient);
            g.fillRoundedRectangle(bounds.toFloat(), 4.f);
    
            g.setColour(juce::Colour{0xFFDDECFF});

        }
        g.drawText(button.getButtonText(), bounds, juce::Justification::centred, false);
        
    }

}  // namespace tremolo
