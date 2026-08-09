#include <iostream>
#include <my_toolkit/audio_buffer.hpp>

int main() {
    audio_toolkit::AudioBuffer buffer(2, 512);
    std::cout << "Audio Toolkit Initialized successfully!\n";
    std::cout << "Buffer Channels: " << buffer.get_num_channels()
              << ", Frames: " << buffer.get_num_frames() << "\n";
    return 0;
}