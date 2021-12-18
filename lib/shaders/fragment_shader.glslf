#version 330 core

in vec3 normal;
in vec3 positionWorld;
in vec2 texCoord;

out vec4 fragment_color;

uniform vec3 lightPosition;
uniform sampler2D colormap;

void main()
{
  vec3 norm = normalize(normal);
  vec3 lightDir = normalize(lightPosition - positionWorld);

  float diffuseComponent = max(dot(norm, lightDir), 0.0);
  fragment_color = texture(colormap, texCoord) * diffuseComponent * vec4(0.5f, 0.5f, 0.5f, 1.0f);
}
