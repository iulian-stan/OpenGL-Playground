# Creating OpenGL Window using [FreeGLUT](http://freeglut.sourceforge.net/)

## Takeaways

* Initialize GLUT using `glutInit` and `glutInit`
```
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
```

* Set Window size and position using `glutInitWindowSize` and `glutInitWindowPosition`
```
glutInitWindowSize(1024, 768);
glutInitWindowPosition(100, 100);
```

* Create Window using `glutCreateWindow`
```
glutCreateWindow("Exercise 01");
```

* Initialize display callback function using `glutDisplayFunc`
```
glutDisplayFunc(onGlutDisplay);
```

* `onGlutDisplay` function sets color buffer value (RGBA), clears color buffer and swaps buffers
```
static void onGlutDisplay()
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glutSwapBuffers();
}
```
**Note:** The callback function is executed only on window manipulations (move, resize, etc.), add `glutPostRedisplay();` at the end of the function to mark current window as needing to be redisplayed.

* Invoke Glut main loop using `glutMainLoop`
```
glutMainLoop();
``` 