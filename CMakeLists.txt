cmake_minimum_required(VERSION 3.15)

project(OpenGL_Projects)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/bin)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib)

# Adding dependencies
add_subdirectory(dependencies)

# Adding projects
add_subdirectory(project01)    # Creating OpenGL Window using FreeGLUT
add_subdirectory(project02)    # Drawing a dot
add_subdirectory(project03)    # Drawing a triangle
add_subdirectory(project04)    # Drawing a rectangle
add_subdirectory(project05)    # OpenGL Shading Language (GLSL)
add_subdirectory(project05.5)  # Color interpolation
add_subdirectory(project06)    # Textures
add_subdirectory(project06.5)  # Texture and color blending
add_subdirectory(project07)    # Transformations with GLM
add_subdirectory(project08)    # Going 3D (cube)
add_subdirectory(project08.5)  # Depth test
add_subdirectory(project09)    # Camera (actor)
add_subdirectory(project09.5)  # Face culing
add_subdirectory(project10)    # Orthogonal projection
add_subdirectory(project11)    # Perspective projection)
