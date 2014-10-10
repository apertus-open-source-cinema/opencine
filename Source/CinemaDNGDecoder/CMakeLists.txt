cmake_minimum_required(VERSION 2.8)
PROJECT(CinemaDNGDecoder)

#FIND_PACKAGE(Qt5 REQUIRED)
#FIND_PACKAGE(Qt5Widgets)
#FIND_PACKAGE(Qt5Declarative)
#find_package(Qt5 COMPONENTS Widgets Declarative)
#INCLUDE(${QT_USE_FILE})

#QT5_WRAP_UI(UISrcs MyWidget.ui)
#QT5_WRAP_CPP(MOCSrcs MyWidget.h)

#include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

ADD_LIBRARY(${PROJECT_NAME} Main.cpp) # MyWidget.cpp ${MOCSrcs} ${UISrcs})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${QT_LIBRARIES})
