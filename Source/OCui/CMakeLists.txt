# Copyright (c) 2017 apertus° Association & contributors
# Project: OpenCine / OCui
# License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

cmake_minimum_required(VERSION 3.5)
PROJECT(OCui)

CMAKE_POLICY(SET CMP0020 NEW)

set( CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

FIND_PACKAGE(Qt5 COMPONENTS Quick QuickWidgets Widgets REQUIRED)

FILE(GLOB_RECURSE SOURCE_FILES "*.cpp")
FILE(GLOB_RECURSE HEADER_FILES "*.h")
FILE(GLOB_RECURSE UI_FILES "*.ui")
FILE(GLOB_RECURSE QML_FILES "*.qml")

QT5_WRAP_UI(UI_FILES_MOC ${UI_FILES})

INCLUDE_DIRECTORIES("${OCcore_SOURCE_DIR}")

ADD_LIBRARY(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${HEADER_FILES} ${UI_FILES_MOC} ${QML_FILES})

#ExternalProject_Get_Property(QtAV_project BINARY_DIR)

#message(STATUS "QtAV: ${QTAV_LIB}")
#message(STATUS "QtAVWidgets: ${QTAVWIDGETS_LIB}")

message(WARNING "QtAV BINARY_DIR: ${BINARY_DIR}")
#LINK_DIRECTORIES(${BINARY_DIR}/lib/)

#add_dependencies(${PROJECT_NAME} QtAV_project)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} OCcore Qt5::Widgets Qt5::Quick Qt5::QuickWidgets) #${BINARY_DIR}/lib/libQtAV.so ${BINARY_DIR}/lib/libQtAVWidgets.so)

include(GenerateExportHeader)
string(TOUPPER "${PROJECT_NAME}_EXPORT" EXPORT_NAME)
GENERATE_EXPORT_HEADER(${PROJECT_NAME} EXPORT_MACRO_NAME ${EXPORT_NAME} EXPORT_FILE_NAME ${CMAKE_BINARY_DIR}/exports/${PROJECT_NAME}_export.h)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_BINARY_DIR}/exports)

FILE(COPY "Themes" DESTINATION ${CMAKE_BINARY_DIR}/bin)
FILE(COPY "Resources" DESTINATION ${CMAKE_BINARY_DIR}/bin)
FILE(COPY "Fonts" DESTINATION ${CMAKE_BINARY_DIR}/bin)

set(_src_root_path ${CMAKE_CURRENT_SOURCE_DIR})

file(
    GLOB_RECURSE _source_list
    LIST_DIRECTORIES false
    "${_src_root_path}/*.c*"
    "${_src_root_path}/*.h*"
    "${_src_root_path}/*.ui*"
    )

foreach(_source IN ITEMS ${_source_list})
    get_filename_component(_source_path "${_source}" PATH)
    file(RELATIVE_PATH _source_path_rel "${_src_root_path}" "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()
