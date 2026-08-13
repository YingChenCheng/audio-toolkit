#pragma once
#include "my_toolkit/audio_node.hpp"
#include <cmath>
#include <numbers>
#include <vector>

namespace audio_toolkit {

class BiquadFilterNode : public AudioNode {
public:
    enum class Type { LowPass, HighPass };

    BiquadFilterNode(Type type = Type::LowPass, float cutoff_freq = 1000.0f, float q = 0.707f, float sample_rate = 48000.0f)
        : type_(type), cutoff_freq_(cutoff_freq), q_(q), sample_rate_(sample_rate) {
        update_coefficients();
        x1_ = x2_ = y1_ = y2_ = 0.0f;
    }

    void set_cutoff_frequency(float freq) {
        cutoff_freq_ = freq;
        update_coefficients();
    }

    void process(AudioBuffer& buffer) override {
        if (!enabled_) return;

        const size_t channels = buffer.get_num_channels();
        const size_t frames = buffer.get_num_frames();

        for (size_t frame = 0; frame < frames; ++frame) {
            for (size_t ch = 0; ch < channels; ++ch) {
                float x = buffer.get_sample(ch, frame);
                
                // Direct Form I Biquad Difference Equation:
                // y[n] = b0*x[n] + b1*x[n-1] + b2*x[n-2] - a1*y[n-1] - a2*y[n-2]
                float y = b0_ * x + b1_ * x1_ + b2_ * x2_ - a1_ * y1_ - a2_ * y2_;

                x2_ = x1_;
                x1_ = x;
                y2_ = y1_;
                y1_ = y;

                buffer.set_sample(ch, frame, y);
            }
        }
    }

private:
    void update_coefficients() {
        const float w0 = 2.0f * std::numbers::pi * cutoff_freq_ / sample_rate_;
        const float alpha = std::sin(w0) / (2.0f * q_);
        const float cos_w0 = std::cos(w0);

        if (type_ == Type::LowPass) {
            float a0 = 1.0f + alpha;
            b0_ = ((1.0f - cos_w0) / 2.0f) / a0;
            b1_ = (1.0f - cos_w0) / a0;
            b2_ = ((1.0f - cos_w0) / 2.0f) / a0;
            a1_ = (-2.0f * cos_w0) / a0;
            a2_ = (1.0f - alpha) / a0;
        }
    }

    Type type_;
    float cutoff_freq_;
    float q_;
    float sample_rate_;

    // filter coefficients
    float b0_{0}, b1_{0}, b2_{0}, a1_{0}, a2_{0};
    // delay state variables
    float x1_{0}, x2_{0}, y1_{0}, y2_{0};
};

}