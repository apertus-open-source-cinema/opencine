#version 330
in vec2 Position;
//in vec3 Color;
//out vec4 vertColor;
in vec2 vertTexCoord;

out vec2 fragTexCoord;

void main(void)
{
  fragTexCoord = vertTexCoord;
  gl_Position = vec4(Position, 0.0, 1.0);
  //vertColor = vec4(Color, 1.0);
}

/*
"#version 130 \n\
in vec2 position; \n\
in vec2 vertTexCoord;\n\
in vec2 vertTexCoord2;\n\
out vec2 fragTexCoord;\n\
out vec2 fragTexCoord2;\n\
void main() \n\
{ \n\
  fragTexCoord = vertTexCoord; \n\
  fragTexCoord2 = vertTexCoord2; \n\
  gl_Position = vec4(position, 0.0, 1.0); \n\
  } \n\
  ");
  */
