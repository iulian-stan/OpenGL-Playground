#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

const char* TITLE = "Project 03: Drawing a Triangle";

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

  // Render primitives from array data
  glDrawArrays(GL_TRIANGLES, 0, 3);

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
  glutCreateWindow(TITLE);

  // Initialize Glut Display callback function
  glutDisplayFunc(onGlutDisplay);

  // Must be done after glut is initialized!
  GLenum res = glewInit();
  if (res != GLEW_OK)
  {
    fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
    return 1;
  }

  // Triangle corners coordinates
  float vertices[3][3] =
  {
    {-1.0f, -1.0f, 0.0f},  // bottom left corner of the window (x = -1, y = -1)
    { 1.0f, -1.0f, 0.0f},  // bottom right corner of the window (x = 1, y = -1)
    { 0.0f,  1.0f, 0.0f}   // middle of the top side of the window (x = 0, y = 1)
  };

  // Create vertex buffer
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Start Glut main loop
  glutMainLoop();

  return 0;
}