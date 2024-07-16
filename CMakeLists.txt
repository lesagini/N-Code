cmake_minimum_required(VERSION 3.10)
project(N-Code)

set(CMAKE_CXX_STANDARD 17)

# Source files
file(GLOB SOURCES "src/*.cpp")

# Executable
add_executable(N-Code ${SOURCES})

