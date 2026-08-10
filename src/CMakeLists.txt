add_library(my_toolkit
    audio_buffer.cpp
    sine_wave_player.cpp
    miniaudio_impl.cpp
)

target_include_directories(my_toolkit
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(my_toolkit PUBLIC miniaudio)

if(APPLE)
    target_link_libraries(my_toolkit PRIVATE "-framework CoreAudio" "-framework AudioToolbox")
elseif(UNIX AND NOT ANDROID)
    target_link_libraries(my_toolkit PRIVATE pthread dl m)
endif()