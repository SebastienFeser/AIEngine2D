# =============================================================================
# AIEngine2D - SNES-Like 2D Pixel Perfect Game Engine
# Top-level CMakeLists.txt
# =============================================================================

cmake_minimum_required(VERSION 3.16)

project(AIEngine2D
    VERSION 0.1.0
    DESCRIPTION "SNES-inspired 2D pixel-perfect game engine"
    LANGUAGES CXX
)

# =============================================================================
# C++ Standard
# =============================================================================

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# =============================================================================
# Compiler Detection & Flags
# =============================================================================

message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    message(STATUS "Using MSVC compiler")
    add_compile_options(
        /W4                 # Warning level 4
        /permissive-        # Strict conformance
        /Zc:__cplusplus     # Correct __cplusplus macro
    )
    # Release optimizations
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /DNDEBUG")
    # Debug flags
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zi /Od")

elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(STATUS "Using GCC compiler")
    add_compile_options(
        -Wall -Wextra -Wpedantic
        -Wno-unused-parameter
    )
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -DNDEBUG")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")

elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    message(STATUS "Using Clang compiler")
    add_compile_options(
        -Wall -Wextra -Wpedantic
        -Wno-unused-parameter
    )
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -DNDEBUG")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")

else()
    message(WARNING "Unknown compiler: ${CMAKE_CXX_COMPILER_ID}")
endif()

# =============================================================================
# Build Type
# =============================================================================

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type" FORCE)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# =============================================================================
# Output Directories
# =============================================================================

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# =============================================================================
# Dependencies (via vcpkg)
# =============================================================================

# --- SDL2 ---
find_package(SDL2 CONFIG REQUIRED)
message(STATUS "SDL2 found")

# --- OpenGL ---
find_package(OpenGL REQUIRED)
message(STATUS "OpenGL found: ${OPENGL_LIBRARIES}")

# --- ImGui ---
find_package(imgui CONFIG REQUIRED)
message(STATUS "ImGui found")

# =============================================================================
# Engine Configuration
# =============================================================================

# Internal resolution (SNES-like)
set(ENGINE_INTERNAL_WIDTH 256 CACHE STRING "Internal render width")
set(ENGINE_INTERNAL_HEIGHT 224 CACHE STRING "Internal render height")

# Default window size
set(ENGINE_WINDOW_WIDTH 800 CACHE STRING "Default window width")
set(ENGINE_WINDOW_HEIGHT 600 CACHE STRING "Default window height")

# Max entities
set(ENGINE_MAX_ENTITIES 10000 CACHE STRING "Maximum number of entities")

# Configure header
configure_file(
    "${CMAKE_SOURCE_DIR}/src/core/config.h.in"
    "${CMAKE_BINARY_DIR}/generated/config.h"
    @ONLY
)

# =============================================================================
# Include Directories
# =============================================================================

include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR}/generated
)

# =============================================================================
# Subdirectories
# =============================================================================

# Engine source
add_subdirectory(src)

# Tests (optional)
option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Examples (optional)
option(BUILD_EXAMPLES "Build examples" ON)
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# =============================================================================
# Summary
# =============================================================================

message(STATUS "")
message(STATUS "=== AIEngine2D Configuration ===")
message(STATUS "Version:          ${PROJECT_VERSION}")
message(STATUS "Build type:       ${CMAKE_BUILD_TYPE}")
message(STATUS "Compiler:         ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "C++ Standard:     ${CMAKE_CXX_STANDARD}")
message(STATUS "Internal res:     ${ENGINE_INTERNAL_WIDTH}x${ENGINE_INTERNAL_HEIGHT}")
message(STATUS "Window size:      ${ENGINE_WINDOW_WIDTH}x${ENGINE_WINDOW_HEIGHT}")
message(STATUS "Max entities:     ${ENGINE_MAX_ENTITIES}")
message(STATUS "Build tests:      ${BUILD_TESTS}")
message(STATUS "Build examples:   ${BUILD_EXAMPLES}")
message(STATUS "================================")
message(STATUS "")
