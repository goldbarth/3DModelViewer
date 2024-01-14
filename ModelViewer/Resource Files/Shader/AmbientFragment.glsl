#version 330 core

out vec4 fragmentColor;

in vec4 vertexColor;
in vec2 vertexUV;

uniform vec3 ambientVector;

void main()
{
    vec3 modelColor = vec3(0.75f, 0.75f, 0.75f);
    vec3 resultColor = modelColor * ambientVector;
    
    fragmentColor = vec4(resultColor + vertexColor.rgb, 1.0f);
}

