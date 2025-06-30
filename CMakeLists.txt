cmake_minimum_required(VERSION 3.15)

project(OpenGL_Projects)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/bin)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib)

# Adding dependencies
add_subdirectory(dependencies)

# Adding projects
add_subdirectory(project01)    # Creating OpenGL Window using FreeGLUT
add_subdirectory(project02)    # Drawing a Dot
add_subdirectory(project03)    # Drawing a triangle
add_subdirectory(project04)    # Drawing a Rectangle
add_subdirectory(project05)    # OpenGL Shading Language (GLSL)
add_subdirectory(project06)    # Color Interpolation
add_subdirectory(project07)    # Textures
add_subdirectory(project08)    # Texture and Color Blending
add_subdirectory(project09)    # Transformations with GLM
add_subdirectory(project10)    # Going 3D (cube)
add_subdirectory(project11)    # Depth Test
add_subdirectory(project12)    # Camera (actor)
add_subdirectory(project13)    # Face Culling
add_subdirectory(project14)    # Orthogonal Projection
add_subdirectory(project15)    # Perspective Projection
