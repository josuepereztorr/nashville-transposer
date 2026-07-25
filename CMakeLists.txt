cmake_minimum_required(VERSION 3.16)
project(nashville_transposer C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

file(GLOB_RECURSE SOURCES src/*.c)

add_executable(nashville_transposer ${SOURCES})

target_include_directories(nashville_transposer PRIVATE
    /usr/local/include
    src
    src/ui/vendor
)

target_link_directories(nashville_transposer PRIVATE /usr/local/lib)
target_link_libraries(nashville_transposer PRIVATE raylib portmidi)

# cd build && cmake .. && cmake --build . && cd .. && ./build/nashville_transposer