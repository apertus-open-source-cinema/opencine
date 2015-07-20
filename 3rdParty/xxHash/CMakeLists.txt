CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(xxHash)

CMAKE_POLICY(SET CMP0020 NEW)

add_library(${PROJECT_NAME} STATIC xxhash.c)

# was meant for Windows, but not required at the moment, lib is found despite ".a" extension
#set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".lib")
	