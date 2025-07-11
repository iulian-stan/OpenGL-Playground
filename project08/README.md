# Project 08: Texture and Color Blending

## Takeaways

* In this example both color and texture attributes are passed into the verted shader
```
#version 330

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 inColor;
layout (location = 2) in vec2 aTexCoord;

out vec4 Color;
out vec2 TexCoord;

void main()

{
  gl_Position = vec4(Position, 1.0);
  Color = vec4(inColor, 1.0);
  TexCoord = aTexCoord;
}
```
and piped into fragment shader wher texture and color are blended by multiplying the two variables
```
#version 330

in vec4 Color;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, TexCoord) * Color;
}
```