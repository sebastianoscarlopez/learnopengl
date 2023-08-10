#version 330 core
out vec4 FragColor;

uniform vec3 lightColor;
uniform float lightStrength;

void main()
{
 FragColor = vec4(lightColor * lightStrength, 1.0);
}
