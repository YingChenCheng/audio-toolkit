cmake_minimum_required(VERSION 3.20)

project(MyAudioToolkit 
    VERSION 1.0.0
    LANGUAGES CXX C
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_subdirectory(src)
add_subdirectory(apps)

option(BUILD_TESTS "Build unit tests" ON)

if(BUILD_TESTS)
    enable_testing() 
    add_subdirectory(tests)
endif()