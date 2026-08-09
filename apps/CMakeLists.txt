add_executable(audio_app
    main.cpp
)

target_link_libraries(audio_app
    PRIVATE
        my_toolkit
)