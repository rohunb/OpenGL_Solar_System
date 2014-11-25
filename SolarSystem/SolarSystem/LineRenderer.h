#pragma once
#include "vgl.h"
#include "glm\glm.hpp"
#include <iostream>
#include <vector>
#include "Shader.h"

typedef unsigned int uint;

class LineRenderer
{
public:
	LineRenderer();
	LineRenderer(Shader* shader);
	LineRenderer(const std::vector<glm::vec3>& vertices);
	LineRenderer(Shader* shader, const std::vector<glm::vec3>& vertices);

	~LineRenderer();

	void Init();
	void Render(const glm::mat4& view, const glm::mat4& projection);
	void ReGenArrays();
	inline void SetColour(const glm::vec3& colour)
	{
		this->colour = new GLfloat[3];
		this->colour[0] = colour[0];
		this->colour[1] = colour[1];
		this->colour[2] = colour[2];
	}
	inline int NumVertices() const 
	{
		return numVertices; 
	}
	inline void NumVertices(int val) 
	{ 
		numVertices = val; 
		vertices.resize(val);
	}
	inline void SetVertexPosition(int index, const glm::vec3& position)
	{
		if (index>=numVertices)
		{
			std::cerr << "Line Renderer Index out of bounds\n";
		}
		else
		{
			vertices[index] = position;
		}
	}
private:
	std::vector<glm::vec3> vertices;
	int numVertices;

	GLuint VAO, VBO;
	GLint viewLoc, projLoc, colourLoc, shaderProgram;
	Shader* shader;
	GLfloat* colour;


};
