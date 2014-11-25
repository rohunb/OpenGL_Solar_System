#include "SceneNode.h"
#include <algorithm>
#include <glm\gtc\type_ptr.hpp>

SceneNode::SceneNode()
	:position(glm::vec3(0.0f)),
	rotation(glm::mat4(1.0f)),
	scaleVec(glm::vec3(1.0f))
{
	angle = 0.0f;
}


SceneNode::SceneNode(const glm::vec3& _position, const glm::mat4& _rotation, const glm::vec3& _scale)
	:position(_position),
	rotation(_rotation),
	scaleVec(_scale)
{
	angle = 0.0f;
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

void SceneNode::RenderSceneNode(const Renderer* renderer, const Camera* camera, const Light& light) const
{
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::scale(modelMatrix, scaleVec);
	modelMatrix = glm::translate(modelMatrix, position);
	modelMatrix = modelMatrix*rotation;

	if (parent)
	{
		//modelMatrix = parent->GetTransformMatrix() * modelMatrix;
		modelMatrix = glm::translate(glm::mat4(1.0f), parent->position) * modelMatrix;
	}

	for (Model* model : models)
	{
		model->shader->Use();

		GLint matSpecLoc = glGetUniformLocation(model->shader->Program(), "uMaterial.specular");
		glUniform3f(matSpecLoc, model->specular.x, model->specular.y, model->specular.z);
		GLint matShinLoc = glGetUniformLocation(model->shader->Program(), "uMaterial.shininess");
		glUniform1f(matShinLoc, model->shininess);

		/*GLint lightPosLoc = glGetUniformLocation(model->shader->Program(), "uLight.position");
		glUniform3f(lightPosLoc, light.position.x, light.position.y, light.position.z);
		GLint lightAmbLoc = glGetUniformLocation(model->shader->Program(), "uLight.ambient");
		glUniform3f(lightAmbLoc, light.ambient.x, light.ambient.y, light.ambient.z);
		GLint lightDiffLoc = glGetUniformLocation(model->shader->Program(), "uLight.diffuse");
		glUniform3f(lightDiffLoc, light.diffuse.x, light.diffuse.y, light.diffuse.z);
		GLint lightSpecLoc = glGetUniformLocation(model->shader->Program(), "uLight.specular");
		glUniform3f(lightSpecLoc, light.specular.x, light.specular.y, light.specular.z);*/

		glUniformMatrix4fv(model->shader->GetStandardUniformLoc(ModelMatrix), 1, GL_FALSE, glm::value_ptr(modelMatrix));
		glUniformMatrix4fv(model->shader->GetStandardUniformLoc(ViewMatrix), 1, GL_FALSE, glm::value_ptr(camera->View()));
		glUniformMatrix4fv(model->shader->GetStandardUniformLoc(ProjectionMatrix), 1, GL_FALSE, glm::value_ptr(camera->Projection()));
		GLint viewPosLoc = glGetUniformLocation(model->shader->Program(), "uViewPos");
		glUniform3f(viewPosLoc, camera->Position().x, camera->Position().y, camera->Position().z);

		renderer->RenderModel(model);

		glUseProgram(0);
	}
	for (SceneNode* childNode : children)
	{
		childNode->RenderSceneNode(renderer, camera,light);
	}

}

void SceneNode::UpdateSceneNode(float dt)
{
	rotation = glm::rotate(rotation, 1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	//angle += 0.5f;
	for (SceneNode* childNode: children)
	{
		childNode->UpdateSceneNode(dt);
	}
}

void SceneNode::SetTransform(const glm::vec3& _position, const glm::mat4& _rotation, const glm::vec3& _scale)
{
	this->position = _position;
	this->rotation = _rotation;
	this->scaleVec = _scale;
}

glm::mat4 SceneNode::GetTransformMatrix() const
{
	glm::mat4 transformMatrix = glm::mat4(1.0f);
	transformMatrix = glm::scale(transformMatrix, scaleVec);
	transformMatrix = rotation*transformMatrix;
	transformMatrix = glm::translate(transformMatrix, position);
	return transformMatrix;
}
