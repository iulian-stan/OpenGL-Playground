#version 330

layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 gTransform;

void main()

{
  gl_Position = gTransform * vec4(Position, 1.0);
  TexCoord = aTexCoord;
}