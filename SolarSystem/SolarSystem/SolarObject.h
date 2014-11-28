#pragma once
#include "Model.h"
#include "Renderer.h"
#include "Camera.h"

class SolarObject
{
private: 
	SolarObject* parent;
	Model* model;
	float angle;

	std::vector<SolarObject*> satellites;

public:
	//transform variables
	glm::vec3 position, scale;
	glm::mat4 rotation;

	//physics variables
	glm::vec3 linearVelocity;
	float rotationPeriod;
	float orbitRadius;
	float orbitPeriod;

	SolarObject();
	SolarObject(const glm::vec3& position, const glm::mat4& rotation, const glm::vec3& scale, Model* model=nullptr);
	SolarObject(const glm::vec3& position, const glm::mat4& rotation, const glm::vec3& scale, float rotationPeriod, float orbitRadius, float orbitPeriod, Model* model = nullptr);
	SolarObject(float rotationPeriod, float orbitRadius, float orbitPeriod, Model* model = nullptr);
	~SolarObject();

	void SetTransform(const glm::vec3& position, const glm::mat4& rotation, const glm::vec3& scale);
	glm::mat4 Transform() const;
	void AddSatellite(SolarObject* solarObject);
	void RemoveSatellite(SolarObject* solarObject);
	void SetModel(Model* model);
	void RenderSolarObject(const Renderer* renderer, const Camera* camera) const;
	void UpdateSolarObject(float dt);

};

