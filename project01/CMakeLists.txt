cmake_minimum_required(VERSION 3.15)

project(project01 LANGUAGES CXX)

add_executable(${PROJECT_NAME}
  main.cpp
  README.md
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    freeglut
)