cmake_minimum_required(VERSION 3.2)
PROJECT(ProcessingTest)

CMAKE_POLICY(SET CMP0020 NEW)
CMAKE_POLICY(SET CMP0063 NEW)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

FIND_PACKAGE(Qt5Widgets REQUIRED)
FIND_PACKAGE(Qt5QuickWidgets REQUIRED)
FIND_PACKAGE(Qt5OpenGL REQUIRED)

FILE(GLOB SOURCE_FILES "*.cpp" "*.h" "*.hpp"
                       "Views/*.cpp" "Views/*.h"
                       "Interfaces/*.cpp" "Interfaces/*.h"
                       "Presenters/*.cpp" "Presenters/*.h"
                       "Controls/*.cpp" "Controls/*.h")

FILE(GLOB UI_FILES "Views/*.ui" "Controls/*.ui")
#FILE(GLOB QML_FILES "Widgets/*.qml")

QT5_WRAP_UI(UI_FILES_MOC ${UI_FILES})

INCLUDE_DIRECTORIES("${OCui_SOURCE_DIR}")
INCLUDE_DIRECTORIES("${OCCore_SOURCE_DIR}")

IF(WIN32)
    ADD_EXECUTABLE(${PROJECT_NAME} WIN32 ${SOURCE_FILES} ${UI_FILES_MOC} ${QML_FILES})
ELSE(UNIX)
    ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCE_FILES} ${UI_FILES_MOC} ${QML_FILES})
ENDIF()

TARGET_LINK_LIBRARIES(${PROJECT_NAME} -lpthread OCCore OCui)

QT5_USE_MODULES(${PROJECT_NAME} Widgets OpenGL QuickWidgets)

#FILE(COPY "Widgets" DESTINATION ${CMAKE_BINARY_DIR}/bin)
FILE(COPY "Shaders" DESTINATION ${CMAKE_BINARY_DIR}/bin)
FILE(COPY axiom.raw12 DESTINATION ${CMAKE_BINARY_DIR}/bin)
