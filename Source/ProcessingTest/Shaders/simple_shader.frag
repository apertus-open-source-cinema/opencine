#version 330
in highp vec4 vColor;
in vec2 vTexCoord;

out highp vec4 fColor;
uniform usampler2D texture1;
uniform usampler2D texture2;
uniform usampler2D texture3;

void main()
{
   vec4 textureRed = uvec4(1.0,0.0,0.0,1.0) * texture(texture1, vTexCoord).r;
   vec4 textureGreen = uvec4(0.0,1.0,0.0,1.0) * texture(texture2, vTexCoord).r;
   vec4 textureBlue = uvec4(0.0,0.0,1.0,1.0) * texture(texture3, vTexCoord).r;
   fColor = pow((textureRed + textureGreen + textureBlue) / 3, vec4(1.0 / 2.2, 1.0 / 2.2, 1.0 / 2.2, 1.0));
}
