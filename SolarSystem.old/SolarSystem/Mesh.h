#pragma once
#include <vector>
#include <string>

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <assimp/scene.h>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
};
struct Texture
{
	GLuint id;
	std::string type;
	aiString path;
};
class Mesh
{
private:
	GLuint VAO, VBO, EBO;

public:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	Mesh();
	~Mesh();
	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
	void Render(GLint shaderProgram) const;

private:
	void Init();


};

