cmake_minimum_required(VERSION 3.2)
PROJECT(OCCore)

CMAKE_POLICY(SET CMP0020 NEW)

set( CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

FIND_PACKAGE(Qt5Core REQUIRED)
FIND_PACKAGE(Qt5Widgets REQUIRED)

file(GLOB SOURCE_FILES "*.cpp" "*.h"
                       "Transfer/*.cpp" "Transfer/*.h"
                       "MVP/*.cpp" "MVP/*.h"
                       "API/*.cpp" "API/*.h"
                       "Image/*.cpp" "Image/*.h"
                       "Interfaces/*.cpp" "Interfaces/*.h"
                       "Log/*.cpp" "Log/*.h"
						"Task/*.cpp" "Task/*.h")

#file(GLOB HEADER_FILES "*.h")

#include_directories(${PROJECT_SOURCE_DIR})

if(WIN32)
    file(GLOB PLATFORM_FILES "Platforms/Win/*.cpp" "Platforms/Win/*.h")
    #file(GLOB HEADER_FILES "Platforms/Win")
elseif(UNIX)
    file(GLOB PLATFORM_FILES "Platforms/Linux/*.cpp" "Platforms/Linux/*.h")
    #file(GLOB HEADER_FILES "Platforms/Linux")
endif()

#SET(INCLUDE_DIRS "")
#foreach (_headerFile ${HEADER_FILES})
    #get_filename_component(_dir ${_headerFile} PATH)
    #list (APPEND INCLUDE_DIRS ${_dir})
#endforeach()
#list(REMOVE_DUPLICATES INCLUDE_DIRS)

ADD_LIBRARY(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${PLATFORM_FILES})

#set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "OCCore")

include(GenerateExportHeader)
string(TOUPPER "${PROJECT_NAME}_EXPORT" EXPORT_NAME)
GENERATE_EXPORT_HEADER(${PROJECT_NAME} EXPORT_MACRO_NAME ${EXPORT_NAME} EXPORT_FILE_NAME ${CMAKE_BINARY_DIR}/exports/${PROJECT_NAME}_export.h)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_BINARY_DIR}/exports)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin/Logs)

QT5_USE_MODULES(${PROJECT_NAME} Core Widgets)

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