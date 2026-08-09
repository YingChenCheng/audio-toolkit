#pragma once
#include <vector>
#include <cstddef>

namespace audio_toolkit {

class AudioBuffer {
public:
    explicit AudioBuffer(size_t num_channels, size_t num_frames);
    size_t get_num_channels() const { return num_channels_; }
    size_t get_num_frames() const { return num_frames_; }
    void clear();

private:
    size_t num_channels_;
    size_t num_frames_;
    std::vector<float> data_;
};

}