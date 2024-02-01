#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in vec3 normal;

out vec3 fragPosition;
out vec4 vertexColor;
out vec3 normalOut;
out vec3 lightOutPosition;

uniform vec3 lightPosition;
uniform mat4 projectionViewMatrix;
uniform mat4 view;

void main()
{
    gl_Position = projectionViewMatrix * vec4(position, 1.0f);
    vertexColor = color;
    
    fragPosition = vec3(view * vec4(position, 1.0f));
    normalOut = mat3(transpose(inverse(view))) * normal;
    lightOutPosition = vec3(view * vec4(lightPosition, 1.0f));
}

