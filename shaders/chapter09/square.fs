#version 330 core
out vec4 FragColor;
in vec2 texCoord;
in vec3 color;

// float precision
precision mediump float;


uniform sampler2D container;
uniform sampler2D face;
uniform float mixValue;

void main()
{
 FragColor = vec4(color, 0.0) * mix(texture(container, texCoord), texture(face, vec2(texCoord.s, -texCoord.t)), mixValue);
}
