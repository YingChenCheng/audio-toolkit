#include <gtest/gtest.h>
#include <my_toolkit/sine_wave_player.hpp>
#include <vector>
#include <cmath>

TEST(SineWaveTest, CallbackOutputBoundsAndFrequency) {
    const float sample_rate = 48000.0f;
    const float frequency = 440.0f;
    const size_t frame_count = 512;

    audio_toolkit::SineWavePlayer player(frequency, sample_rate);
    
    std::vector<float> output_buffer(frame_count, 0.0f);
    
    player.audio_callback(output_buffer.data(), nullptr, frame_count);

    EXPECT_NEAR(output_buffer[0], 0.0f, 1e-5f);
    for (size_t i = 0; i < frame_count; ++i) {
        EXPECT_LE(std::abs(output_buffer[i]), 0.2001f);
    }
    size_t quarter_period_index = static_cast<size_t>(sample_rate / frequency / 4.0f);
    EXPECT_NEAR(output_buffer[quarter_period_index], 0.2f, 0.02f);
}