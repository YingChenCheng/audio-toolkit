#include "my_toolkit/sine_wave_player.hpp"
#include <cmath>
#include <numbers>
#include <iostream>

namespace audio_toolkit {

static void ma_audio_callback_bridge(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount) {
    auto* player = static_cast<SineWavePlayer*>(pDevice->pUserData);
    if (player) {
        player->audio_callback(pOutput, pInput, frameCount);
    }
}

SineWavePlayer::SineWavePlayer(float frequency, float sample_rate)
    : frequency_(frequency), sample_rate_(sample_rate) {
    
    ma_device_config config = ma_device_config_init(ma_device_type_playback);
    config.playback.format   = ma_format_f32;
    config.playback.channels = 1;
    config.sampleRate        = static_cast<ma_uint32>(sample_rate_);
    config.dataCallback      = ma_audio_callback_bridge;
    config.pUserData         = this;

    if (ma_device_init(NULL, &config, &device_) != MA_SUCCESS) {
        std::cerr << "Failed to initialize miniaudio device.\n";
    }
}

SineWavePlayer::~SineWavePlayer() {
    stop();
    ma_device_uninit(&device_);
}

bool SineWavePlayer::start() {
    if (is_running_) return true;
    if (ma_device_start(&device_) == MA_SUCCESS) {
        is_running_ = true;
        return true;
    }
    return false;
}

void SineWavePlayer::stop() {
    if (!is_running_) return;
    ma_device_stop(&device_);
    is_running_ = false;
}

void SineWavePlayer::audio_callback(void* output_buffer, const void* input_buffer, ma_uint32 frame_count) {
    (void)input_buffer;

    float* out = static_cast<float*>(output_buffer);
    const double phase_increment = 2.0 * std::numbers::pi * frequency_ / sample_rate_;

    for (ma_uint32 i = 0; i < frame_count; ++i) {
        out[i] = 0.2f * static_cast<float>(std::sin(phase_));

        phase_ += phase_increment;
        if (phase_ >= 2.0 * std::numbers::pi) {
            phase_ -= 2.0 * std::numbers::pi;
        }
    }
}

}