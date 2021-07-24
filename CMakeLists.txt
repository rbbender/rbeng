cmake_minimum_required(VERSION 3.15)

project("rbeng")

set(CMAKE_CXX_FLAGS_RELEASE "/MT /Zi")
set(CMAKE_CXX_FLAGS_DEBUG "/MTd /Zi /Od")

add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_20)

# conan
if (NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan.io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.16.1/conan.cmake"
    "${CMAKE_BINARY_DIR}/conan.cmake"
    TLS_VERIFY ON
    )
else()
    message(STATUS "${CMAKE_BINARY_DIR}/conan.cmake exists")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_run(REQUIRES
    spdlog/[>=1.4.1]
    glfw/3.3.4
    glm/0.9.9.8
    freetype/2.10.4
    BASIC_SETUP
    CMAKE_TARGETS
    BUILD missing
)

add_subdirectory("src")
