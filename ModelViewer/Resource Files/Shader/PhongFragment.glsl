#version 330 core

out vec4 fragmentColor;

in vec3 fragPosition;
in vec4 vertexColor;
in vec2 vertexUV;
in vec3 normal;
in vec3 lightPositon;

uniform vec3 lightVector;
uniform vec3 objectVector;

void main()
{
    // Ambient
    vec3 modelColor = vec3(0.75f, 0.75f, 0.75f);
    vec3 ambient = modelColor * lightVector;
    
    // Diffuse
    vec3 normalized = normalize(normal);
    vec3 lightDirection = normalize(lightPositon - fragPosition);
    float diffuseFactor = max(dot(normalized, lightDirection), 0.0f);
    vec3 diffuse = diffuseFactor * lightVector;

    // Specular
    float specularFactor = 0.5f;
    vec3 viewDirection = normalize(-fragPosition);
    vec3 reflectDirection = reflect(-lightDirection, normalized);
    float specularIntensity = pow(max(dot(viewDirection, reflectDirection), 0.0f), 32);
    vec3 specular = specularFactor * specularIntensity * lightVector;
    
    // Final (Phong model with ambient, diffuse and specular)
    vec3 resultColor = (ambient + diffuse + specular) * objectVector;
    fragmentColor = vec4(resultColor, 1.0f);
}