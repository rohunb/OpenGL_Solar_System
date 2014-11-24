#include "GameApp.h"

GameApp::GameApp()
{
	renderer = new Renderer(1024, 1024, 600, 0, "Solar System", GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	sceneGraph = new SceneGraph();
	InitializeGameData();
	SetupScene();
}

GameApp::~GameApp()
{
	if (renderer)
	{
		delete renderer;
		renderer = NULL;
	}
	if (sceneGraph)
	{
		delete sceneGraph;
		sceneGraph = NULL;
	}
	if (camera)
	{
		delete camera;
		camera = NULL;
	}
	
}

void GameApp::InitializeGameData()
{

}
void GameApp::SetupScene()
{
	camera = new Camera(glm::vec3(0.0f, 0.0f, 15.0f));
	
	earth = new Model("Art/Earth/sphere.obj");
	Shader* shader = new Shader("unlit_textured_Shader.vert", "unlit_textured_Shader.frag");
	shader->HandleStandardUniforms("uModel", "uView", "uProjection");
	earth->shader = shader;

	sceneGraph->root->AddModel(earth);
	sceneGraph->root->SetTransform(glm::vec3(-1.0f, -1.0, 0.0f), glm::rotate(glm::mat4(1.0f), 30.0f, glm::vec3(0.0f, 0.0f, 1.0f)), glm::vec3(3.0f));

	moon = new Model("Art/Moon/sphere.obj",shader);
	SceneNode* moonNode = new SceneNode(glm::vec3(0.0f, 0.0f, 0.0f), glm::mat4(1.0f), glm::vec3(1.0f));
	moonNode->AddModel(moon);
	sceneGraph->root->AddChild(moonNode);
	
}
void GameApp::ProcessInput()
{

}

void GameApp::Update()
{
	sceneGraph->UpdateSceneGraph(dt);
}

void GameApp::Display()
{
	renderer->PreRender();
	sceneGraph->RenderSceneGraph(renderer, camera);
}


