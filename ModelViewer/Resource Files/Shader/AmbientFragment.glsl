#version 330 core
out vec4 fragmentColor;
in vec3 vertexColor;

uniform vec3 ambientVector;

void main()
{
    vec3 modelColor = vec3(0.75f, 0.75f, 0.75f);
    vec3 resultColor = modelColor * ambientVector;
    
    fragmentColor = vec4(resultColor, 1.0f);
}

