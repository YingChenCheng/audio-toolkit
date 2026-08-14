#include "my_toolkit/audio_engine.hpp"
#include <iostream>

namespace audio_toolkit {

static void ma_engine_callback(ma_device *pDevice, void *pOutput, const void *pInput,
                               ma_uint32 frameCount) {
    (void)pInput;
    auto *engine = static_cast<AudioEngine *>(pDevice->pUserData);
    if (engine) {
        engine->audio_callback(static_cast<float *>(pOutput), frameCount);
    }
}

AudioEngine::AudioEngine(size_t sample_rate, size_t channels)
    : sample_rate_(sample_rate), channels_(channels), internal_buffer_(channels, 512) {

    ma_device_config config = ma_device_config_init(ma_device_type_playback);
    config.playback.format = ma_format_f32;
    config.playback.channels = static_cast<ma_uint32>(channels_);
    config.sampleRate = static_cast<ma_uint32>(sample_rate_);
    config.dataCallback = ma_engine_callback;
    config.pUserData = this;

    if (ma_device_init(NULL, &config, &device_) != MA_SUCCESS) {
        std::cerr << "Failed to init miniaudio in AudioEngine\n";
    }
}

AudioEngine::~AudioEngine() {
    stop();
    ma_device_uninit(&device_);
}

void AudioEngine::add_node(std::shared_ptr<AudioNode> node) { pipeline_.push_back(node); }

bool AudioEngine::start() {
    if (is_running_)
        return true;
    if (ma_device_start(&device_) == MA_SUCCESS) {
        is_running_ = true;
        return true;
    }
    return false;
}

void AudioEngine::stop() {
    if (!is_running_)
        return;
    ma_device_stop(&device_);
    is_running_ = false;
}

void AudioEngine::audio_callback(float *output_buffer, size_t frame_count) {
    if (internal_buffer_.get_num_frames() != frame_count) {
        internal_buffer_ = AudioBuffer(channels_, frame_count);
    }

    internal_buffer_.clear();

    for (auto &node : pipeline_) {
        node->process(internal_buffer_);
    }

    for (size_t frame = 0; frame < frame_count; ++frame) {
        for (size_t ch = 0; ch < channels_; ++ch) {
            output_buffer[frame * channels_ + ch] = internal_buffer_.get_sample(ch, frame);
        }
    }
}

} // namespace audio_toolkit