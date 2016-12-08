cmake_minimum_required(VERSION 2.6)

project(ahocorasick)

if (WIN32)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /wd4996 /wd4805")
endif()

file(GLOB src_dirs *.c *.h)

set(ahocorasick_STAT_SRCS
   ${src_dirs}   
)

include_directories(
   ${CMAKE_CURRENT_SOURCE_DIR}/  
)

add_library(ahocorasick STATIC ${ahocorasick_STAT_SRCS})
SET_TARGET_PROPERTIES(ahocorasick PROPERTIES LINKER_LANGUAGE C)
 