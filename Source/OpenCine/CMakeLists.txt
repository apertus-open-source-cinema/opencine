cmake_minimum_required(VERSION 2.8.11)
PROJECT(OpenCine)

set( CMAKE_VERBOSE_MAKEFILE on )

set(CMAKE_AUTOMOC TRUE)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -O0")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage -O0")

FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(Qt5Core REQUIRED)
FIND_PACKAGE(Qt5Widgets REQUIRED)
FIND_PACKAGE(Qt5QuickWidgets REQUIRED)
FIND_PACKAGE(Qt5OpenGL REQUIRED)

#find_library(AVUTIL_LIB "avutil-ffmpeg")
#if(AVUTIL_LIB)
#  message(STATUS "Found: avutil -> " ${AVUTIL_LIB})
#else()
#  message(STATUS "Not found: avutil")
#endif()

#find_library(AVFORMAT_LIB "avformat-ffmpeg")
#if(AVFORMAT_LIB)
#  message(STATUS "Found: avformat -> " ${AVFORMAT_LIB})
#else()
#  message(STATUS "Not found: avformat")
#endif()

#find_library(AVCODEC_LIB "avcodec-ffmpeg")
#if(AVCODEC_LIB)
#  message(STATUS "Found: avcodec -> " ${AVCODEC_LIB})
#else()
#  message(STATUS "Not found: avcodec")
#endif()

#find_library(OPENCL_LIB "libOpenCL.so.1")
#if(OPENCL_LIB)
#  message(STATUS "Found: OpenCL -> " ${OPENCL_LIB})
#else()
#  message(STATUS "Not found: OpenCL")
#endif()

#find_library(LIBJPEG_LIB "libjpeg.so")
#if(LIBJPEG_LIB)
#  message(STATUS "Found: libjpeg8 -> " ${LIBJPEG_LIB})
#else()
#  message(STATUS "Not found: libjpeg8")
#endif()

INCLUDE_DIRECTORIES(${Qt5Widgets_INCLUDES})
INCLUDE_DIRECTORIES(${Qt5QuickWidgets_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${Qt5OpenGL_INCLUDE_DIRS})

#FILE(GLOB SOURCE_FILES *.cpp)
#FILE(GLOB HEADER_FILES *.h)
FILE(GLOB_RECURSE UI_FILES "*.ui")
FILE(GLOB_RECURSE RESOURCE_FILES "*.qrc")

file(GLOB_RECURSE SOURCE_FILES "*.cpp")
file(GLOB_RECURSE HEADER_FILES "*.h")

SET(INCLUDE_DIRS "")
foreach (_headerFile ${HEADER_FILES})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES INCLUDE_DIRS)

include_directories(${INCLUDE_DIRS})

#Add source from subfolders
#LINK_DIRECTORIES(DataProvider)
#file(GLOB SOURCE_FILES "./DataStorage/*.cpp")

FILE(COPY "Themes" DESTINATION ${CMAKE_BINARY_DIR}/bin)
FILE(COPY "Icons" DESTINATION ${CMAKE_BINARY_DIR}/bin)
FILE(COPY "Widgets" DESTINATION ${CMAKE_BINARY_DIR}/bin)

QT5_WRAP_UI(UI_FILES_MOC ${UI_FILES})
#QT5_WRAP_CPP(SOURCE_MOC ${SOURCE_FILES})
QT5_ADD_RESOURCES(UI_RESOURCES ${RESOURCE_FILES})



if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCE_FILES} ${UI_FILES_MOC} ${SOURCE_MOC} ${UI_RESOURCES})

	TARGET_LINK_LIBRARIES(
    ${PROJECT_NAME}
    ${QT_QTMAIN_LIBRARY}
    ${QT_LIBRARIES}
    ${OPENGL_LIBRARIES}
    "${CMAKE_BINARY_DIR}/lib/libraw.so"
    gcov
    #"${AVUTIL_LIB}"
    #"${AVFORMAT_LIB}"
    #"${AVCODEC_LIB}"
    #"${OPENCL_LIB}"
    #"${LIBJPEG_LIB}"
    pthread
  )

elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")

	ADD_EXECUTABLE(${PROJECT_NAME} WIN32 ${SOURCE_FILES} ${UI_FILES_MOC} ${SOURCE_MOC} ${UI_RESOURCES})

	TARGET_LINK_LIBRARIES(
    ${PROJECT_NAME}
	#Qt5::WinMain
    #${Qt5Core_QTMAIN_LIBRARIES}
    #${QT_LIBRARIES}
    ${OPENGL_LIBRARIES}
	"${CMAKE_BINARY_DIR}/bin/libraw.dll"
    #"${AVUTIL_LIB}"
    #"${AVFORMAT_LIB}"
    #"${AVCODEC_LIB}"
    #"${OPENCL_LIB}"
    #"${LIBJPEG_LIB}"
    #pthread
  )



	#ADD_EXECUTABLE(${PROJECT_NAME} WIN32 ${SOURCE_FILES} ${HEADER_FILES} ${UI_FILES_MOC} ${HEADERS_MOC} ${RESOURCE_FILES} )

	#INCLUDE(BundleUtilities)
	#fixup_bundle(${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.exe ""  $ENV{CMAKE_PREFIX_PATH})

	#Source: http://www.cmake.org/Wiki/CMake/Tutorials/Qt
	if(MSVC) # Check if we are using the Visual Studio compiler
		SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:windows")
		SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup")
	elseif(CMAKE_COMPILER_IS_GNUCXX)
		# SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows") # Not tested
	else()
		message(SEND_ERROR "You are using an unsupported Windows compiler! (Not MSVC or GCC)")
	endif()
endif()

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

QT5_USE_MODULES(${PROJECT_NAME} Widgets QuickWidgets OpenGL)
