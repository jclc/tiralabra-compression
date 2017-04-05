cmake_minimum_required(VERSION 3.1)
project("tl-compression")
set(CMAKE_CXX_STANDARD 11)

option(MAKE_TESTS "Enable unit tests" ON)

include_directories(include)

set(SOURCES
	src/main.cpp
	src/input.cpp
	src/output.cpp)

set(HEADERS
	include/input.hpp
	include/output.hpp)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

if(MAKE_TESTS)
	add_subdirectory(tests)
endif()
