# Project 07: Color Interpolation

## Takeaways

* In the previous example all vertices had the same color attribute value `1.0f,  0.0f, 0.0f` that corresponds to the red color in RGB format. Note that user code has color definitions only for declared vertices and the engine will compute the color value of each fragment (pixel) by computing a weigthed average of the closest vertices. This example aims to show the interpolation effect obtained when the vertices have sifferent color values.