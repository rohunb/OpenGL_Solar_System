#version 330 core

struct Material {
    sampler2D texture_diffuse1;
    vec3 specular;
    float shininess;
};
struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 fragPosition;
in vec3 fragNormal;
in vec2 fragTexCoord;

out vec4 outColour;

uniform vec3 uViewPos;
uniform Light uLight;
uniform Material uMaterial;

uniform sampler2D texture_diffuse1;

void main()
{
    //color = texture(myTexture, TexCoord);
	vec3 norm = normalize(fragNormal);
    vec3 lightDir = normalize(uLight.position - fragPosition);
    vec3 viewDir = normalize(uViewPos - fragPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    
    // Diffuse shading    
    float diffuse = max(dot(norm, lightDir), 0.0);
    
    // Specular shading    
    float specular = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.shininess);

    // Combine results
    vec3 ambientColor = uLight.ambient * vec3(texture(texture_diffuse1, fragTexCoord));
    vec3 diffuseColor = uLight.diffuse * diffuse * vec3(texture(texture_diffuse1, fragTexCoord));
    vec3 specularColor = uLight.specular * specular * uMaterial.specular;
    outColour = vec4(ambientColor + diffuseColor + specularColor, 1.0f);
	//outColour = vec4(0.8f,0.2f,0.3f,1.0f);
}