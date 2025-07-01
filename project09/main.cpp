#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cstdio>
#include "utils.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

const char* TITLE = "Project 09: Transformations with GLM";

// Vertex Buffer Object handler
GLuint VBO;
// Index Buffer Object handler
GLuint IBO;
// Uniform variable
GLuint gTrans;

// Shader program files
const char* pVSFileName = "shader09.vs";
const char* pFSFileName = "shader09.fs";

// Texture image
const char* pTexFileName = "brickwall.jpg";

static float dx = 0.f; // translation on X azis
static float dy = 0.f; // translation on Y axis
const float dt = 0.05; // translation delta increment
static float sx = 1.f; // scale factor on X axis
static float sy = 1.f; // scale factor on Y axis
const float ds = 0.1;  // scale delta increment
static float rz = 0.f; // rotation around Z
const float dr = 1.f;    // rotate delta increment

// Display Function callback
static void onGlutDisplay()
{
  // Set color buffer clear values (RBA)
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  // Clear color buffer
  glClear(GL_COLOR_BUFFER_BIT);

  //Initialize identity matrix
  glm::mat4 trans = glm::mat4(1.0f);

  // Apply translation transformation
  trans = glm::translate(trans, glm::vec3(dx, dy, 0.0f));

  // Apply scaling transformation
  trans = glm::scale(trans, glm::vec3(sx, sy, 1));

  // Apply rotation transformation
  trans = glm::rotate(trans, glm::radians(rz), glm::vec3(0.0, 0.0, 1.0));

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
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
    switch (key)
    {
        case 'w':
            dy += dt; // move up
            break;
        case 's':
            dy -= dt; // move down
            break;
        case 'd':
            dx += dt; // move right
            break;
        case 'a':
            dx -= dt; // move left
            break;
        case 'q':
            sx += ds; // upscale on horizontal
            break;
        case 'Q':
            sx -= ds; // downscale on horizontal
            break;
        case 'e':
            sy += ds; // upscale on vertical
            break;
        case 'E':
            sy -= ds; // downscale on vertical
            break;
        case 'r':
            rz += dr; // rotate clock-wise
            break;
        case 'R':
            rz -= dr; // rotate anti clock-wise
            break;
        default:
            return;
    }

    // Force redisplay
    glutPostRedisplay();
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
  glutCreateWindow(TITLE);

  // Initialize Glut Display callback function
  glutDisplayFunc(onGlutDisplay);

  // Initialize Glut Keyboard callback function
  glutKeyboardFunc(onGlutKey);

  // Must be done after glut is initialized!
  GLenum res = glewInit();
  if (res != GLEW_OK)
  {
    fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
    return 1;
  }

  // Rectangle corners coordinates
  float vertices[4][5] =
  {
    {
      -0.5f, -0.5f, 0.0f,  // bottom left corner of the window (x = -0.5, y = -0.5)
      -1.0f, -1.0f         // Texture bottom left
    },
    {
       0.5f, -0.5f, 0.0f,  // bottom right corner of the window (x = 0.5, y = -0.5)
       1.0f, -1.0f         // Texture bottom right
    },
    {
       0.5f,  0.5f, 0.0f,  // top right corner of the window (x = 0.5, y = 0.5)
       1.0f,  1.0f         // Texture top right
    },
    {
      -0.5f,  0.5f, 0.0f,  // top left corner of the window (x = -0.5, y = 0.5)
      -1.0f,  1.0f         // Texture top left
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
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
    fprintf(stderr, "Error loading texture file'%s'\n", pTexFileName);
    exit(1);
  }
  stbi_image_free(data);

  // Create, compile and install shader program
  ShaderProgram();

  // Start Glut main loop
  glutMainLoop();

  return 0;
}