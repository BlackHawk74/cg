cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(exam)

add_executable(exam_1801 exam_1801.cpp)
target_link_libraries(exam_1801 visualization ${GMP_LIBRARIES})

add_executable(exam_2401 exam_2401.cpp)
target_link_libraries(exam_2401 visualization ${GMP_LIBRARIES})

add_executable(exam_2401_2 exam_2401_2.cpp)
target_link_libraries(exam_2401_2 visualization ${GMP_LIBRARIES})

add_executable(exam_0102 exam_0102.cpp)
target_link_libraries(exam_0102 visualization ${GMP_LIBRARIES})
