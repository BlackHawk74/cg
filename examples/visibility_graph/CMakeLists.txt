cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(visibility_graph-example)

add_executable(visibility_graph visibility_graph.cpp)
target_link_libraries(visibility_graph visualization ${GMP_LIBRARIES})
