cmake_minimum_required(VERSION 2.8)
project(ApertusOpenCine)

#TODO: Enable C++11 support for all projects. Adjust when porting to windows (e.g. for Visual Studio compatibility)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#Force to output to /bin and /lib on Windows, witohut additional "Debug" and "Release" folder
#Source: http://stackoverflow.com/questions/543203/cmake-runtime-output-directory-on-windows
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
SET( CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
SET( CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

#Includes
include_directories("${PROJECT_SOURCE_DIR}/3rdParty/LibRaw")

#Dependencies
SET(ENABLE_EXAMPLES OFF CACHE BOOL "Build LibRaw shared library")
add_subdirectory(${PROJECT_SOURCE_DIR}/3rdParty/LibRaw)

#Projects
add_subdirectory(${PROJECT_SOURCE_DIR}/Source/OpenCine/)
add_subdirectory(${PROJECT_SOURCE_DIR}/Source/CinemaDNGDecoder/)
add_subdirectory(${PROJECT_SOURCE_DIR}/Source/CinemaDNGInfo/)
