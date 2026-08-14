#pragma once
#include "my_toolkit/audio_buffer.hpp"
#include <memory>

namespace audio_toolkit {

class AudioNode {
  public:
    virtual ~AudioNode() = default;

    virtual void process(AudioBuffer &buffer) = 0;

    void set_enabled(bool enabled) { enabled_ = enabled; }
    bool is_enabled() const { return enabled_; }

  protected:
    bool enabled_{true};
};

} // namespace audio_toolkit