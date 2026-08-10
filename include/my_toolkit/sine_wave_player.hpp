#pragma once
#include <miniaudio.h>
#include <atomic>

namespace audio_toolkit {

class SineWavePlayer {
public:
    SineWavePlayer(float frequency = 440.0f, float sample_rate = 48000.0f);
    ~SineWavePlayer();

    bool start();
    void stop();
    void audio_callback(void* output_buffer, const void* input_buffer, ma_uint32 frame_count);

private:
    float frequency_;
    float sample_rate_;
    double phase_{0.0};
    
    ma_device device_;
    std::atomic<bool> is_running_{false};
};

}