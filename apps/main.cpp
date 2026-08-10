#include <iostream>
#include <thread>
#include <chrono>
#include <my_toolkit/sine_wave_player.hpp>

int main() {
    std::cout << "Audio Toolkit Initialized successfully!\n";
    std::cout << "Starting Audio Toolkit Sine Wave Test (440 Hz)...\n";
    audio_toolkit::SineWavePlayer player(440.0f, 48000.0f);
    if (player.start()) {
        std::cout << "Playing sine wave for 3 seconds...\n";
        std::this_thread::sleep_for(std::chrono::seconds(3));
        player.stop();
        std::cout << "Playback stopped.\n";
    } else {
        std::cerr << "Failed to start audio playback.\n";
        return 1;
    }

    return 0;
}