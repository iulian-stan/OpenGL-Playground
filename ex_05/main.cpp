#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cstdio>
#include "utils.h"

// Vertex Buffer Object handler
GLuint VBO;
// Index Buffer Object handler
GLuint IBO;

// Shader program files
const char* pVSFileName = "shader.vs";
const char* pFSFileName = "shader.fs";

// DisplayFunction callback
static void onGlutDisplay()
{
  // Set color buffer clear values (RBA)
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  // Clear color buffer
  glClear(GL_COLOR_BUFFER_BIT);

  // Enable a generic vertex attribute array (position)
  glEnableVertexAttribArray(0);

  // Define an array of generic vertex attribute data (vertex of 3 floats)
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);

  // Enable a generic vertex attribute array (color)
  glEnableVertexAttribArray(1);

  // Define an array of generic vertex attribute data (vertex of 3 floats)
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

  // Render primitives from array data (vertex reprezenting the dot)
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  // Disable a generic vertex attribute array (position)
  glDisableVertexAttribArray(0);

  // Disable a generic vertex attribute array (color)
  glDisableVertexAttribArray(1);

  // Swap buffers
  glutSwapBuffers();
}

static void AttachShader(GLuint ShaderProgram, GLenum ShaderType, const char* pShaderFile)
{
  // Create shader object
  GLuint ShaderObj = glCreateShader(ShaderType);

  // Check shader object
  if (ShaderObj == 0)
  {
    fprintf(stderr, "Error creating shader type %d\n", ShaderType);
    exit(1);
  }

  const GLchar* shaders[1];
  GLint legths[1];

  // Read shader source code
  if (!ReadFile(pShaderFile, shaders[0], legths[0]))
  {
    fprintf(stderr, "Error reading shader file '%s'\n", pShaderFile);
    exit(1);
  };

  // Set shader object source code
  glShaderSource(ShaderObj, 1, shaders, legths);

  // Compile shader object
  glCompileShader(ShaderObj);

  free((void*)shaders[0]);

  // Check shader compilation status
  GLint success;
  glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    GLchar InfoLog[1024];
    glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
    fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
    exit(1);
  }

  // Attach shader to program
  glAttachShader(ShaderProgram, ShaderObj);
}

static void ShaderProgram()
{
  // Create shader program object
  GLuint ShaderProgram = glCreateProgram();

  // Check program object
  if (ShaderProgram == 0)
  {
    fprintf(stderr, "Error creating shader program\n");
    exit(1);
  }

  // Create and attach vertex shader
  AttachShader(ShaderProgram, GL_VERTEX_SHADER, pVSFileName);

  // Create and attach frahment shader
  AttachShader(ShaderProgram, GL_FRAGMENT_SHADER, pFSFileName);

  // Link program object
  glLinkProgram(ShaderProgram);

  // Check program object linking status
  GLint Success;
  glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
  if (!Success)
  {
    GLchar ErrorLog[1024];
    glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
    fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
    exit(1);
  }

  // Validate program object
  glValidateProgram(ShaderProgram);

  // Check program object validation status
  glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
  if (!Success)
  {
    GLchar ErrorLog[1024];
    glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
    fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
    exit(1);
  }

  // Install program object as part of current rendering state
  glUseProgram(ShaderProgram);
}

int main(int argc, char** argv)
{
  // Initialize Glut
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);

  // Initialize Glut Window
  glutInitWindowSize(1024, 768);
  glutInitWindowPosition(100, 100);

  // Create Glut Window
  glutCreateWindow("Exercise 05: OpenGL Shading Language (GLSL)");

  // Initialize Glut Display callback function
  glutDisplayFunc(onGlutDisplay);

  // Must be done after glut is initialized!
  GLenum res = glewInit();
  if (res != GLEW_OK)
  {
    fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
    return 1;
  }

  // Rectangle corners coordinates
  float vertices[4][6] =
  {
    {
      -0.5f, -0.5f, 0.0f,  // bottom left corner of the window (x = -0.5, y = -0.5)
       1.0f,  0.0f, 0.0f   // RGB (Red-1, Green-0, Blue-0)
    },
    {
       0.5f, -0.5f, 0.0f,  // bottom right corner of the window (x = 0.5, y = -0.5)
       1.0f,  0.0f, 0.0f   // RGB (Red-1, Green-0, Blue-0)
    },
    {
       0.5f,  0.5f, 0.0f,  // top right corner of the window (x = 0.5, y = 0.5)
       1.0f,  0.0f, 0.0f   // RGB (Red-1, Green-0, Blue-0)
    },
    {
      -0.5f,  0.5f, 0.0f,  // top left corner of the window (x = -0.5, y = 0.5)
       1.0f,  0.0f, 0.0f   // RGB (Red-1, Green-0, Blue-0)
    }
  };

  // Create vertex buffer
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Square is actually drawn as a combination of two triangles
  unsigned int indices[] =
  { 
    0, 1, 2, // first triangle (corners: bottom left, bottom right, top right)
    0, 3, 2  // second triangle (corners: bottom left, top left, top right)
  };

  // Create index buffer
  glGenBuffers(1, &IBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // Create, compile and install shader program
  ShaderProgram();

  // Start Glut main loop
  glutMainLoop();

  return 0;
}