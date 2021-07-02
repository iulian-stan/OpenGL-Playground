# Texture

## Takeaways

* Just like VBO and IBO, texture is an object that needs to be created using a corresponding function `glGenTextures` and bound to a texturing target using `glBindTexture `
```
GLuint texture;
glGenTextures(1, &texture);
glBindTexture(GL_TEXTURE_2D, texture);
```
* Additional texture options ca be set using `glTexParameteri`
```
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
```
* OpenGL knows how to load texture data in different formats from a memory location but does not provide any means for loading the texture into memory from image. For this purpose an additional library is used `stb_image`
```
int width, height, nrChannels;
unsigned char *data = stbi_load(pTexFileName, &width, &height, &nrChannels, 0);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
glGenerateMipmap(GL_TEXTURE_2D);
```
* Simialr to color attribute, texture is also, first loaded into the vertex shader
```
#version 330

layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

void main()

{
  gl_Position = vec4(Position, 1.0);
  TexCoord = aTexCoord;
}
```
and passed down the pipeline into the fragment shader
```
#version 330

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, TexCoord);
}
```