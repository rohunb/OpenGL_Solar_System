#version 330 core

in vec2 fragTexCoord;
uniform sampler2D texture_diffuse1;  
out vec4 outColour;

void main()
{    
    outColour = texture(texture_diffuse1, fragTexCoord);
}