#include "SolarSystem.h"

SolarSystem::SolarSystem()
	:sun(new SolarObject())
{}

SolarSystem::SolarSystem(SolarObject* _sun)
	: sun(_sun)
{}

SolarSystem::~SolarSystem()
{
	if (sun)
	{
		delete sun;
		sun = nullptr;
	}
}

void SolarSystem::RenderSolarSystem(const Renderer* renderer, const Camera* camera) const
{
	if (sun)
	{
		sun->RenderSolarObject(renderer, camera);
	}
}

void SolarSystem::UpdateSolarSystem(float dt)
{
	if (sun)
	{
		sun->UpdateSolarObject(dt);
	}
}
