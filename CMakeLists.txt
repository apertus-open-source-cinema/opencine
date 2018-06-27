# Copyright (c) 2017 apertus° Association & contributors
# Project: OpenCine
# License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

cmake_minimum_required(VERSION 3.5)
project(ApertusOpenCine)

include(ExternalProject)

CMAKE_POLICY(SET CMP0020 NEW)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#TODO: Enable C++11 support for all projects. Adjust when porting to windows (e.g. for Visual Studio compatibility)
if(NOT ${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

# Compiler flags
# SET(CMAKE_CXX_FLAGS "-O3") #Optimize

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/bench_frame.dng
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)

#SET( CMAKE_BUILD_TYPE Release ... FORCE )

#if(WIN32)
#ADD_DEFINITIONS(-DWIN32)
#endif()

# Simplifies configuration under Windows, have to be checked in Linux, if something similar is required when not using QtCreator
#IF(WIN32)
#    SET( CMAKE_PREFIX_PATH "C:/Qt/5.7/msvc2015_64/" CACHE FILEPATH "Qt path, e.g. C:/Qt/5.7/msvc2015_64/" )
#if(UNIX)
#   set(CMAKE_GENERATOR "Unix Makefiles")
#    SET( CMAKE_PREFIX_PATH "$HOME/Qt/5.8/gcc_64/lib/cmake" CACHE FILEPATH "Qt path, e.g. $HOME/Qt/5.8/gcc_64/lib/cmake/Qt5" )
#ENDIF()

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
#include_directories("${PROJECT_SOURCE_DIR}/3rdParty/xxHash")
include_directories("${PROJECT_SOURCE_DIR}/3rdParty/")

#Dependencies
SET(ENABLE_EXAMPLES OFF CACHE BOOL "LibRaw: Build shared library (without examples)")
#add_subdirectory(${PROJECT_SOURCE_DIR}/3rdParty/LibRaw)
add_subdirectory(${PROJECT_SOURCE_DIR}/3rdParty/xxHash/cmake_unofficial)
add_subdirectory(${PROJECT_SOURCE_DIR}/3rdParty/MemoryPool)

#ExternalProject_Add(FFMPEG
#PREFIX 3rdParty/FFMPEG
#GIT_REPOSITORY "https://github.com/FFmpeg/FFmpeg.git"
#GIT_TAG "master"
#INSTALL_COMMAND ""
#CONFIGURE_COMMAND ""
#BUILD_COMMAND ""
#GIT_SHALLOW 1 )

#ExternalProject_Add(QtAV
#                   PREFIX 3rdParty/QtAV
#                  GIT_REPOSITORY "https://github.com/wang-bin/QtAV.git"
#                 GIT_TAG "master"
#                INSTALL_COMMAND ""
#               UPDATE_COMMAND "")
#GIT_SHALLOW 1
#CMAKE_ARGS -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH} -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/bin)

#INCLUDE_DIRECTORIES({$QtAV_INCLUDE})
#message(STATUS $QtAV_SOURCE_DIR)

SET(QTDIR ${CMAKE_PREFIX_PATH})

#message(WARNING "CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")
#ExternalProject_Add(QtAV_project
#                    PREFIX 3rdParty/QtAV
#                    GIT_REPOSITORY "https://github.com/wang-bin/QtAV.git"
#                    GIT_TAG "master"
#                    UPDATE_COMMAND ""
#                    INSTALL_COMMAND ""
#                    CMAKE_ARGS -DQTDIR=${QTDIR} -DBUILD_EXAMPLES=OFF)


#ExternalProject_Get_Property(QtAV_project INSTALL_DIR)
#include_directories(${INSTALL_DIR}/src/QtAV_project/src/)
#message(WARNING "QTAV_DIR: ${INSTALL_DIR}/src/QtAV_project/src/")
#include_directories(${INSTALL_DIR}/src/QtAV_project/widgets/)

#Projects
#add_subdirectory(${PROJECT_SOURCE_DIR}/Source/OpenCine/)
add_subdirectory(${PROJECT_SOURCE_DIR}/Source/OCcore/)
add_subdirectory(${PROJECT_SOURCE_DIR}/Source/OCui/)
#add_subdirectory(${PROJECT_SOURCE_DIR}/Source/OCLauncher/)
#add_subdirectory(${PROJECT_SOURCE_DIR}/Source/OCBackup/)
add_subdirectory(${PROJECT_SOURCE_DIR}/Source/ProcessingTest/)
add_subdirectory(${PROJECT_SOURCE_DIR}/Source/UnitTests/)

#add_subdirectory(${PROJECT_SOURCE_DIR}/Source/CinemaDNGDecoder/)
#add_subdirectory(${PROJECT_SOURCE_DIR}/Source/CinemaDNGInfo/)
