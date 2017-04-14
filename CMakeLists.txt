cmake_minimum_required(VERSION 3.1)
project("tiralabra-compression")
set(CMAKE_CXX_STANDARD 11)

set(EXENAME "tiracomp")

option(MAKE_TESTS "Enable unit tests" ON)

if(WIN32)
	# This preprocessor define should prevent a name clash with Windows API
	add_definitions(-DNOMINMAX)
endif()

include_directories(include)

set(SOURCES
	src/main.cpp
	src/input.cpp
	src/output.cpp
	src/encoder.cpp
	src/decoder.cpp)

set(HEADERS
	include/input.hpp
	include/output.hpp
	include/encoder.hpp
	include/decoder.hpp
	include/bitbuffer.hpp
	include/stringtable.hpp)

add_executable(${EXENAME} ${SOURCES} ${HEADERS})

if(MAKE_TESTS)
	add_subdirectory(tests)
endif()
