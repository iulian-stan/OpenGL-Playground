cmake_minimum_required(VERSION 3.15)

set(TARGET ex_04)

project(${TARGET})

add_executable(${TARGET}
  main.cpp
)

target_link_libraries(${TARGET}
  PRIVATE
    freeglut
    glew
)