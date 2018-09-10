# Copyright (c) 2017 apertus° Association & contributors
# Project: OpenCine / OCcore
# License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

cmake_minimum_required(VERSION 3.2)
PROJECT(OCcore)

CMAKE_POLICY(SET CMP0020 NEW)

set( CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

FIND_PACKAGE(Qt5 COMPONENTS Core REQUIRED)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

INCLUDE_DIRECTORIES("${MemoryPool_SOURCE_DIR}/C-11")

file(GLOB SOURCE_FILES "*.cpp" "*.h"
    "Transfer/*.cpp" "Transfer/*.h"
    "MVP/*.cpp" "MVP/*.h"
    "API/*.cpp" "API/*.h"
    "Image/*.cpp" "Image/*.h"
    "Interfaces/*.cpp" "Interfaces/*.h"
    "Log/*.cpp" "Log/*.h"
    "Task/*.cpp" "Task/*.h"
    "Memory/*.cpp" "Memory/*.h"
	"Events/*.cpp" "Events/*.h"
	"Hash/*.cpp" "Hash/*.h")

if(WIN32)
    file(GLOB PLATFORM_FILES "Platforms/Win/*.cpp" "Platforms/Win/*.h")
elseif(UNIX)
    file(GLOB PLATFORM_FILES "Platforms/Linux/*.cpp" "Platforms/Linux/*.h")
endif()

find_package(OpenCL REQUIRED)

ADD_LIBRARY(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${PLATFORM_FILES})

TARGET_LINK_LIBRARIES(${PROJECT_NAME} xxhash Qt5::Core OpenCL::OpenCL)

include(GenerateExportHeader)
string(TOUPPER "${PROJECT_NAME}_EXPORT" EXPORT_NAME)
GENERATE_EXPORT_HEADER(${PROJECT_NAME} EXPORT_MACRO_NAME ${EXPORT_NAME} EXPORT_FILE_NAME ${CMAKE_BINARY_DIR}/exports/${PROJECT_NAME}_export.h)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_BINARY_DIR}/exports)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin/Logs)

set(_src_root_path ${CMAKE_CURRENT_SOURCE_DIR})

file(
    GLOB_RECURSE _source_list
    LIST_DIRECTORIES false
    "${_src_root_path}/*.c*"
    "${_src_root_path}/*.h*"
    )

foreach(_source IN ITEMS ${_source_list})
    get_filename_component(_source_path "${_source}" PATH)
    file(RELATIVE_PATH _source_path_rel "${_src_root_path}" "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()
