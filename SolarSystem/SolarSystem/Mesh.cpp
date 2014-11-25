#include "Mesh.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "Shader.h"

Mesh::Mesh(){}
Mesh::~Mesh(){}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
	Init();
}
void Mesh::Init()
{

#define VERTEX_SIZE sizeof(Vertex)

	glGenVertexArrays(1,&VAO);
	glGenBuffers(1,&VBO);
	glGenBuffers(1,&EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*VERTEX_SIZE, &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(VertexAttrib, sizeof(GL_FLOAT), GL_FLOAT, GL_FALSE, VERTEX_SIZE, (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(NormalAttrib, sizeof(GL_FLOAT), GL_FLOAT, GL_FALSE, VERTEX_SIZE, (GLvoid*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(TexCoordAttrib, sizeof(GL_FLOAT), GL_FLOAT, GL_FALSE, VERTEX_SIZE, (GLvoid*)offsetof(Vertex, texCoord));
	glBindVertexArray(0);

#undef VERTEX_SIZE
}
void Mesh::Render(GLint shaderProgram) const
{
	GLuint diffuseNr = 1;
	GLuint specularNr = 1;
	for (GLuint i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		std::stringstream ss;
		std::string number;
		std::string name = textures[i].type;
		if (name == "texture_diffuse")
		{
			ss << diffuseNr++;
		}
		else if (name == "texture_specular")
		{
			ss << specularNr++;
		}
		number = ss.str();
		//printf("text: %s\n", ("uMaterial." + name + number).c_str());
		glUniform1i(glGetUniformLocation(shaderProgram, (name + number).c_str()), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}
	glActiveTexture(GL_TEXTURE0);

	//draw
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}


