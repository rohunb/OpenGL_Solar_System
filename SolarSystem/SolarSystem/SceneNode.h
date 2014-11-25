#pragma once
#include "glm\glm.hpp"
#include <vector>
#include "Model.h"
#include "Renderer.h"
#include "Camera.h"
#include "Light.h"

class SceneNode
{
private:

	SceneNode* parent;
	std::vector<Model*> models;
	std::vector<SceneNode*> children;

public:
	glm::vec3 position, scaleVec;
	glm::mat4 rotation;
	float angle;

	SceneNode();
	SceneNode(const glm::vec3& position, const glm::mat4& rotation, const glm::vec3& scale);
	~SceneNode();

	void SetTransform(const glm::vec3& position, const glm::mat4& rotation, const glm::vec3& scale);
	glm::mat4 GetTransformMatrix() const;
	void AddChild(SceneNode* node);
	void RemoveChild(SceneNode* node);
	void AddModel(Model* model);
	void RemoveModel(Model* model);
	void RenderSceneNode(const Renderer* renderer, const Camera* camera, const Light& light) const;
	void UpdateSceneNode(float dt);


};

