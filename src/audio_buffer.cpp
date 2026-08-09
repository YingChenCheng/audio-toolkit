#include "my_toolkit/audio_buffer.hpp"
#include <algorithm>

namespace audio_toolkit {

AudioBuffer::AudioBuffer(size_t num_channels, size_t num_frames)
    : num_channels_(num_channels),
      num_frames_(num_frames),
      data_(num_channels * num_frames, 0.0f) {}

void AudioBuffer::clear() {
    std::fill(data_.begin(), data_.end(), 0.0f);
}

}