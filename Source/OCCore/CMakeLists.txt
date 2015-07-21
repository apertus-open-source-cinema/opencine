cmake_minimum_required(VERSION 2.8)
PROJECT(OCCore)

CMAKE_POLICY(SET CMP0020 NEW)

set( CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

file(GLOB SOURCE_FILES "*.cpp" "*.h")
#file(GLOB HEADER_FILES "*.h")

#include_directories(${PROJECT_SOURCE_DIR})

if(WIN32)
    file(GLOB PLATFORM_FILES "Platforms/Win/*.cpp" "Platforms/Win/*.h")
    #file(GLOB HEADER_FILES "Platforms/Win")
elseif(LINUX)
    file(GLOB PLATFORM_FILES "Platforms/Linux")
    #file(GLOB HEADER_FILES "Platforms/Linux")
endif()

#SET(INCLUDE_DIRS "")
#foreach (_headerFile ${HEADER_FILES})
    #get_filename_component(_dir ${_headerFile} PATH)
    #list (APPEND INCLUDE_DIRS ${_dir})
#endforeach()
#list(REMOVE_DUPLICATES INCLUDE_DIRS)

ADD_LIBRARY(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${PLATFORM_FILES})
