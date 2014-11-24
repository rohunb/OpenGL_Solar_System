#pragma once
#include "Renderer.h"
#include "SceneGraph.h"
#include "Model.h"
#include "Camera.h"

class GameApp
{
private:
	const float dt = 0.16f;
	
	//Engine components
	Renderer* renderer;
	SceneGraph* sceneGraph;

	//Game Objects
	Camera* camera;
	Model* earth;
	Model* moon;

public:
	GameApp();
	~GameApp();
	
	void Update();
	void Display();

private:

	void InitializeGameData();
	void SetupScene();
	void ProcessInput();
	

	
};

