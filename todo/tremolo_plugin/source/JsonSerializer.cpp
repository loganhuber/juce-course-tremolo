namespace tremolo {

  namespace 
  {
    struct SerializableParameters {
      float rate;
      bool bypassed;
      juce::String waveform;

      static constexpr auto marshallingVersion = 1;

      template <typename Archive, typename T>
      static void serialise(Archive& archive, T& t) {

        using namespace juce;

        if (archive.getVersion() != 1) {
          return;
        }

        std::string pluginName = TREMOLO_PLUGIN_NAME;
        archive(named("pluginName", pluginName));

        if (pluginName != TREMOLO_PLUGIN_NAME) {
          return;
        }

        archive(named("modulationRateHz", t.rate),
         named("bypassed", t.bypassed), 
         named("modulationWaveform", t.waveform));

      }
    };

    SerializableParameters from(const Parameters& parameters) {
      return {
        .rate = parameters.rate.get(),
        .bypassed = parameters.bypassed.get(),
        .waveform = parameters.waveform.getCurrentChoiceName(),
      };
    }
  } // unnamed namespace 
  
void JsonSerializer::serialize(const Parameters& parameters,
                               juce::OutputStream& output) {

    const auto parametersToSerialize = from(parameters);
    const auto json = juce::ToVar::convert(parametersToSerialize);

    if (!json.has_value()) {
      return;
    }

    juce::JSON::writeToStream(
                            output, 
                            *json, 
                            juce::JSON::FormatOptions{}
                            .withSpacing(juce::JSON::Spacing::multiLine)
                            .withMaxDecimalPlaces(2)
                          );
  // TODO: serialize parameters to the output stream as JSON
}

juce::Result JsonSerializer::deserialize(juce::InputStream& input,
                                         Parameters& parameters) {
  juce::ignoreUnused(input, parameters);

  // TODO: deserialize parameters from the JSON input stream
  juce::var parsedResult;
  const auto result = juce::JSON::parse(input.readEntireStreamAsString(), parsedResult);

  if (result.failed()) {
    return result;
  }

  const auto parsedParameters = juce::FromVar::convert<SerializableParameters>(parsedResult);

  if (!parsedParameters.has_value()) {
    return juce::Result::fail("Failed to deserialize json");
  }

  const auto modulationWaveformIndex = parameters.waveform.choices.indexOf(parsedParameters->waveform);

  if (modulationWaveformIndex < 0) {
    return juce::Result::fail("Invalid modulation waveform name. Supported values are: " +
    parameters.waveform.choices.joinIntoString(", "));
  }

  parameters.waveform = modulationWaveformIndex;
  parameters.rate = parsedParameters->rate;
  parameters.bypassed = parsedParameters->bypassed;

  return juce::Result::ok();
}
}  // namespace tremolo
