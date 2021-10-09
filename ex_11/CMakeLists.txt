cmake_minimum_required(VERSION 3.15)

project(ex_11 LANGUAGES CXX)

add_executable(${PROJECT_NAME}
  stb_image.h
  utils.h
  utils.cpp
  main.cpp
  shader.fs
  shader.vs
  README.md
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    freeglut
    glew
    glm
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/shader.fs
    ${CMAKE_CURRENT_SOURCE_DIR}/shader.vs
    ${CMAKE_CURRENT_SOURCE_DIR}/box.png
    ${CMAKE_CURRENT_BINARY_DIR}
)