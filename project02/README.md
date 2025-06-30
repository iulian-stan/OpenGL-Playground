# Project02: Drawing a dot

## Intro

## Summary

## Functions Glossary

## Notes

## Spoiler

## Takeaways

* Initialize GLEW after GLUT is initialized
```
GLenum res = glewInit();
if (res != GLEW_OK)
{
  fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
  return 1;
}
```

* Declare a Vertex Buffer Object (VBO)
```
GLuint VBO;
```

* Create Vetex Buffer and bind it to the VBO
```
glGenBuffers(1, &VBO);
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
```

* Before drawing the dot intialize vertex attribute array. Then define vetex attribute data (3 float numbers `GL_FLOAT` reprezenting dot coordinates) and render the primitive `GL_POINTS` from array data. Finnaly, disable vertex attribute array to keep application state clean.
```
glEnableVertexAttribArray(0);
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
glDrawArrays(GL_POINTS, 0, 1);
glDisableVertexAttribArray(0);
```