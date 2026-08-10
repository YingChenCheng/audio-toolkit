include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(unit_tests
    test_audio_buffer.cpp
    test_sine_wave.cpp
)

target_link_libraries(unit_tests
    PRIVATE
        my_toolkit
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(unit_tests)