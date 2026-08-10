#include <gtest/gtest.h>
#include <my_toolkit/audio_buffer.hpp>

TEST(AudioBufferTest, Initialization) {
    audio_toolkit::AudioBuffer buffer(2, 512);
    EXPECT_EQ(buffer.get_num_channels(), 2);
    EXPECT_EQ(buffer.get_num_frames(), 512);
}

TEST(AudioBufferTest, ClearData) {
    audio_toolkit::AudioBuffer buffer(1, 100);
    buffer.clear();
    EXPECT_EQ(buffer.get_num_frames(), 100);
}