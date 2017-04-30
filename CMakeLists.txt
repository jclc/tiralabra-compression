cmake_minimum_required(VERSION 3.1)
project("tiralabra-compression")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)
set(EXENAME "tiracomp")

option(MAKE_TESTS "Enable unit tests" ON)

if(WIN32)
	# This preprocessor define should prevent a name clash with Windows API
	add_definitions(-DNOMINMAX)
endif()

#if(CMAKE_COMPILER_IS_GNUCXX)
#	option(COVERAGE "Compile with code coverage options" OFF)
#	if (COVERAGE)
#		SET(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
#	endif()
#endif()

find_package(Threads REQUIRED)
include_directories(include)

set(SOURCES
	src/main.cpp
	src/input.cpp
	src/output.cpp
	src/encoder.cpp
	src/decoder.cpp
	src/progressbar.cpp
	src/tempfilenames.cpp
	)

set(HEADERS
	include/input.hpp
	include/output.hpp
	include/encoder.hpp
	include/decoder.hpp
	include/progressbar.hpp
	include/bitbuffer.hpp
	include/stringtable.hpp
	include/common.hpp
	include/tempfilenames.hpp
	)


add_executable(${EXENAME} ${SOURCES} ${HEADERS})
target_link_libraries(${EXENAME} ${CMAKE_THREAD_LIBS_INIT})

if(MAKE_TESTS)
	add_subdirectory(tests)
endif()
