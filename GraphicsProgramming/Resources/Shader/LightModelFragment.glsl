#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;  
in vec3 FragPos;  

uniform vec3 lightPos; 
uniform vec3 viewPos;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform sampler2D texture_diffuse1;

void main()
{    
 // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos); // Direction from light source to fragment
    float diff = max(dot(norm, lightDir), 0.0); // Diffuse intensity
    vec3 diffuse = diff * lightColor;
    
    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos); // Direction from fragment to camera
    vec3 reflectDir = reflect(-lightDir, norm);  // Direction of reflected light
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32); // Specular intensity
    vec3 specular = specularStrength * spec * lightColor;  
    
    // combine results
    vec3 light = ambient + diffuse + specular;
    vec3 lightResult = light * objectColor;
    vec4 texResult = texture(texture_diffuse1, TexCoords);
    
    // output
    FragColor = vec4(lightResult, 1.0) * texResult;
}