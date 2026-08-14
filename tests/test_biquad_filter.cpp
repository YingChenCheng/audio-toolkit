#include <gtest/gtest.h>
#include <my_toolkit/audio_buffer.hpp>
#include <my_toolkit/sine_wave_node.hpp>
#include <my_toolkit/biquad_filter_node.hpp>
#include <cmath>
#include <algorithm>

namespace audio_toolkit {

float calculate_peak(const AudioBuffer& buffer, size_t channel = 0) {
    float max_val = 0.0f;
    for (size_t frame = 0; frame < buffer.get_num_frames(); ++frame) {
        max_val = std::max(max_val, std::abs(buffer.get_sample(channel, frame)));
    }
    return max_val;
}

float calculate_rms(const AudioBuffer& buffer, size_t channel = 0) {
    float sum_squares = 0.0f;
    const size_t frames = buffer.get_num_frames();
    for (size_t frame = 0; frame < frames; ++frame) {
        float sample = buffer.get_sample(channel, frame);
        sum_squares += sample * sample;
    }
    return std::sqrt(sum_squares / static_cast<float>(frames));
}

TEST(BiquadFilterTest, LowPassAttenuatesHighFrequency) {
    const float sample_rate = 48000.0f;
    const size_t num_frames = 2048;

    const float input_freq = 1000.0f;
    SineWaveNode sine_gen(input_freq, sample_rate);
    
    AudioBuffer dry_buffer(1, num_frames);
    sine_gen.process(dry_buffer);

    float dry_peak = calculate_peak(dry_buffer);
    EXPECT_NEAR(dry_peak, 1.0f, 1e-3f);

    const float cutoff_freq = 200.0f;
    BiquadFilterNode lpf_node(BiquadFilterNode::Type::LowPass, cutoff_freq, 0.707f, sample_rate);

    AudioBuffer wet_buffer = dry_buffer;
    lpf_node.process(wet_buffer);

    AudioBuffer steady_state_buffer(1, num_frames / 2);
    for (size_t i = 0; i < num_frames / 2; ++i) {
        steady_state_buffer.set_sample(0, i, wet_buffer.get_sample(0, i + num_frames / 2));
    }

    float wet_peak = calculate_peak(steady_state_buffer);
    float wet_rms  = calculate_rms(steady_state_buffer);

    EXPECT_LT(wet_peak, 0.15f);
    EXPECT_LT(wet_rms, 0.10f);

    AudioBuffer bypass_buffer = dry_buffer;
    lpf_node.set_enabled(false);
    lpf_node.process(bypass_buffer);

    float bypass_peak = calculate_peak(bypass_buffer);
    EXPECT_NEAR(bypass_peak, dry_peak, 1e-4f);
}

}