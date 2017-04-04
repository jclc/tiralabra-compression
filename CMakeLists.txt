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
	enable_testing()
	find_package(GTest REQUIRED)
	# Defines the following:
	# GTEST_FOUND - Found the Google Testing framework
	# GTEST_INCLUDE_DIRS - Include directories
	# GTEST_BOTH_LIBRARIES - Both libgtest & libgtest-main
	# GTEST_LIBRARIES - libgtest
	# GTEST_MAIN_LIBRARIES - libgtest-main

	set(TESTOUTPUT
		src/testoutput.cpp
		include/testoutput.hpp)

	include_directories(${GTEST_INCLUDE_DIRS})

	# Unit tests

	add_executable(testoutputtest
		tests/testoutputtest.cpp
		${TESTOUTPUT})

	target_link_libraries(testoutputtest ${GTEST_BOTH_LIBRARIES})
	add_test(NAME TestOutputTest COMMAND testoutputtest
		WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test-resources")

	add_executable(inputtest
		tests/inputtest.cpp
		src/input.cpp
		${TESTOUTPUT})

	target_link_libraries(inputtest ${GTEST_BOTH_LIBRARIES})
	add_test(NAME InputTest COMMAND inputtest
		WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test-resources")

	add_executable(outputtest
		tests/outputtest.cpp
		src/output.cpp)

	target_link_libraries(outputtest ${GTEST_BOTH_LIBRARIES})
	add_test(NAME OutputTest COMMAND outputtest
		WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test-resources")
endif()
