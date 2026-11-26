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
        
        g.setFont(interMedium().withPointHeight(12.f));   
                                                    
    //    DBG(g.getCurrentFont().getTypefacePtr()->getName());
        g.drawText(button.getButtonText(), bounds, juce::Justification::centred, false);
        
    }

    void CustomLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
         float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, juce::Slider&) 
    {

        auto bounds = juce::Rectangle{x, y, width, height}.toFloat().reduced(3.75f);
        g.setColour(juce::Colour{0xFF2A3A3B});
        g.fillEllipse(bounds);

        auto toAngle = 
            rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);

        juce::Path valueArc;
        valueArc.addPieSegment(bounds.reduced(0.25f), rotaryStartAngle, toAngle, 0.f);

        g.setColour(juce::Colour{0xFFFFAA00});
        g.fillPath(valueArc);
        
        auto cannalBounds = bounds.reduced(2.0f);
        g.setColour(juce::Colour{0xFF2A3A3B});
        g.fillEllipse(cannalBounds.reduced(3.0f));

        auto knobStrokeBounds = cannalBounds.reduced(4.5f);
        g.setColour(juce::Colour{0xFF0B1E3A});
        g.fillEllipse(knobStrokeBounds);

        auto knobBounds = cannalBounds.reduced(6.5f);
        auto knobGradient = juce::ColourGradient::vertical(juce::Colour{0xFF060F1C}, knobBounds.getBottom(), juce::Colour{0xFF4A7090}, 0.f);

        g.setGradientFill(knobGradient);
        g.fillEllipse(knobBounds);

        auto knobTopBounds = knobStrokeBounds.reduced(8.f);

        g.setColour(juce::Colour{0x4C08EFA2});
        g.fillEllipse(knobTopBounds);
        
        auto knobTopGradient = juce::ColourGradient::vertical(juce::Colour{0xFF1B1E48}, knobBounds.getBottom(), juce::Colour{0xFF6697CB}, 0.f);
        g.setGradientFill(knobTopGradient);
        g.fillEllipse(knobTopBounds);

        auto knobEdgeGradient = juce::ColourGradient::vertical(juce::Colour{0xFF1A0F4E}, knobTopBounds.getBottom(), juce::Colour{0xFF8FFFFF}, 0.f);
        
        g.drawEllipse(knobTopBounds, 5.0f);

    }

    juce::FontOptions CustomLookAndFeel::interMedium() 
    {
        static const auto result = juce::FontOptions{
            juce::Typeface::createSystemTypefaceFor(
                assets::interMedium_ttf, 
                assets::interMedium_ttfSize
            )};
            return juce::FontOptions{result};
    }

}  // namespace tremolo
