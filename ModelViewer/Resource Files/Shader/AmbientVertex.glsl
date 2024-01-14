#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 vertexUV;
layout (location = 3) in vec3 normal;

out vec4 vertexColor;

uniform mat4 projectionViewMatrix;

void main()
{
    gl_Position = projectionViewMatrix * vec4(position, 1.0);
    vertexColor = color;
}
