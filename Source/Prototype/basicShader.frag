#version 330
//in vec4 vertColor;
out vec4 fragColor;
in vec2 fragTexCoord;
//uniform vec2 texCoord;
uniform sampler2D mainTexture;

void main(void)
{
  fragColor = texture(mainTexture, fragTexCoord);
}


/*std::string fragmentShaderSource(
"#version 130 \n\
uniform sampler2D texture1; \n\
uniform sampler2D texture2; \n\
in vec2 fragTexCoord; \n\
in vec2 fragTexCoord2; \n\
out vec3 outColor; \n\
void main() \n\
{ \n\
outColor = vec3(1.0f, 1.0f, 1.0f) * texture( texture1, fragTexCoord ).rgb * 10;// * texture(texture2, fragTexCoord2).rgb; \n\
} \n\
*/
