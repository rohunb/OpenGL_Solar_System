#pragma once
#include"vgl.h"
#include "glm\glm.hpp"

struct Light 
{
	glm::vec3 position;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	~Light(){}
	Light()
		:position(glm::vec3(0.0f)),
		ambient(glm::vec3(1.0f)),
		diffuse(glm::vec3(1.0f)),
		specular(glm::vec3(1.0f))
	{}
	Light(const glm::vec3& _position, const glm::vec3& _ambient, const glm::vec3& _diffuse, const glm::vec3& _specular)
		:position(_position),
		ambient(_ambient),
		diffuse(_diffuse),
		specular(_specular)
	{}
};

