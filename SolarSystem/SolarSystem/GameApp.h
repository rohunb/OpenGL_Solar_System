#pragma once
#include "Renderer.h"
#include "Model.h"
#include "Camera.h"
#include "Input.h"
#include "Light.h"
#include "SolarSystem.h"

class GameApp
{
private:
	const float dt = 0.16f;
	const int windowHeight = 1024;
	const int windowWidth = 1024;

	//Engine components
	Renderer* renderer;
	//SceneGraph* sceneGraph;

	//Game Objects
	SolarSystem* solarSystem;

	Camera* camera;
	Light light;

	//game values
	float cameraMoveSpeed;

public:
	GameApp();
	~GameApp();
	
	void Update();
	void Display();

private:

	void InitializeGameData();
	void SetupScene();
	void ProcessInput();
	static void Keyboard(unsigned char key, int x, int y);
	static void KeyboardUp(unsigned char key, int x, int y);
	

	
};

