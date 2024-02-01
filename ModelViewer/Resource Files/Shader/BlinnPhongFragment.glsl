#version 330 core

out vec4 fragmentColor;

in vec3 fragPosition;
in vec4 vertexColor;
in vec3 normalOut;
in vec3 lightOutPosition;

uniform vec3 lightColor;
uniform vec3 materialColor;
uniform vec3 specularColor;

void main()
{
    // Normalized normal
    vec3 normal = normalize(normalOut);

    // Ambient (Multiplying light color with object color)
    float ambientFactor = 0.5f;
    vec3 ambient = lightColor * materialColor * ambientFactor;
    
    // Diffuse (Angle between light and surface normal)
    vec3 lightDirection = normalize(lightOutPosition - fragPosition);
    float diffuseFactor = max(dot(normal, lightDirection), 0.0f);
    vec3 diffuse = diffuseFactor * lightColor * materialColor;
    
    // Specular (Angle between reflected light and view direction)
    float specularFactor = 0.5f;
    vec3 viewDirection = normalize(-fragPosition);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float specularIntensity = pow(max(dot(viewDirection, reflectDirection), 0.0f), 32);
    vec3 specular = specularFactor * specularIntensity * specularColor;
    
    // Final (Phong model with ambient, diffuse and specular)
    vec3 result = (ambient + diffuse + specular);
    fragmentColor = vec4(result, 1.0f);
}