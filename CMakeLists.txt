cmake_minimum_required(VERSION 3.15)

project(OpenGL_Exercise)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/bin)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib)

# Adding dependencies
add_subdirectory(dependencies)

# Adding tutorials
add_subdirectory(project01)
add_subdirectory(project02)
add_subdirectory(project03)
add_subdirectory(project04)
add_subdirectory(project05)
add_subdirectory(project06)
add_subdirectory(project07)
add_subdirectory(project08)
add_subdirectory(project09)
add_subdirectory(project10)
add_subdirectory(project11)
