cmake_minimum_required(VERSION 2.6)

project(nginx-lua-ahocorasick)

if (WIN32)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /wd4996 /wd4805")
endif()

file(GLOB src_dirs *.cpp *.c *.h)

set(ahocorasick_STAT_SRCS
   ${src_dirs}
)

include_directories(
   ${CMAKE_CURRENT_SOURCE_DIR}/
)

add_library(ahocorasick SHARED ${ahocorasick_STAT_SRCS})
#add_executable(ahocorasick ${ahocorasick_STAT_SRCS})
SET_TARGET_PROPERTIES(ahocorasick PROPERTIES LINKER_LANGUAGE C)

