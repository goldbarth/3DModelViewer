#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
out vec4 vertexColor;

// uniform mat4 cameraMatrix;

void main()
{
    gl_Position = //cameraMatrix * 
                    vec4(position, 1.0);
    vertexColor = color;
}