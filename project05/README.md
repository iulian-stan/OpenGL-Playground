# Project 05: Face Culling

## Takeaways

* Note that in the `Drawing Rectangle` the order of corner indices does not affect the end result (the rectangle is always rendered). By default, OpenGL renders all sides of the polygon. This is not efficient as the back side of the shape is not visible, thus additional space can be saved by preventing it from beeing rendered. The technique that accomplishes this action is called [`Face Culling`](https://www.khronos.org/opengl/wiki/Face_Culling).

* Enable Face Culling using `glEnable` function.
```
glEnable(GL_CULL_FACE);
```

* Define how fron- and back- faced polygons are identified using `glFrontFace` (by default the Counter Clock Wise rule applies to the front face).
```
glFrontFace(GL_CW);
```

* Set the side to be culled using `glCullFace`.
```
glCullFace(GL_FRONT);
```