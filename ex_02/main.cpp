#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

// Vertex Buffer Object handler
GLuint VBO;

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
  glDrawArrays(GL_POINTS, 0, 1);

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
  glutCreateWindow("Exercise 02");

  // Initialize Glut Display callback function
  glutDisplayFunc(onGlutDisplay);

  // Must be done after glut is initialized!
  GLenum res = glewInit();
  if (res != GLEW_OK)
  {
    fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
    return 1;
  }

  // Dot coordinates (middle of the window)
  float vertex[3] =
  {
    0.0f, // x axis coordinate
    0.0f, // y axis coordinate
    0.0f  // z axis coordinate
  };

  // Create vertex buffer
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

  // Start Glut main loop
  glutMainLoop();

  return 0;
}