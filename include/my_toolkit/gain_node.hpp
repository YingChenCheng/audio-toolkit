#pragma once
#include "my_toolkit/audio_node.hpp"

namespace audio_toolkit {

class GainNode : public AudioNode {
public:
    explicit GainNode(float gain_linear = 0.2f) : gain_(gain_linear) {}

    void set_gain(float gain_linear) { gain_ = gain_linear; }

    void process(AudioBuffer& buffer) override {
        if (!enabled_) return;

        const size_t channels = buffer.get_num_channels();
        const size_t frames = buffer.get_num_frames();

        for (size_t ch = 0; ch < channels; ++ch) {
            for (size_t frame = 0; frame < frames; ++frame) {
                float sample = buffer.get_sample(ch, frame);
                buffer.set_sample(ch, frame, sample * gain_);
            }
        }
    }

private:
    float gain_;
};

}