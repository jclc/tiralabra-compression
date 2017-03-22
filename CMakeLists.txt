cmake_minimum_required(VERSION 2.8)
project("tl-compression")

include_directories(src)

set(SOURCES
	src/main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
