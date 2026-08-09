#include <gtest/gtest.h>
#include <my_toolkit/audio_buffer.hpp>

TEST(AudioBufferTest, BasicInitialization) {
    audio_toolkit::AudioBuffer buffer(2, 512);
    EXPECT_EQ(buffer.get_num_channels(), 2);
    EXPECT_EQ(buffer.get_num_frames(), 512);
}