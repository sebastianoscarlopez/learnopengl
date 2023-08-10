#version 330 core
out vec4 FragColor;

uniform vec3 color;

uniform vec3 ambientColor;
uniform float ambientStrength;

uniform vec3 lightColor;
uniform float lightStrength;

uniform vec3 lightPosition;
uniform vec3 cameraPosition;

in vec3 normals;
in vec3 fragPos;

void main()
{
  vec3 ambient = ambientColor * ambientStrength;

  vec3 norm = normalize(normals);
  vec3 lightDir = normalize(lightPosition - fragPos);
  vec3 diffuse = lightStrength * lightColor * max(dot(norm, lightDir), 0.0);

  float specularStrength = 1.0f;
  vec3 viewDir = normalize(cameraPosition - fragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
  vec3 specular = specularStrength * spec * lightStrength * lightColor;

  FragColor = vec4((ambient + diffuse + specular) * color, 1.0);
  // FragColor = vec4((norm + 1.0) / 2.0f, 1.0f);
}
