cmake_minimum_required(VERSION 3.28)
project(Pixa LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(BUILD_SHARED_LIBS OFF)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.1.0
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(Pixa main.cpp
        src/Button.cpp
        src/Button.hpp
        src/Constants.hpp)

target_compile_features(Pixa PRIVATE cxx_std_17)

target_link_libraries(Pixa PRIVATE SFML::Graphics)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_link_options(Pixa PRIVATE -static -static-libgcc -static-libstdc++)
endif()

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Pixa)