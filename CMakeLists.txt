cmake_minimum_required(VERSION 2.8.4)
project(midi2gba)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(HEADER_FILES globals.h path.h sfile.h midi.h utils.h)
set(SOURCE_FILES ${HEADER_FILES} main.c path.c globals.c sfile.c unused.c midi.c utils.c)
add_executable(midi2gba ${SOURCE_FILES})