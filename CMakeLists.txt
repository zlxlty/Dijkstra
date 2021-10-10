cmake_minimum_required(VERSION 3.16.3)

project(Dijkstra)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

add_subdirectory(Heap)
add_subdirectory(Graph)

add_executable(${PROJECT_NAME} main.c)

target_link_libraries(${PROJECT_NAME} heap graph)