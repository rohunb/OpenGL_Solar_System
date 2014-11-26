#version 330 core

out vec4 outColour;

uniform vec3 uColour;

void main()
{
    outColour = vec4(uColour, 1.0f);
	//outColour = vec4(1.0f,1.0f,1.0f,1.0f);
}