#include <iostream>
#include <thread>
#include <chrono>
#include <memory>
#include "my_toolkit/audio_engine.hpp"
#include "my_toolkit/sine_wave_node.hpp"
#include "my_toolkit/biquad_filter_node.hpp"
#include "my_toolkit/gain_node.hpp"

using namespace audio_toolkit;

int main() {
    std::cout << "Audio Toolkit Initialized successfully!\n";
    std::cout << "Starting Audio Graph Engine...\n";

    AudioEngine engine(48000, 1);

    auto sine_source = std::make_shared<SineWaveNode>(880.0f, 48000.0f);
    auto lpf_filter  = std::make_shared<BiquadFilterNode>(BiquadFilterNode::Type::LowPass, 400.0f, 0.707f, 48000.0f);
    auto gain_ctrl   = std::make_shared<GainNode>(0.2f);

    engine.add_node(sine_source);
    engine.add_node(lpf_filter);
    engine.add_node(gain_ctrl);

    if (engine.start()) {
        std::cout << "Playing 880Hz Sine Wave with 400Hz Low-Pass Filter (muted high tone)..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));

        std::cout << "Bypassing Low-Pass Filter (original 880Hz tone)..." << std::endl;
        lpf_filter->set_enabled(false);
        std::this_thread::sleep_for(std::chrono::seconds(2));

        engine.stop();
        std::cout << "Engine stopped.\n";
    } else {
        std::cerr << "Failed to start.\n";
        return 1;
    }

    return 0;
}