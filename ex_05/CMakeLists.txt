cmake_minimum_required(VERSION 3.15)

set(TARGET ex_05)

project(${TARGET})

add_executable(${TARGET}
  utils.h
  utils.cpp
  main.cpp
  shader.fs
  shader.vs
)

target_link_libraries(${TARGET}
  PRIVATE
    freeglut
    glew
)

add_custom_command(TARGET ${TARGET} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/shader.fs
    ${CMAKE_CURRENT_SOURCE_DIR}/shader.vs
    ${CMAKE_CURRENT_BINARY_DIR}
)