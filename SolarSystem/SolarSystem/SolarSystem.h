#pragma once
#include "SolarObject.h"

class SolarSystem
{
public:
	SolarObject* sun;

	SolarSystem();
	SolarSystem(SolarObject* sun);
	~SolarSystem();

	void RenderSolarSystem(const Renderer* renderer, const Camera* camera) const;
	void UpdateSolarSystem(float dt);
};

