#pragma once
#include "Renderer.h"
#include "SceneGraph.h"
#include "Model.h"
#include "Camera.h"
#include "Input.h"
#include "Light.h"

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

