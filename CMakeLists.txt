cmake_minimum_required(VERSION 3.15)

project(OpenGL_Exercise)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/bin)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib)

# Adding dependencies
add_subdirectory(deps)

# Adding tutorials
add_subdirectory(ex_01)    # Creating OpenGL Window using FreeGLUT
add_subdirectory(ex_02)    # Drawing a dot
add_subdirectory(ex_03)    # Drawing a triangle
add_subdirectory(ex_04)    # Drawing a rectangle
add_subdirectory(ex_05)    # OpenGL Shading Language (GLSL)
add_subdirectory(ex_05.5)  # Color interpolation
add_subdirectory(ex_06)    # Textures
add_subdirectory(ex_06.5)  # Texture and color blending
add_subdirectory(ex_07)    # Transformations with GLM
add_subdirectory(ex_08)    # Going 3D (cube)
add_subdirectory(ex_08.5)  # Depth test
add_subdirectory(ex_09)    # Camera (actor)
add_subdirectory(ex_09.5)  # Face culing
add_subdirectory(ex_10)    # Orthogonal projection
add_subdirectory(ex_11)    # Perspective projection)
