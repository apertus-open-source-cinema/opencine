#version 330
in vec2 Position;
in vec2 vertTexCoord;
uniform mat4 ProjectionMatrix, CameraMatrix, ModelMatrix;

out vec2 fragTexCoord;

void main(void)
{
//   mat4 Matrix = ProjectionMatrix * CameraMatrix * ModelMatrix;

  mat4 Matrix = CameraMatrix * ModelMatrix;

  fragTexCoord = vertTexCoord;
  gl_Position = Matrix * vec4(Position, 0.0, 1.0);
}
