#include "SceneNode.h"
#include <algorithm>
#include <glm\gtc\type_ptr.hpp>

SceneNode::SceneNode()
	:position(glm::vec3(0.0f)),
	rotation(glm::mat4(1.0f)),
	scaleVec(glm::vec3(1.0f))
{

}


SceneNode::SceneNode(const glm::vec3& _position, const glm::mat4& _rotation, const glm::vec3& _scale)
	:position(_position),
	rotation(_rotation),
	scaleVec(_scale)
{

}


SceneNode::~SceneNode()
{
	parent = NULL;
	for (uint i = 0; i < models.size(); i++)
	{
		if (models[i])
		{
			delete models[i];
			models[i] = NULL;
		}
	}
	for (uint i = 0; i < children.size(); i++)
	{
		if (children[i])
		{
			delete children[i];
			children[i] = NULL;
		}
	}
}


void SceneNode::AddChild(SceneNode* node)
{
	children.push_back(node);
	node->parent = this;
}

void SceneNode::RemoveChild(SceneNode* node)
{
	node->parent = NULL;
	children.erase(std::remove(children.begin(), children.end(), node), children.end());
}
void SceneNode::AddModel(Model* model)
{
	models.push_back(model);
	//model->sceneNode = this;
}
void SceneNode::RemoveModel(Model* model)
{
	models.erase(std::remove(models.begin(), models.end(), model), models.end());
	//model->sceneNode = NULL;
}

void SceneNode::RenderSceneNode(const Renderer* renderer, const Camera* camera) const
{
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::scale(modelMatrix, scaleVec);
	modelMatrix = rotation*modelMatrix;
	modelMatrix = glm::translate(modelMatrix, position);

	for (Model* model: models)
	{
		model->shader->Use();
		glUniformMatrix4fv(model->shader->GetStandardUniformLoc(ModelMatrix), 1, GL_FALSE, glm::value_ptr(modelMatrix));
		glUniformMatrix4fv(model->shader->GetStandardUniformLoc(ViewMatrix), 1, GL_FALSE, glm::value_ptr(camera->View()));
		glUniformMatrix4fv(model->shader->GetStandardUniformLoc(ProjectionMatrix), 1, GL_FALSE, glm::value_ptr(camera->Projection()));
	
		renderer->RenderModel(model);
		
		glUseProgram(0);
	}
	for (SceneNode* childNode: children)
	{
		childNode->RenderSceneNode(renderer, camera);
	}
	
	/*for (uint i = 0; i < models.size(); i++)
	{
		
	}
	for (uint i = 0; i < children.size(); i++)
	{

	}*/
}

void SceneNode::UpdateSceneNode(float dt)
{
	
}

void SceneNode::SetTransform(const glm::vec3& _position, const glm::mat4& _rotation, const glm::vec3& _scale)
{
	this->position = _position;
	this->rotation = _rotation;
	this->scaleVec = _scale;
}
