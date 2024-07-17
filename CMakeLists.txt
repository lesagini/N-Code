cmake_minimum_required(VERSION 3.10)
project(N-Code)

set(CMAKE_CXX_STANDARD 17)

# Set the output directory for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

list(FILTER SOURCES EXCLUDE REGEX "src/main.cpp")

add_executable(N-Code src/main.cpp ${SOURCES})

enable_testing()

file(GLOB TEST_SOURCES "tests/*.cpp")
list(REMOVE_ITEM TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/tests/test_main.cpp") 

add_executable(runTests tests/test_main.cpp ${TEST_SOURCES} ${SOURCES})

# Include doctest
include_directories(third_party/doctest)

add_test(NAME ParserTest COMMAND runTests)
