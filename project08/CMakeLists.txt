cmake_minimum_required(VERSION 3.15)

project(project08 LANGUAGES CXX)

add_executable(${PROJECT_NAME}
  stb_image.h
  utils.h
  utils.cpp
  main.cpp
  shader08.fs
  shader08.vs
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
    ${CMAKE_CURRENT_SOURCE_DIR}/shader08.fs
    ${CMAKE_CURRENT_SOURCE_DIR}/shader08.vs
    ${CMAKE_CURRENT_SOURCE_DIR}/brickwall.jpg
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
)