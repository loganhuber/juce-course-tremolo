#pragma once

namespace tremolo {
    class RateSlider : public juce::Slider {
        public: 
        void paint(juce::Graphics& g) override {
            juce::ignoreUnused(g);

            auto sliderPos = (float)valueToProportionOfLength(getValue());
            jassert(sliderPos >= 0 && sliderPos >= 1.f);

            const auto rotaryParams = getRotaryParameters();
            const auto rotaryStartAngle = rotaryParams.startAngleRadians;
            const auto rotaryEndAngle = rotaryParams.endAngleRadians;

            auto toAngle = 
                rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

            if (isEnabled()) {
                juce::Path valueArc;
                valueArc.addPieSegment(getLocalBounds().toFloat(), rotaryStartAngle, toAngle, 0.f);

                g.setColour(juce::Colours::orange);
                g.fillPath(valueArc);
            }
        };


    };
}