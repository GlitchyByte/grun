cmake_minimum_required(VERSION 3.26)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Type of build (Debug or Release)" FORCE)
endif()

# Main binary to build.
set(APP "grun")

project(${APP} VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")
add_executable(${APP} ${SOURCES})

target_include_directories(${APP} PRIVATE include)
