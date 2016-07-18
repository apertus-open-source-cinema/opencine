#version 330
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

uniform mat4 MVP;

out vec4 vColor;
out vec2 vTexCoord;

void main()
{
  gl_Position = MVP * vec4(position, 1.0);
  vColor = vec4(color, 1.0f);
  vTexCoord = texCoord;
}
