#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform float offset;

out vec4 vertexColor;
void main()
{
  vertexColor = vec4(aColor, 1.0);
 gl_Position = vec4(1 - (aPos.x + offset), -aPos.y, aPos.z, 1.0);
}