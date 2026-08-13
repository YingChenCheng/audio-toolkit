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

float AudioBuffer::get_sample(size_t channel, size_t frame) const {
    if (channel >= num_channels_ || frame >= num_frames_) {
        return 0.0f;
    }
    return data_[channel * num_frames_ + frame];
}

void AudioBuffer::set_sample(size_t channel, size_t frame, float value) {
    if (channel < num_channels_ && frame < num_frames_) {
        data_[channel * num_frames_ + frame] = value;
    }
}

}