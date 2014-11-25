#version 330 core

out vec4 outColour;

uniform vec3 uColour;

void main()
{
    outColour = vec4(uColour, 1.0f);
}