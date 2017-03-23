cmake_minimum_required(VERSION 2.8)
project("tl-compression")

include_directories("include")

set(SOURCES
	src/main.cpp)

set(HEADERS
	include/input.hpp
	include/output.hpp)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
