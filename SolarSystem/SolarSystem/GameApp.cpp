#include "GameApp.h"

GameApp::GameApp()
{
	renderer = new Renderer(windowHeight, windowWidth, 600, 0, "Solar System", GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	//sceneGraph = new SceneGraph();
	solarSystem = new SolarSystem();

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
		renderer = nullptr;
	}
	if (solarSystem)
	{
		delete solarSystem;
		solarSystem = nullptr;
	}
	if (camera)
	{
		delete camera;
		camera = nullptr;
	}
	
}

void GameApp::InitializeGameData()
{
	cameraMoveSpeed = 5.0f;
	paused = false;
}
void GameApp::SetupScene()
{
	camera = new Camera(glm::vec3(15.0f, 0.0f, 205.0f));
	camera->SetProjection(53.13f, (float)windowWidth / (float)windowHeight, 0.1f, 10000.0f);

	Shader* planetShader = new Shader("lit_textured_Shader.vert", "lit_textured_Shader.frag");
	planetShader->HandleStandardUniforms("uModel", "uView", "uProjection");

	planetShader->Use();
	//setup light in shader
	GLint lightPosLoc = glGetUniformLocation(planetShader->Program(), "uLight.position");
	glUniform3f(lightPosLoc, light.position.x, light.position.y, light.position.z);
	GLint lightAmbLoc = glGetUniformLocation(planetShader->Program(), "uLight.ambient");
	glUniform3f(lightAmbLoc, light.ambient.x, light.ambient.y, light.ambient.z);
	GLint lightDiffLoc = glGetUniformLocation(planetShader->Program(), "uLight.diffuse");
	glUniform3f(lightDiffLoc, light.diffuse.x, light.diffuse.y, light.diffuse.z);
	GLint lightSpecLoc = glGetUniformLocation(planetShader->Program(), "uLight.specular");
	glUniform3f(lightSpecLoc, light.specular.x, light.specular.y, light.specular.z);
	glUseProgram(0);

	/*Shader* lineShader = new Shader("line_renderer_shader.vert", "line_renderer_shader.frag");
	lineShader->HandleStandardUniforms(NULL, "uView", "uProjection");*/


	Model* sunModel = new Model("Art/Sun/sphere.obj", planetShader);
	solarSystem->sun->SetModel(sunModel);
	solarSystem->sun->scale = glm::vec3(20.0f);
	solarSystem->sun->rotationPeriod = 1000.0f;
	light.position = glm::vec3(solarSystem->sun->position);
	light.ambient = glm::vec3(0.8f);//white-ish
	light.diffuse = glm::vec3(0.8f, 0.8f, 0.2f);//yellow-ish
	light.specular = glm::vec3(1.0f,1.0f,0.0f);

	Model* mercury = new Model("Art/Mercury/sphere.obj", planetShader);
	SolarObject* mercuryObj = new SolarObject(59.0f, 25.79f/0.3f, 488.0f, mercury);
	mercuryObj->scale = glm::vec3(0.3f);
	solarSystem->sun->AddSatellite(mercuryObj);

	//LineRenderer mercuryOrbitLine = LineRenderer();

	Model* venus = new Model("Art/Venus/sphere.obj", planetShader);
	SolarObject* venusObj = new SolarObject(243.0f, 30.0f / 0.95f, 324.7f, venus);
	venusObj->scale = glm::vec3(0.95f);
	solarSystem->sun->AddSatellite(venusObj);
	

	Model* earth = new Model("Art/Earth/sphere.obj", planetShader);
	SolarObject* earthObj = new SolarObject(1.0f, 35.0f, 965.5f, earth);
	solarSystem->sun->AddSatellite(earthObj);

	
	Model* moon = new Model("Art/Moon/sphere.obj", planetShader);
	SolarObject* moonObj = new SolarObject(27.3f, 5.0f, 27.3f, moon);
	moonObj->scale = glm::vec3(0.3f);
	earthObj->AddSatellite(moonObj);

	Model* mars = new Model("Art/Mars/sphere.obj", planetShader);
	SolarObject* marsObj = new SolarObject(1.0f, 42.79f/0.532f, 686.98f, mars);
	marsObj->scale = glm::vec3(0.532f);
	solarSystem->sun->AddSatellite(marsObj);

	Model* jupiter = new Model("Art/Jupiter/sphere.obj", planetShader);
	SolarObject* jupiterObj = new SolarObject(2.4f, 77.0f / 11.19f, 1.86f*365.0f, jupiter);
	jupiterObj->scale = glm::vec3(11.19f);
	/*SolarObject* jupiterObj = new SolarObject(2.4f, 77.0f , 1.86f*365.0f, jupiter);
	jupiterObj->scale = glm::vec3(1.0f);*/
	solarSystem->sun->AddSatellite(jupiterObj);

	/*Model* jMoon1 = new Model("Art/Moon/sphere.obj", shader);
	SolarObject* jMoonObj1 = new SolarObject(10.0f, 30.0f, 50.0f, jMoon1);
	jupiterObj->AddSatellite(jMoonObj1);*/

	Model* saturn = new Model("Art/Saturn/sphere.obj", planetShader);
	SolarObject* saturnObj = new SolarObject(2.3f, 121.0f / 9.26f, 2.941f*365.0f, saturn);
	saturnObj->scale = glm::vec3(9.26f);
	solarSystem->sun->AddSatellite(saturnObj);

	Model* uranus = new Model("Art/Uranus/sphere.obj", planetShader);
	SolarObject* uranusObj = new SolarObject(24.0f / 17.2f, 225.07f / 4.01f, 8.404f*365.0f, uranus);
	uranusObj->scale = glm::vec3(4.01f);
	solarSystem->sun->AddSatellite(uranusObj);

	Model* neptune = new Model("Art/Neptune/sphere.obj", planetShader);
	SolarObject* neptuneObj = new SolarObject(24.0f / 16.11f, 341.2f / 3.88f, 16.48f*365.0f, neptune);
	neptuneObj->scale = glm::vec3(3.88f);
	solarSystem->sun->AddSatellite(neptuneObj);
		
}
void GameApp::Update()
{
	ProcessInput();
	if (!paused)
	{
		solarSystem->UpdateSolarSystem(dt);
	}
}

void GameApp::Display()
{
	renderer->PreRender();
	solarSystem->RenderSolarSystem(renderer, camera);
}

void GameApp::ProcessInput()
{
	if (Input::GetInstance().keyStates['p']
		|| Input::GetInstance().keyStates['P'])
	{
		paused = !paused;
	}


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



void GameApp::Keyboard(unsigned char key, int x, int y)
{
	Input::GetInstance().KeyPressed(key, x, y);
}

void GameApp::KeyboardUp(unsigned char key, int x, int y)
{
	Input::GetInstance().KeyUp(key, x, y);
}


