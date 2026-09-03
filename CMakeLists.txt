cmake_minimum_required(VERSION 3.15)
project(transformable_pebble_sorting_rover)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
set(SOURCES
    src/main.cpp
    src/motors.cpp
    src/arm.cpp
    src/gripper.cpp
    src/sorter.cpp
    src/transformation.cpp
)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})
