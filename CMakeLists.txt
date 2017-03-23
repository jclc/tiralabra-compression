cmake_minimum_required(VERSION 2.8)
project("tl-compression")

option(MAKE_TESTS "Enable unit tests" ON)

include_directories("include")

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
	include_directories(${GTEST_INCLUDE_DIRS})
	add_executable(testtest tests/testtest.cpp)
	target_link_libraries(testtest ${GTEST_BOTH_LIBRARIES})
	add_test(TestTest testtest)
endif()
