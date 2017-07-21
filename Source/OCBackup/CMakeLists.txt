// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCBackup
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

cmake_minimum_required(VERSION 3.5)
PROJECT(OCBackup)

CMAKE_POLICY(SET CMP0020 NEW)

set( CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

FIND_PACKAGE(Qt5Widgets REQUIRED)
FIND_PACKAGE(Qt5QuickWidgets REQUIRED)
FIND_PACKAGE(Qt5Concurrent REQUIRED)

FILE(GLOB SOURCE_FILES "*.cpp" "*.h"
    "Views/*.cpp" "Views/*.h"
    "Interfaces/*.cpp" "Interfaces/*.h"
    "Presenters/*.cpp" "Presenters/*.h"
    "Data/*.cpp" "Data/*.h"
    "Controls/*.cpp" "Controls/*.h"
    "Services/*.cpp" "Services/*.h")

FILE(GLOB UI_FILES "Views/*.ui" "Controls/*.ui")
FILE(GLOB QML_FILES "Widgets/*.qml")

QT5_WRAP_UI(UI_FILES_MOC ${UI_FILES})

INCLUDE_DIRECTORIES(${OCui_SOURCE_DIR})
INCLUDE_DIRECTORIES(${OCCore_SOURCE_DIR})

IF(WIN32)
ADD_EXECUTABLE(${PROJECT_NAME} WIN32 ${SOURCE_FILES} ${UI_FILES_MOC} ${QML_FILES})
ELSE(UNIX)
ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCE_FILES} ${UI_FILES_MOC} ${QML_FILES})
ENDIF()

TARGET_LINK_LIBRARIES(${PROJECT_NAME} OCCore OCui)

QT5_USE_MODULES(${PROJECT_NAME} Widgets QuickWidgets Concurrent)

FILE(COPY "Widgets" DESTINATION ${CMAKE_BINARY_DIR}/bin)

#set_property( GLOBAL PROPERTY USE_FOLDERS ON)

set(_src_root_path ${CMAKE_CURRENT_SOURCE_DIR})

file(
    GLOB_RECURSE _source_list
    LIST_DIRECTORIES false
    "${_src_root_path}/*.c*"
    "${_src_root_path}/*.h*"
    "${_src_root_path}/*.ui"
    "${_src_root_path}/*.qml"
    )

foreach(_source IN ITEMS ${_source_list})
    get_filename_component(_source_path "${_source}" PATH)
    file(RELATIVE_PATH _source_path_rel "${_src_root_path}" "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()
