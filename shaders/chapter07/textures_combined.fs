#version 330 core
out vec4 FragColor;
in vec2 texCoord;
in vec3 color;

uniform sampler2D container;
uniform sampler2D face;

void main()
{
 FragColor = mix(texture(container, texCoord), texture(face, texCoord), 0.2);
}
