#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

// Vertex Buffer Object handler
GLuint VBO;
// Index Buffer Object handler
GLuint IBO;

// DisplayFunction callback
static void onGlutDisplay()
{
  // Set color buffer clear values (RBA)
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  // Clear color buffer
  glClear(GL_COLOR_BUFFER_BIT);

  // Enable a generic vertex attribute array
  glEnableVertexAttribArray(0);

  // Define an array of generic vertex attribute data (vertex of 3 floats)
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

  // Render primitives from array data (vertex reprezenting the dot)
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  // Disable a generic vertex attribute array
  glDisableVertexAttribArray(0);

  // Swap buffers
  glutSwapBuffers();
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
  glutCreateWindow("Project 04: Drawing a Rectangle");

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
  float vertices[4][3] =
  {
    {-0.5f, -0.5f, 0.0f},  // bottom left corner of the window (x = -0.5, y = -0.5)
    { 0.5f, -0.5f, 0.0f},  // bottom right corner of the window (x = 0.5, y = -0.5)
    { 0.5f,  0.5f, 0.0f},  // top right corner of the window (x = 0.5, y = 0.5)
    {-0.5f,  0.5f, 0.0f}   // top left corner of the window (x = -0.5, y = 0.5)
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

  // Start Glut main loop
  glutMainLoop();

  return 0;
}