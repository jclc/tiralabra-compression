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

	set(TESTOUTPUT
		tests/testoutput.cpp
		tests/testoutput.hpp)

	include_directories(${GTEST_INCLUDE_DIRS})

	add_executable(testoutputtest
		${TESTOUTPUT}
		tests/testoutputtest.cpp)

	add_executable(inputtest
		${TESTOUTPUT}
		src/input.cpp
		tests/inputtest.cpp)

	target_link_libraries(testoutputtest ${GTEST_BOTH_LIBRARIES})
	add_test(NAME TestOutputTest COMMAND testoutputtest
		WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test-resources")

	target_link_libraries(inputtest ${GTEST_BOTH_LIBRARIES})
	add_test(NAME InputTest COMMAND inputtest
		WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test-resources")
endif()
