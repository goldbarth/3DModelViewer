#version 330 core

out vec4 fragmentColor;

in vec4 vertexColor;
in vec2 vertexUV;

void main()
{
   fragmentColor = vec4(vertexColor);
}