
# Define project properties
cmake_minimum_required(VERSION 3.10)
project(kdtree-cpp VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)

# Add library
add_library(kdtree STATIC 
${CMAKE_SOURCE_DIR}/src/kdtree.cpp
${CMAKE_SOURCE_DIR}/src/kdtree.hpp
${CMAKE_SOURCE_DIR}/src/point.cpp
${CMAKE_SOURCE_DIR}/src/point.hpp
${CMAKE_SOURCE_DIR}/src/aabb.cpp
${CMAKE_SOURCE_DIR}/src/aabb.hpp
)
target_include_directories(kdtree PRIVATE "${PROJECT_SOURCE_DIR}/src")

# Add main executable
add_executable(kdtree-cpp main.cpp)

# Link libraries to executable
target_link_libraries(kdtree-cpp PRIVATE kdtree)
