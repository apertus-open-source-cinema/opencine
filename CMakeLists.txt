cmake_minimum_required(VERSION 2.8)
project(ApertusOpenCine)

#TODO: Enable C++11 support for all projects. Adjust when porting to windows (e.g. for Visual Studio compatibility)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")

if(WIN32)
	ADD_DEFINITIONS(-DWIN32)
endif()

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#Force to output to /bin and /lib on Windows, without additional "Debug" and "Release" folder
#Source: http://stackoverflow.com/questions/543203/cmake-runtime-output-directory-on-windows
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
SET( CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
SET( CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

#Includes
include_directories("${PROJECT_SOURCE_DIR}/3rdParty/LibRaw")
include_directories("${PROJECT_SOURCE_DIR}/3rdParty/Catch")
include_directories("${PROJECT_SOURCE_DIR}/3rdParty/POCO/Foundation/include")
#include_directories("${PROJECT_SOURCE_DIR}/3rdParty/RawSpeed/include")

#Dependencies
SET(ENABLE_EXAMPLES OFF CACHE BOOL "LibRaw: Build shared library (without examples)")
add_subdirectory(${PROJECT_SOURCE_DIR}/3rdParty/LibRaw)

SET(ENABLE_DATA OFF CACHE BOOL "POCO: Disable Data")
SET(ENABLE_DATA_MYSQL OFF CACHE BOOL "POCO: Disable MySQL")
SET(ENABLE_DATA_ODBC OFF CACHE BOOL "POCO: Disable ODBC")
SET(ENABLE_DATA_SQLITE OFF CACHE BOOL "POCO: Disable SQLite")
SET(ENABLE_CRYPTO OFF CACHE BOOL "POCO: Disable Crypto")
SET(ENABLE_JSON OFF CACHE BOOL "POCO: Disable JSON")
SET(ENABLE_NET OFF CACHE BOOL "POCO: Disable Net")
SET(ENABLE_NETSSL OFF CACHE BOOL "POCO: Disable SSL")
SET(ENABLE_MONGODB OFF CACHE BOOL "POCO: Disable MongoDB")
SET(ENABLE_UTIL OFF CACHE BOOL "POCO: Disable Util")
SET(ENABLE_XML OFF CACHE BOOL "POCO: Disable XML")
SET(ENABLE_ZIP OFF CACHE BOOL "POCO: Disable Zip")
SET(ENABLE_PAGECOMPILER OFF CACHE BOOL "POCO: Disable PageCompiler")
SET(ENABLE_PAGECOMPILER_FILE2PAGE OFF CACHE BOOL "POCO: Disable PageCompiler File2Page")
SET(POCO_STATIC ON CACHE BOOL "POCO: Static build")
add_subdirectory(${PROJECT_SOURCE_DIR}/3rdParty/POCO)

#Projects
add_subdirectory(${PROJECT_SOURCE_DIR}/Source/OpenCine/)
#add_subdirectory(${PROJECT_SOURCE_DIR}/Source/CinemaDNGDecoder/)
#add_subdirectory(${PROJECT_SOURCE_DIR}/Source/CinemaDNGInfo/)
