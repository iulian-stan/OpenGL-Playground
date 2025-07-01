cmake_minimum_required(VERSION 3.15)

project(project11 LANGUAGES CXX)

add_executable(${PROJECT_NAME}
  stb_image.h
  utils.h
  utils.cpp
  main.cpp
  shader11.fs
  shader11.vs
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
    ${CMAKE_CURRENT_SOURCE_DIR}/shader11.fs
    ${CMAKE_CURRENT_SOURCE_DIR}/shader11.vs
    ${CMAKE_CURRENT_SOURCE_DIR}/box.png
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
)