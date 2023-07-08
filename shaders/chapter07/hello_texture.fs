#version 330 core
out vec4 FragColor;
in vec2 texCoord;
in vec3 color;

uniform sampler2D container;

void main()
{
 FragColor = texture(container, texCoord);// * vec4(color, 1.0);
}
