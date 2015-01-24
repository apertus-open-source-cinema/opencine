#version 330
in vec2 fragTexCoord;
out vec4 fragColor;

uniform sampler2D mainTexture;

void main(void)
{
  bool red = true;
  bool green = true;
  bool blue = true;

  fragColor = texture(mainTexture, fragTexCoord) * vec4(red, green, blue, 1.0);
}
