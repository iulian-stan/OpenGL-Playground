#include <GL/freeglut.h>

// DisplayFunction callback
static void onGlutDisplay()
{
  // Set color buffer clear values (RGBA)
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  // Clear color buffer
  glClear(GL_COLOR_BUFFER_BIT);

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
  glutCreateWindow("Project 01: Creating OpenGL Window using FreeGLUT");

  // Initialize Glut Display callback function
  glutDisplayFunc(onGlutDisplay);

  // Start Glut main loop
  glutMainLoop();

  return 0;
}