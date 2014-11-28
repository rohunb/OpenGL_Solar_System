#include "SolarObject.h"
#include <algorithm>
#include <glm\gtc\type_ptr.hpp>

SolarObject::SolarObject()
	:position(glm::vec3(0.0f)),
	rotation(glm::mat4(1.0f)),
	scale(glm::vec3(1.0f)),
	rotationPeriod(1.0f),
	orbitRadius(0.0f),
	orbitPeriod(10.0f),
	model(nullptr)
{

}

SolarObject::SolarObject(const glm::vec3& _position, const glm::mat4& _rotation, const glm::vec3& _scale, Model* _model)
	:position(_position),
	rotation(_rotation),
	scale(_scale),
	rotationPeriod(1.0f),
	orbitRadius(0.0f),
	orbitPeriod(10.0f),
	model(_model)
{

}

SolarObject::SolarObject(const glm::vec3& _position, const glm::mat4& _rotation, const glm::vec3& _scale, float _rotationPeriod, float _orbitRadius, float _orbitPeriod, Model* _model)
	:position(_position),
	rotation(_rotation),
	scale(_scale),
	rotationPeriod(_rotationPeriod),
	orbitRadius(_orbitRadius),
	orbitPeriod(_orbitPeriod),
	model(_model)
{

}

SolarObject::SolarObject(float _rotationPeriod, float _orbitRadius, float _orbitPeriod, Model* _model)
	:position(glm::vec3(0.0f)),
	rotation(glm::mat4(1.0f)),
	scale(glm::vec3(1.0f)),
	rotationPeriod(_rotationPeriod),
	orbitRadius(_orbitRadius),
	orbitPeriod(_orbitPeriod),
	model(_model)
{

}
void SolarObject::RenderSolarObject(const Renderer* renderer, const Camera* camera) const
{
	glm::mat4 rotMat, transMat, scaleMat;
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	//scaleMat = glm::scale(glm::mat4(1.0f), scale);
	//modelMatrix = glm::rotate(modelMatrix, angle, glm::vec3(0.0f, 1.0f, 0.0f));
	//modelMatrix = rotation*modelMatrix;
	/*if (parent)
	{
	modelMatrix = glm::translate(modelMatrix, glm::vec3(parent->orbitRadius, 0.0f, 0.0f));
	}*/
	//modelMatrix = glm::translate(modelMatrix, glm::vec3(orbitRadius, 0.0f, 0.0f));

	/*else
	{
	modelMatrix = glm::translate(modelMatrix, position);
	}*/
	//modelMatrix = glm::rotate(modelMatrix, angle, glm::vec3(0.0f, 1.0f, 0.0f));
	//modelMatrix = glm::translate(modelMatrix, position);
	/*if (parent)
	{
		modelMatrix = parent->Transform()*Transform();
	}
	else*/
	{
		modelMatrix = Transform();
	}

	//if (parent)
	//{
	//	modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(parent->orbitRadius, 0.0f, 0.0f))*modelMatrix;
	//	modelMatrix = glm::rotate(glm::mat4(1.0f), parent->angle, glm::vec3(0.0f, 1.0f, 0.0f))*modelMatrix;

	//	//modelMatrix = glm::translate(modelMatrix, parent->position + position);
	//}
	//modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(orbitRadius, 0.0f, 0.0f))*modelMatrix;
	//modelMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f))*modelMatrix;

	//modelMatrix = rotMat*transMat*scaleMat;

	//glm::mat4 modelMatrix = glm::mat4(1.0f);
	///*if (parent)
	//{
	//	modelMatrix = glm::translate(glm::mat4(1.0f), parent->position)*modelMatrix;
	//}
	//modelMatrix = glm::scale(modelMatrix, scale);
	//modelMatrix = glm::translate(modelMatrix, position);
	//modelMatrix = modelMatrix*rotation;*/
	//modelMatrix = glm::scale(modelMatrix, scale);
	//
	//if (parent)
	//{
	//	modelMatrix = glm::translate(glm::mat4(1.0f), parent->position)*modelMatrix;
	//	position = position + parent->position;
	//}
	////modelMatrix = glm::scale(modelMatrix, scale);
	//modelMatrix = rotation*modelMatrix;
	//modelMatrix = glm::translate(modelMatrix, position);



	/*glm::mat4 modelMatrix = glm::mat4(1.0f);
	glm::vec3 newPos = position;
	if (parent)
	{
	newPos += parent->position;
	}
	modelMatrix = glm::scale(modelMatrix, scale);

	modelMatrix = glm::translate(modelMatrix, newPos);
	modelMatrix = modelMatrix*rotation;*/

	if (model)
	{
		model->shader->Use();
		GLint matSpecLoc = glGetUniformLocation(model->shader->Program(), "uMaterial.specular");
		glUniform3f(matSpecLoc, model->specular.x, model->specular.y, model->specular.z);
		GLint matShinLoc = glGetUniformLocation(model->shader->Program(), "uMaterial.shininess");
		glUniform1f(matShinLoc, model->shininess);
		GLint viewPosLoc = glGetUniformLocation(model->shader->Program(), "uViewPos");
		glUniform3f(viewPosLoc, camera->Position().x, camera->Position().y, camera->Position().z);

		glUniformMatrix4fv(model->shader->GetStandardUniformLoc(ModelMatrix), 1, GL_FALSE, glm::value_ptr(modelMatrix));
		glUniformMatrix4fv(model->shader->GetStandardUniformLoc(ViewMatrix), 1, GL_FALSE, glm::value_ptr(camera->View()));
		glUniformMatrix4fv(model->shader->GetStandardUniformLoc(ProjectionMatrix), 1, GL_FALSE, glm::value_ptr(camera->Projection()));

		renderer->RenderModel(model);

		glUseProgram(0);
	}
	for (SolarObject* solarObject : satellites)
	{
		solarObject->RenderSolarObject(renderer, camera);
	}
}


void SolarObject::UpdateSolarObject(float dt)
{
	//rotation
	rotation = glm::rotate(rotation, dt / rotationPeriod*10.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	//revolution
	float orbitCircum = 2.0f*glm::pi<float>() * orbitRadius;
	angle += dt*orbitCircum / orbitPeriod * 10.0f;
	if (angle >= 360.0f)
	{
		angle = 0.0f;
	}
	printf("angle: %f\n", angle);

	if (parent)
	{
		position = parent->position;
		position.x += orbitRadius*glm::cos(glm::radians(angle));
		position.z += orbitRadius*glm::sin(glm::radians(angle));
	}
	else
	{
		position.x = orbitRadius*glm::cos(glm::radians(angle));
		position.z = orbitRadius*glm::sin(glm::radians(angle));
	}

	/*if (parent)
	{
		position.x = parent->position.x + orbitRadius*glm::cos(glm::radians(angle));
		position.z = parent->position.z + orbitRadius*glm::sin(glm::radians(angle));
	}*/
	for (SolarObject* satellite : satellites)
	{
		satellite->UpdateSolarObject(dt);
	}

	//modelMatrix = glm::mat4(1.0f);
	///*if (parent)
	//{
	//	modelMatrix = glm::translate(glm::mat4(1.0f), parent->position)*modelMatrix;
	//}
	//modelMatrix = glm::scale(modelMatrix, scale);
	//modelMatrix = glm::translate(modelMatrix, position);
	//modelMatrix = modelMatrix*rotation;*/
	//modelMatrix = glm::scale(modelMatrix, scale);
	//modelMatrix = rotation*modelMatrix;
	//if (parent)
	//{
	//	modelMatrix = glm::translate(glm::mat4(1.0f), parent->position)*modelMatrix;
	//	
	//}
	////modelMatrix = glm::scale(modelMatrix, scale);
	//
	//modelMatrix = glm::translate(modelMatrix, position);
	//if (parent)
	//{
	//	position = position + parent->position;
	//}
}

SolarObject::~SolarObject()
{
	parent = nullptr;
	if (model)
	{
		delete model;
		model = nullptr;
	}
	for (SolarObject* solarObject : satellites)
	{
		if (solarObject)
		{
			delete solarObject;
			solarObject = nullptr;
		}
	}
}

void SolarObject::AddSatellite(SolarObject* solarObject)
{
	satellites.push_back(solarObject);
	solarObject->parent = this;
}

void SolarObject::RemoveSatellite(SolarObject* solarObject)
{
	solarObject->parent = nullptr;
	satellites.erase(std::remove(satellites.begin(), satellites.end(), solarObject), satellites.end());
}

void SolarObject::SetModel(Model* model)
{
	this->model = model;
}



void SolarObject::SetTransform(const glm::vec3& position, const glm::mat4& rotation, const glm::vec3& scale)
{
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}

glm::mat4 SolarObject::Transform() const
{
	glm::mat4 transform;
	transform = glm::translate(glm::mat4(1.0f), position)*rotation*glm::scale(glm::mat4(1.0f), scale) * transform;
	/*transform =  * transform;
	transform =  * transform;*/
	return transform;
}
