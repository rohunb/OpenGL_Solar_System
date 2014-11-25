#include "GameApp.h"

GameApp::GameApp()
{
	renderer = new Renderer(1024, 1024, 600, 0, "Solar System", GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	sceneGraph = new SceneGraph();

	glutKeyboardFunc(GameApp::Keyboard);
	glutKeyboardUpFunc(GameApp::KeyboardUp);
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
	cameraMoveSpeed = 1.0f;
}
void GameApp::SetupScene()
{
	camera = new Camera(glm::vec3(0.0f, 0.0f, 15.0f));
	light.position = glm::vec3(-2.0f,0.0f,2.0f);
	light.ambient = glm::vec3(0.8f);//white-ish
	light.diffuse = glm::vec3(0.8f, 0.8f, 0.8f);//white-ish
	light.specular = glm::vec3(1.0f);

	Shader* shader = new Shader("lit_textured_Shader.vert", "lit_textured_Shader.frag");
	shader->HandleStandardUniforms("uModel", "uView", "uProjection");

	shader->Use();
	//setup light in shader
	GLint lightPosLoc = glGetUniformLocation(shader->Program(), "uLight.position");
	glUniform3f(lightPosLoc, light.position.x, light.position.y, light.position.z);
	GLint lightAmbLoc = glGetUniformLocation(shader->Program(), "uLight.ambient");
	glUniform3f(lightAmbLoc, light.ambient.x, light.ambient.y, light.ambient.z);
	GLint lightDiffLoc = glGetUniformLocation(shader->Program(), "uLight.diffuse");
	glUniform3f(lightDiffLoc, light.diffuse.x, light.diffuse.y, light.diffuse.z);
	GLint lightSpecLoc = glGetUniformLocation(shader->Program(), "uLight.specular");
	glUniform3f(lightSpecLoc, light.specular.x, light.specular.y, light.specular.z);
	glUseProgram(0);

	earth = new Model("Art/Earth/sphere.obj", shader);
	earth->specular = glm::vec3(.3f, 0.3f, 0.3f);
	earth->shininess = 4.0f;

	sceneGraph->root->AddModel(earth);
	sceneGraph->root->SetTransform(glm::vec3(-2.0f, 0.0, 0.0f), 
		//glm::rotate(glm::mat4(1.0f), -0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), 
		glm::mat4(1.0f),
		glm::vec3(1.0f));

	moon = new Model("Art/Moon/sphere.obj",shader);
	moon->specular = glm::vec3(.3f, 0.3f, 0.3f);
	moon->shininess = 4.0f;
	SceneNode* moonNode = new SceneNode(glm::vec3(4.0f, 0.0f, 0.0f), glm::mat4(1.0f), glm::vec3(.3f));
	moonNode->AddModel(moon);
	sceneGraph->root->AddChild(moonNode);
	
}
void GameApp::ProcessInput()
{
	glm::vec3 camMoveDir = glm::vec3(0.0f);
	if (Input::GetInstance().keyStates['w']
		|| Input::GetInstance().keyStates['W'])
	{
		camMoveDir.z -= cameraMoveSpeed*dt;
	}
	if (Input::GetInstance().keyStates['s']
		|| Input::GetInstance().keyStates['S'])
	{
		camMoveDir.z += cameraMoveSpeed*dt;
	}
	if (Input::GetInstance().keyStates['a']
		|| Input::GetInstance().keyStates['A'])
	{
		camMoveDir.x -= cameraMoveSpeed*dt;
	}
	if (Input::GetInstance().keyStates['d']
		|| Input::GetInstance().keyStates['D'])
	{
		camMoveDir.x += cameraMoveSpeed*dt;
	}
	camera->MoveCamera(camMoveDir);

	
}

void GameApp::Update()
{
	ProcessInput();
	sceneGraph->UpdateSceneGraph(dt);
}

void GameApp::Display()
{
	renderer->PreRender();
	sceneGraph->RenderSceneGraph(renderer, camera);
}

void GameApp::Keyboard(unsigned char key, int x, int y)
{
	Input::GetInstance().KeyPressed(key, x, y);
}

void GameApp::KeyboardUp(unsigned char key, int x, int y)
{
	Input::GetInstance().KeyUp(key, x, y);
}


