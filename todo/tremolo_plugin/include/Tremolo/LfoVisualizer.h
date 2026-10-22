namespace tremolo {

    class LfoVisualizer : public juce::Component {

        public: 
            void paint(juce::Graphics& g) override {
                juce::Path sine;
                const auto strokeWidth = 4.0f;
                const auto halfHeight = getHeight() / 2;
                const auto amplitude = halfHeight - strokeWidth;

                sine.startNewSubPath(0.f, halfHeight + amplitude * std::sin(0.f));
                
                for (const auto x : std::views::iota(1, getWidth())) {
                    sine.lineTo(x, halfHeight + amplitude * std::sin(0.1f * x));
                }

                g.setColour(juce::Colours::orange);
                g.strokePath(sine, juce::PathStrokeType{strokeWidth});
            }


    };

} //namespace tremolo