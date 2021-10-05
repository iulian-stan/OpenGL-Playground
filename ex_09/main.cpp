#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cstdio>
#include "utils.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Vertex Buffer Object handler
GLuint VBO;
// Index Buffer Object handler
GLuint IBO;
// Uniform variable
GLuint gTrans;

// Shader program files
const char* pVSFileName = "shader.vs";
const char* pFSFileName = "shader.fs";

// Texture image
const char* pTexFileName = "box.png";

static float rx = 0.f; // rotation around X (pitch / tilt)
static float ry = 0.f; // rotation around Y (pan / yaw)
static float rz = 0.f; // rotation around Z (roll)
const float dr = 1.f;  // rotate delta increment


static glm::mat4 trans1 = glm::mat4(1.0f);

// DisplayFunction callback
static void onGlutDisplay()
{
  // Set color buffer clear values (RBA)
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  // Clear color buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //Initialize identity matrix
  glm::mat4 trans = glm::mat4(1.0f);

  // Apply rotation transformation
  trans = glm::rotate(trans, glm::radians(rx), glm::vec3(1.0, 0.0, 0.0));
  trans = glm::rotate(trans, glm::radians(ry), glm::vec3(0.0, 1.0, 0.0));
  trans = glm::rotate(trans, glm::radians(rz), glm::vec3(0.0, 0.0, 1.0));

  trans1 = trans1 * trans;

  trans = glm::lookAt(glm::vec3(.0, .0, -.1), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0)) * trans1;

  // Set value 
  glUniformMatrix4fv(gTrans, 1, GL_FALSE, &trans[0][0]);

  // Enable a generic vertex attribute array (position)
  glEnableVertexAttribArray(0);

  // Define an array of generic vertex attribute data (vertex of 3 floats)
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);

  // Enable a generic vertex attribute array (texture)
  glEnableVertexAttribArray(1);

  // Define an array of generic vertex attribute data (texture - 2 floats)
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

  // Render primitives from array data (vertex reprezenting the dot)
  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

  // Disable a generic vertex attribute array (position)
  glDisableVertexAttribArray(0);

  // Disable a generic vertex attribute array (texture)
  glDisableVertexAttribArray(1);

  // Swap buffers
  glutSwapBuffers();
}

// Keyboard Function callback
static void onGlutKey(unsigned char key, int x, int y)
{
    //switch (key)
    //{
    //case 'w':
    //    ry += dr; // move forward
    //    break;
    //case 's':
    //    ry -= dr; // move backward
    //    break;
    //case 'a':
    //    rx += dr; // move left
    //    break;
    //case 'd':
    //    rx -= dr; // move right
    //    break;
    //case 'q':
    //    glutLeaveMainLoop(); // quit
    //    break;
    //default:
    //    return;
    //}

    switch (key)
    {
    case 'a':
        ry += dr; // Pan clock-wise
        break;
    case 'd':
        ry -= dr; // Pan anti clock-wise
        break;
    case 'w':
        rx += dr; // Tilt clock-wise
        break;
    case 's':
        rx -= dr; // Tilt anti clock-wise
        break;
    case 'q':
        rz += dr; // Roll clock-wise
        break;
    case 'e':
        rz -= dr; // Roll anti clock-wise
        break;
    default:
        return;
    }

    // Force redisplay
    glutPostRedisplay();
}

static void onGlutMotion(int x, int y)
{

}

static void onGlutMouseWheel(int button, int state, int x, int y)
{

}

static void onGlutMouseEntry(int state)
{

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

  gTrans = glGetUniformLocation(ShaderProgram, "gTransform");
  if (gTrans == -1)
  {
    fprintf(stderr, "Error getting uniform location of 'gTransform'\n");
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
  glutCreateWindow("Exercise 09: Camera (actor)");

  // Initialize Glut Display callback function
  glutDisplayFunc(onGlutDisplay);

  // Initialize Glut Keyboard callback function
  glutKeyboardFunc(onGlutKey);

  // Initialize Glut Mouse Motion callback function
  glutMotionFunc(onGlutMotion);
  glutPassiveMotionFunc(onGlutMotion);

  // Initialize Glut Mouse Wheel callback function
  glutMouseWheelFunc(onGlutMouseWheel);

  // Initialize Glut Mouse enter/leave callback function
  glutEntryFunc(onGlutMouseEntry);

  // Must be done after glut is initialized!
  GLenum res = glewInit();
  if (res != GLEW_OK)
  {
    fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
    return 1;
  }

  // Rectangle corners coordinates
  float vertices[24][5] =
  {  
    // Left Side
    { -0.5f, -0.5f,  0.5f,  0.0f,  0.0f },
    { -0.5f, -0.5f, -0.5f,  1.0f,  0.0f },
    { -0.5f,  0.5f, -0.5f,  1.0f,  1.0f },
    { -0.5f,  0.5f,  0.5f,  0.0f,  1.0f },
    // Front Side
    { -0.5f, -0.5f, -0.5f,  0.0f,  0.0f },
    {  0.5f, -0.5f, -0.5f,  1.0f,  0.0f },
    {  0.5f,  0.5f, -0.5f,  1.0f,  1.0f },
    { -0.5f,  0.5f, -0.5f,  0.0f,  1.0f },
    // Right Side
    {  0.5f, -0.5f, -0.5f,  0.0f,  0.0f },
    {  0.5f, -0.5f,  0.5f,  1.0f,  0.0f },
    {  0.5f,  0.5f,  0.5f,  1.0f,  1.0f },
    {  0.5f,  0.5f, -0.5f,  0.0f,  1.0f },
    // Back Side
    {  0.5f, -0.5f,  0.5f,  0.0f,  0.0f },
    { -0.5f, -0.5f,  0.5f,  1.0f,  0.0f },
    { -0.5f,  0.5f,  0.5f,  1.0f,  1.0f },
    {  0.5f,  0.5f,  0.5f,  0.0f,  1.0f },
    // Top Side
    { -0.5f,  0.5f, -0.5f,  0.0f,  0.0f },
    {  0.5f,  0.5f, -0.5f,  1.0f,  0.0f },
    {  0.5f,  0.5f,  0.5f,  1.0f,  1.0f },
    { -0.5f,  0.5f,  0.5f,  0.0f,  1.0f },
    // Bottom Side
    { -0.5f, -0.5f,  0.5f,  0.0f,  0.0f },
    {  0.5f, -0.5f,  0.5f,  1.0f,  0.0f },
    {  0.5f, -0.5f, -0.5f,  1.0f,  1.0f },
    { -0.5f, -0.5f, -0.5f,  0.0f,  1.0f }
  };

  // Create vertex buffer
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Square is actually drawn as a combination of two triangles
  unsigned int indices[36] =
  { 
     0,  1,  3,  1,  2,  3,
     4,  5,  7,  5,  6,  7,
     8,  9, 11,  9, 10, 11,
    12, 13, 15, 13, 14, 15,
    16, 17, 19, 17, 18, 19,
    20, 21, 23, 21, 22, 23
  };

  // Create index buffer
  glGenBuffers(1, &IBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // Texture Object handler
  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  // Set the texture wrapping/filtering options (on the currently bound texture object)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // Load and generate the texture
  int width, height, nrChannels;
  unsigned char *data = stbi_load(pTexFileName, &width, &height, &nrChannels, 0);
  if (data)
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
    fprintf(stderr, "Error loading texture file'%s'\n", pTexFileName);
    exit(1);
  }
  stbi_image_free(data);

  //glEnable(GL_DEPTH_TEST);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glFrontFace(GL_CCW);

  // Create, compile and install shader program
  ShaderProgram();

  // Start Glut main loop
  glutMainLoop();

  return 0;
}