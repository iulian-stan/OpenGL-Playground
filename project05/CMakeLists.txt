cmake_minimum_required(VERSION 3.15)

project(project05 LANGUAGES CXX)

add_executable(${PROJECT_NAME}
  utils.h
  utils.cpp
  main.cpp
  shader05.fs
  shader05.vs
  README.md
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    freeglut
    glew
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/shader05.fs
    ${CMAKE_CURRENT_SOURCE_DIR}/shader05.vs
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
)