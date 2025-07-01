cmake_minimum_required(VERSION 3.15)

project(project12 LANGUAGES CXX)

add_executable(${PROJECT_NAME}
  stb_image.h
  utils.h
  utils.cpp
  main.cpp
  shader12.fs
  shader12.vs
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
    ${CMAKE_CURRENT_SOURCE_DIR}/shader12.fs
    ${CMAKE_CURRENT_SOURCE_DIR}/shader12.vs
    ${CMAKE_CURRENT_SOURCE_DIR}/box.png
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
)