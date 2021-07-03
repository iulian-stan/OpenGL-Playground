cmake_minimum_required(VERSION 3.15)

project(OpenGL_Exercise)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/bin)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib)

# Adding dependencies
add_subdirectory(deps)

# Adding tutorials
add_subdirectory(ex_01)
add_subdirectory(ex_02)
add_subdirectory(ex_03)
add_subdirectory(ex_04)
add_subdirectory(ex_04.5)
add_subdirectory(ex_05)
add_subdirectory(ex_05.5)
add_subdirectory(ex_06)
add_subdirectory(ex_06.5)
add_subdirectory(ex_07)
add_subdirectory(ex_07.5)
