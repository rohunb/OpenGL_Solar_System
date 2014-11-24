#pragma once
#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "Shader.h"

class Model
{
private:
	std::vector<Mesh> meshes;
	std::string directory;

	void LoadModel(std::string path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

public:
	Shader* shader;

	Model();
	~Model();
	Model(GLchar* path);
	Model(GLchar* path, Shader* shader);
	void Render() const;
	static GLint TextureFromFile(const char* path, std::string directory);
};

