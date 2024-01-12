#version 330 core
out vec4 fragmentColor;
in vec4 vertexColor;
in vec2 TexCoord;

void main()
{
   fragmentColor = vec4(vertexColor);
}