# Project04: Drawing a rectangle

## Intro

## Summary

## Functions Glossary

## Notes

## Spoiler

## Takeaways

* GPUs are designed to render triangles, thus other shapes can be seen as a combination of multiple triangles. For example, a rectangle can be represented as 2 right-angled triangles with one common side (hypotenuse). 

* Define rectangle corner vertices. Note the use of 0.5 and -0.5 values instead of 1 and -1, they prevent the rectangle from covering the entire window.
```
float vertices[4][3] =
{
  {-0.5f, -0.5f, 0.0f},  // bottom left corner of the window (x = -0.5, y = -0.5)
  { 0.5f, -0.5f, 0.0f},  // bottom right corner of the window (x = 0.5, y = -0.5)
  { 0.5f,  0.5f, 0.0f},  // top right corner of the window (x = 0.5, y = 0.5)
  {-0.5f,  0.5f, 0.0f}   // top left corner of the window (x = -0.5, y = 0.5)
};
```

* Considering 2 corners are reused by the triangles, the vertices array will not include redeclarations. Instead, another mechanic will be used to indicate corner indices for each triangle.
```
unsigned int indices[] =
{ 
  0, 1, 2, // first triangle (corners: bottom left, bottom right, top right)
  0, 2, 3  // second triangle (corners: bottom left, top right, top left)
};
```

* To bind these indices are linked into OpenGL application via Index Buffer Object. 
```
GLuint IBO;
```

* Index Buffer Object is generated and bound similar to Vertex Buffer Object,
```
glGenBuffers(1, &IBO);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
```

* Finnaly, the triangles a drawn using `glDrawElements` instead of `glDrawArrays`.
```
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
```