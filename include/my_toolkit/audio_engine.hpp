#pragma once
#include "my_toolkit/audio_buffer.hpp"
#include "my_toolkit/audio_node.hpp"
#include <atomic>
#include <memory>
#include <miniaudio.h>
#include <vector>

namespace audio_toolkit {

class AudioEngine {
  public:
    AudioEngine(size_t sample_rate = 48000, size_t channels = 1);
    ~AudioEngine();

    void add_node(std::shared_ptr<AudioNode> node);

    bool start();
    void stop();

    void audio_callback(float *output_buffer, size_t frame_count);

  private:
    size_t sample_rate_;
    size_t channels_;
    ma_device device_;
    std::atomic<bool> is_running_{false};

    std::vector<std::shared_ptr<AudioNode>> pipeline_;
    AudioBuffer internal_buffer_;
};

} // namespace audio_toolkit