enable_testing()
find_package(GTest REQUIRED)
# Defines the following:
# GTEST_FOUND - Found the Google Testing framework
# GTEST_INCLUDE_DIRS - Include directories
# GTEST_BOTH_LIBRARIES - Both libgtest & libgtest-main
# GTEST_LIBRARIES - libgtest
# GTEST_MAIN_LIBRARIES - libgtest-main

set(TESTOUTPUT
	../src/testoutput.cpp
	../include/testoutput.hpp)

include_directories(${GTEST_INCLUDE_DIRS})


### Unit tests

# TestOutput

add_executable(testoutputtest
	testoutputtest.cpp
	${TESTOUTPUT})

target_link_libraries(testoutputtest ${GTEST_BOTH_LIBRARIES})
add_test(NAME TestOutputTest COMMAND testoutputtest
	WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test-resources")


# Input

add_executable(inputtest
	inputtest.cpp
	../src/input.cpp
	${TESTOUTPUT})

target_link_libraries(inputtest ${GTEST_BOTH_LIBRARIES})
add_test(NAME InputTest COMMAND inputtest
	WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test-resources")


# Output

add_executable(outputtest
	outputtest.cpp
	../src/output.cpp)

target_link_libraries(outputtest ${GTEST_BOTH_LIBRARIES})
add_test(NAME OutputTest COMMAND outputtest
	WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test-resources")


# BitBuffer

add_executable(bitbuffertest
	bitbuffertest.cpp
	../include/bitbuffer.hpp)

target_link_libraries(bitbuffertest ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
add_test(NAME BitBufferTest COMMAND bitbuffertest
	WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test-resources")


# StringTable

add_executable(stringtabletest
	stringtabletest.cpp)

target_link_libraries(stringtabletest ${GTEST_BOTH_LIBRARIES})
add_test(NAME StringTableTest COMMAND stringtabletest
	WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test-resources")


# Encoder

add_executable(encodertest
	encodertest.cpp
	../src/encoder.cpp
	../src/input.cpp
	../src/output.cpp
	../src/progressbar.cpp
	${TESTOUTPUT})

target_link_libraries(encodertest ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
add_test(NAME EncoderTest COMMAND encodertest
	WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test-resources")
