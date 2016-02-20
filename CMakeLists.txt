cmake_minimum_required(VERSION 3.2)
project(ApertusOpenCine)

CMAKE_POLICY(SET CMP0020 NEW)

#TODO: Enable C++11 support for all projects. Adjust when porting to windows (e.g. for Visual Studio compatibility)
if(NOT ${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

#if(WIN32)
        #ADD_DEFINITIONS(-DWIN32)
#endif()

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#Force to output to /bin and /lib on Windows, without additional "Debug" and "Release" folder
#Source: http://stackoverflow.com/questions/543203/cmake-runtime-output-directory-on-windows
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
SET( CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
SET( CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

#Includes
#include_directories("${PROJECT_SOURCE_DIR}/3rdParty/LibRaw")
#include_directories("${PROJECT_SOURCE_DIR}/3rdParty/Catch")
#include_directories("${PROJECT_SOURCE_DIR}/3rdParty/RawSpeed/include")
include_directories("${PROJECT_SOURCE_DIR}/3rdParty/xxHash")

#Dependencies
SET(ENABLE_EXAMPLES OFF CACHE BOOL "LibRaw: Build shared library (without examples)")
#add_subdirectory(${PROJECT_SOURCE_DIR}/3rdParty/LibRaw)
add_subdirectory(${PROJECT_SOURCE_DIR}/3rdParty/xxHash)
add_subdirectory(${PROJECT_SOURCE_DIR}/3rdParty/EventBus)

#Projects
#add_subdirectory(${PROJECT_SOURCE_DIR}/Source/OpenCine/)
add_subdirectory(${PROJECT_SOURCE_DIR}/Source/OCCore/)
add_subdirectory(${PROJECT_SOURCE_DIR}/Source/OCui/)
add_subdirectory(${PROJECT_SOURCE_DIR}/Source/OCLauncher/)
add_subdirectory(${PROJECT_SOURCE_DIR}/Source/OCBackup/)
add_subdirectory(${PROJECT_SOURCE_DIR}/Source/ProcessingTest/)

#add_subdirectory(${PROJECT_SOURCE_DIR}/Source/CinemaDNGDecoder/)
#add_subdirectory(${PROJECT_SOURCE_DIR}/Source/CinemaDNGInfo/)
