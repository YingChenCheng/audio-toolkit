#pragma once
#include "my_toolkit/audio_node.hpp"
#include <cmath>
#include <numbers>

namespace audio_toolkit {

class SineWaveNode : public AudioNode {
  public:
    SineWaveNode(float frequency = 440.0f, float sample_rate = 48000.0f)
        : frequency_(frequency), sample_rate_(sample_rate) {}

    void set_frequency(float freq) { frequency_ = freq; }

    void process(AudioBuffer &buffer) override {
        if (!enabled_)
            return;

        const double phase_increment = 2.0 * std::numbers::pi * frequency_ / sample_rate_;
        const size_t channels = buffer.get_num_channels();
        const size_t frames = buffer.get_num_frames();

        for (size_t frame = 0; frame < frames; ++frame) {
            float sample = static_cast<float>(std::sin(phase_));
            phase_ += phase_increment;
            if (phase_ >= 2.0 * std::numbers::pi) {
                phase_ -= 2.0 * std::numbers::pi;
            }

            for (size_t ch = 0; ch < channels; ++ch) {
                buffer.set_sample(ch, frame, sample);
            }
        }
    }

  private:
    float frequency_;
    float sample_rate_;
    double phase_{0.0};
};

} // namespace audio_toolkit