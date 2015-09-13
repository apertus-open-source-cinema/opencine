cmake_minimum_required(VERSION 2.8)
PROJECT(OCBackup)

CMAKE_POLICY(SET CMP0020 NEW)

set( CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

FIND_PACKAGE(Qt5Widgets REQUIRED)
FIND_PACKAGE(Qt5QuickWidgets REQUIRED)

FILE(GLOB SOURCE_FILES "*.cpp" "*.h"
                       "Views/*.cpp" "Views/*.h"
                       "Interfaces/*.cpp" "Interfaces/*.h"
                       "Presenters/*.cpp" "Presenters/*.h"
                       "Data/*.cpp" "Data/*.h")
FILE(GLOB UI_FILES "Views/*.ui")
FILE(GLOB QML_FILES "Widgets/*.qml")

QT5_WRAP_UI(UI_FILES_MOC ${UI_FILES})

INCLUDE_DIRECTORIES("${OCui_SOURCE_DIR}")
INCLUDE_DIRECTORIES("${OCCore_SOURCE_DIR}")

IF(WIN32)
    ADD_EXECUTABLE(${PROJECT_NAME} WIN32 ${SOURCE_FILES} ${UI_FILES_MOC} ${QML_FILES})
ELSE(UNIX)
    ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCE_FILES} ${UI_FILES_MOC} ${QML_FILES})
ENDIF()

TARGET_LINK_LIBRARIES(${PROJECT_NAME} OCCore OCui xxHash)

QT5_USE_MODULES(${PROJECT_NAME} Widgets QuickWidgets)

FILE(COPY "Widgets" DESTINATION ${CMAKE_BINARY_DIR}/bin)
