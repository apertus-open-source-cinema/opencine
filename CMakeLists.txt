cmake_minimum_required(VERSION 2.8)
project(ApertusOpenCine)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(${PROJECT_SOURCE_DIR}/Source/OpenCine/)
add_subdirectory(${PROJECT_SOURCE_DIR}/Source/CinemaDNGDecoder/)
