#pragma once
#include <cstddef>
#include <vector>

namespace audio_toolkit {

class AudioBuffer {
  public:
    explicit AudioBuffer(size_t num_channels = 1, size_t num_frames = 512);

    size_t get_num_channels() const { return num_channels_; }
    size_t get_num_frames() const { return num_frames_; }

    void clear();

    float get_sample(size_t channel, size_t frame) const;
    void set_sample(size_t channel, size_t frame, float value);

  private:
    size_t num_channels_;
    size_t num_frames_;
    std::vector<float> data_;
};

} // namespace audio_toolkit