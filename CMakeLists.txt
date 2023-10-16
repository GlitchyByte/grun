# Copyright 2023 GlitchyByte
# SPDX-License-Identifier: MIT-0

cmake_minimum_required(VERSION 3.26)

if(NOT CMAKE_BUILD_TYPE)
    # Force MinSizeRel if no build type specified.
    set(CMAKE_BUILD_TYPE "MinSizeRel" CACHE STRING "Type of build." FORCE)
endif()

# Main binary to build.
set(APP "grun")
project(${APP} VERSION 1.0.0)

# Set C++ standard and binary output dir.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

if(CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
    message(STATUS ${CMAKE_BUILD_TYPE})
    if(CMAKE_SYSTEM_NAME STREQUAL "Linux" OR CMAKE_SYSTEM_NAME STREQUAL "Darwin")
        # Linux and macOS.
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -flto -ffunction-sections -fdata-sections")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -flto -ffunction-sections -fdata-sections")
    elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
        # Windows has not been tested.
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /GL")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /GL")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /LTCG")
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /LTCG")
    else()
        message(WARNING "Unknown OS.")
    endif ()
endif()

# Add all cpp files in src dir.
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")
add_executable(${APP} ${SOURCES})

target_include_directories(${APP} PRIVATE include)

if((CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "MinSizeRel") AND
        (CMAKE_SYSTEM_NAME STREQUAL "Linux" OR CMAKE_SYSTEM_NAME STREQUAL "Darwin"))
    # Strip all remaining symbols and relocation information.
    add_custom_command(
        TARGET ${APP}
        POST_BUILD
        COMMAND strip $<TARGET_FILE:${APP}>
    )
endif ()
