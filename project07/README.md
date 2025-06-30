# Project07: Transformations with GLM

## Intro

## Summary

## Functions Glossary

## Notes

## Spoiler

## Takeaways

* OpenGL Mathematics (GLM) is a header only C++ mathematics library for graphics software based on the OpenGL Shading Language (GLSL) specifications. It works perfectly with OpenGL but it also ensures interoperability with other third party libraries and SDK. It is a good candidate for software rendering (raytracing / rasterisation), image processing, physics simulations and any development context that requires a simple and convenient mathematics library.

* Transformations used in this example (translation, scalling and rotation) have corerspoinding GLM functions. Each function returns a 4 by 4 matrix. The final transformation is obtained by chaining an initial identity matrix (no transformation) though glm functions. Note: the final transformation is dependent on the order each independent transformation is applied.
1. Initialize identity matrix
```
glm::mat4 trans = glm::mat4(1.0f);
```
2. Apply translation transformation (0.5f on X axis - to the right, -0.5f on Y axis - to the bottom)
```
trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
```
3. Apply scaling transformation (0.5f on both X and Y axises - cut the size in half)
```
trans = glm::scale(trans, glm::vec3(0.5, 0.5, 1));
```
4. Apply rotation transformation (45 degrees across Z azis)
```
trans = glm::rotate(trans, glm::radians(45), glm::vec3(0.0, 0.0, 1.0));
```
**Note:** most application use radias instead of degrees thus the value passed to the rotation function has to be converted into radians.

* The final transformation is passed into the shader program using an uniform variable. Uniforms is an alternative to vertex attribute that allows passind data to the shaders.
```
#version 330

layout (location = 0) in vec3 Position;

uniform mat4 gTransform;

void main()
{
  gl_Position = gTransform * vec4(Position, 1.0);
}
```
To bind the uniform variable `gTransform` to the previously computed tranformation" follow these steps:
1. Declare a handler for the variable
```
GLuint gTrans;
```
2. Bind the handler to shader variable location (the name should match the one declared in the shader)
```
gTrans = glGetUniformLocation(ShaderProgram, "gTransform");
if (gTrans == -1)
{
  fprintf(stderr, "Error getting uniform location of 'gTransform'\n");
  exit(1);
}
```
This step should be executed after the shader is attached to the program, but before the program is validated

3. Set uniform variable value by passing the pointer to the transformation matrix `&trans[0][0]`, it is also possible to use GLM function `value_ptr`
```
glUniformMatrix4fv(gTrans, 1, GL_FALSE, &trans[0][0]);
```
**Note:** both OpenGL and GLM uses column-major ordering by default, thus the 3rd argument `GL_FALSE` informs that the matrix should not be transposed.

* To observe these transformation in real time, they are bound to the keyboard (see onGlutKey function). Keyboard bindings are initialized via `glutKeyboardFunc`.

**Note:** FreeGLUT call the dispkay callback function only when on system requests such as resize, minimize / maximize, etc. To force the redisplay an explicit call to the `glutPostRedisplay` is added to the Keyboard callback function.