CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
PROJECT(MemoryPool)

CMAKE_POLICY(SET CMP0020 NEW)

set(MemoryPool_SOURCES "${MemoryPool_SOURCE_DIR}/C-11/MemoryPool.h" "${MemoryPool_SOURCE_DIR}/C-11/MemoryPool.tcc")

add_library(${PROJECT_NAME} STATIC ${MemoryPool_SOURCES})

set_target_properties(MemoryPool PROPERTIES LINKER_LANGUAGE CXX)

# was meant for Windows, but not required at the moment, lib is found despite ".a" extension
#set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".lib")
	