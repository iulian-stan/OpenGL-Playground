# Project 03: Drawing a Triangle

## Takeaways

* Define triangle vetices as 3 arrays (1 per corner) each of 3 floats (x, y and z componnets)
```
float vertices[3][3] =
{
  {-1.0f, -1.0f, 0.0f},  // bottom left corner of the window (x = -1, y = -1)
  { 1.0f, -1.0f, 0.0f},  // bottom right corner of the window (x = 1, y = -1)
  { 0.0f,  1.0f, 0.0f}   // middle of the top side of the window (x = 0, y = 1)
};
```

* Create buffer of a corresponding size. In our case it is handled automatically due to the use the `sizeof` function
```
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
```

* Call `glDrawArrays` with `GL_TRIANGLES` argument to render one or more triangles
```
glDrawArrays(GL_TRIANGLES, 0, 3);
```