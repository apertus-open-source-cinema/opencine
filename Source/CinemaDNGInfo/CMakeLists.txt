cmake_minimum_required(VERSION 2.8)
PROJECT(CinemaDNGInfo)

#FIND_PACKAGE(LibRaw REQUIRED)

FILE(GLOB SOURCE_FILES *.cpp)
FILE(GLOB HEADER_FSILES *.h)

ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  TARGET_LINK_LIBRARIES(${PROJECT_NAME} CinemaDNGDecoder
                        /home/andi/Source/OpenCine/build/lib/libraw.so)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
endif()
