#include "GameApp.h"

GameApp::GameApp()
{
	renderer = new Renderer(windowHeight, windowWidth, 600, 0, "Solar System", GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
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
	currentTime = 0.0f;
	keyPressInterval = 1.0f;
	numOrbitVertices = 360;
}
void GameApp::SetupScene()
{
	camera = new Camera(glm::vec3(15.0f, 5.0f, 205.0f)); //15,205
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

	Shader* lineShader = new Shader("line_renderer_shader.vert", "line_renderer_shader.frag");
	lineShader->HandleStandardUniforms(NULL, "uView", "uProjection");


	Model* sunModel = new Model("Art/Sun/sphere.obj", planetShader);
	solarSystem->sun->SetModel(sunModel);
	solarSystem->sun->scale = glm::vec3(20.0f);
	solarSystem->sun->rotationPeriod = 1000.0f;
	light.position = glm::vec3(solarSystem->sun->position);
	light.ambient = glm::vec3(0.8f);//white-ish
	light.diffuse = glm::vec3(0.8f, 0.8f, 0.2f);//yellow-ish
	light.specular = glm::vec3(1.0f, 1.0f, 0.0f);

	Model* mercury = new Model("Art/Mercury/sphere.obj", planetShader);
	SolarObject* mercuryObj = new SolarObject(59.0f, 25.79f , 488.0f, mercury);
	mercuryObj->scale = glm::vec3(0.3f);
	solarSystem->sun->AddSatellite(mercuryObj);
	AddOrbitVertices(25.79f);

	Model* venus = new Model("Art/Venus/sphere.obj", planetShader);
	SolarObject* venusObj = new SolarObject(70.0f, 30.0f , 324.7f, venus);
	venusObj->scale = glm::vec3(0.95f);
	solarSystem->sun->AddSatellite(venusObj);
	AddOrbitVertices(30.0f);

	Model* earth = new Model("Art/Earth/sphere.obj", planetShader);
	SolarObject* earthObj = new SolarObject(1.0f, 35.0f, 965.5f, earth);
	earthObj->scale = glm::vec3(1.0f);
	solarSystem->sun->AddSatellite(earthObj);
	AddOrbitVertices(35.0f);

		Model* moon = new Model("Art/Moon/sphere.obj", planetShader);
		SolarObject* moonObj = new SolarObject(27.3f, 2.0f, 27.3f, moon);
		moonObj->scale = glm::vec3(0.3f);
		earthObj->AddSatellite(moonObj);

	Model* mars = new Model("Art/Mars/sphere.obj", planetShader);
	SolarObject* marsObj = new SolarObject(1.0f, 42.79f , 686.98f, mars);
	marsObj->scale = glm::vec3(0.732f);
	solarSystem->sun->AddSatellite(marsObj);
	AddOrbitVertices(42.79f);

		Model* deimos = new Model("Art/Moon/sphere.obj", planetShader);
		SolarObject* deimosObj = new SolarObject(27.3f, 3.0f, 27.3f, deimos);
		deimosObj->scale = glm::vec3(0.3f);
		marsObj->AddSatellite(deimosObj);
		Model* phobos = new Model("Art/Moon/sphere.obj", planetShader);
		SolarObject* phobosObj = new SolarObject(273.3f, 1.0f, -273.3f, phobos);
		phobosObj->scale = glm::vec3(0.1f);
		marsObj->AddSatellite(phobosObj);


	Model* jupiter = new Model("Art/Jupiter/sphere.obj", planetShader);
	SolarObject* jupiterObj = new SolarObject(2.4f, 77.0f , 5.86f*365.0f, jupiter);
	jupiterObj->scale = glm::vec3(11.19f);
	/*SolarObject* jupiterObj = new SolarObject(2.4f, 77.0f , 1.86f*365.0f, jupiter);
	jupiterObj->scale = glm::vec3(1.0f);*/
	solarSystem->sun->AddSatellite(jupiterObj);
	AddOrbitVertices(77.0f);

		Model* jMoon1 = new Model("Art/Moon/sphere.obj", planetShader);
		SolarObject* jMoonObj1 = new SolarObject(100.0f, 15.0f, -50.0f, jMoon1);
		jupiterObj->AddSatellite(jMoonObj1);
		Model* jMoon2 = new Model("Art/Mars/sphere.obj", planetShader);
		SolarObject* jMoonObj2 = new SolarObject(-10.0f, 20.0f, 500.0f, jMoon2);
		jupiterObj->AddSatellite(jMoonObj2);
		Model* jMoon3 = new Model("Art/Neptune/sphere.obj", planetShader);
		SolarObject* jMoonObj3 = new SolarObject(50.0f, 25.0f, -360.0f, jMoon3);
		jupiterObj->AddSatellite(jMoonObj3);
		Model* jMoon4 = new Model("Art/Uranus/sphere.obj", planetShader);
		SolarObject* jMoonObj4 = new SolarObject(70.0f, 27.0f, 50.0f, jMoon4);
		jupiterObj->AddSatellite(jMoonObj4);

	Model* saturn = new Model("Art/Saturn/sphere.obj", planetShader);
	SolarObject* saturnObj = new SolarObject(2.3f, 121.0f, -29.41f*365.0f, saturn);
	saturnObj->scale = glm::vec3(9.26f);
	solarSystem->sun->AddSatellite(saturnObj);
	AddOrbitVertices(121.0f);

		Model* sMoon1 = new Model("Art/Jupiter/sphere.obj", planetShader);
		SolarObject* sMoonObj1 = new SolarObject(100.0f, 15.0f, -50.0f, sMoon1);
		saturnObj->AddSatellite(sMoonObj1);
		Model* sMoon2 = new Model("Art/Mars/sphere.obj", planetShader);
		SolarObject* sMoonObj2 = new SolarObject(-10.0f, 12.0f, 50.0f, sMoon2);
		saturnObj->AddSatellite(sMoonObj2);
		Model* sMoon3 = new Model("Art/Neptune/sphere.obj", planetShader);
		SolarObject* sMoonObj3 = new SolarObject(50.0f, 11.0f, -160.0f, sMoon3);
		saturnObj->AddSatellite(sMoonObj3);
	

	Model* uranus = new Model("Art/Uranus/sphere.obj", planetShader);
	SolarObject* uranusObj = new SolarObject(24.0f / 17.2f, 225.07f , 18.404f*365.0f, uranus);
	uranusObj->scale = glm::vec3(4.01f);
	solarSystem->sun->AddSatellite(uranusObj);
	AddOrbitVertices(225.07f);

		Model* uMoon1 = new Model("Art/Neptune/sphere.obj", planetShader);
		SolarObject* uMoonObj1 = new SolarObject(100.0f, 6.0f, -50.0f, uMoon1);
		uranusObj->AddSatellite(uMoonObj1);
		Model* uMoon2 = new Model("Art/Mars/sphere.obj", planetShader);
		SolarObject* uMoonObj2 = new SolarObject(-10.0f, 8.0f, 50.0f, uMoon2);
		uranusObj->AddSatellite(uMoonObj2);
		

	Model* neptune = new Model("Art/Neptune/sphere.obj", planetShader);
	SolarObject* neptuneObj = new SolarObject(24.0f / 16.11f, 341.2f, 46.48f*365.0f, neptune);
	neptuneObj->scale = glm::vec3(3.88f);
	solarSystem->sun->AddSatellite(neptuneObj);
	AddOrbitVertices(341.2f);

		Model* nMoon1 = new Model("Art/Jupiter/sphere.obj", planetShader);
		SolarObject* nMoonObj1 = new SolarObject(100.0f, 6.0f, -50.0f, nMoon1);
		neptuneObj->AddSatellite(nMoonObj1);
		Model* nMoon2 = new Model("Art/Mars/sphere.obj", planetShader);
		SolarObject* nMoonObj2 = new SolarObject(-10.0f, 8.0f, 50.0f, nMoon2);
		neptuneObj->AddSatellite(nMoonObj2);

	orbitLineRenderer = new LineRenderer(lineShader, orbitLineVertices);
	orbitLineRenderer->SetColour(glm::vec3(0.4f));
}
void GameApp::Update()
{
	currentTime += dt;
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
	orbitLineRenderer->Render(camera);
}

void GameApp::ProcessInput()
{
	if (currentTime > keyPressInterval)
	{
		if (Input::GetInstance().keyStates['p']
			|| Input::GetInstance().keyStates['P'])
		{
			paused = !paused;
			currentTime = 0.0f;
		}
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

void GameApp::AddOrbitVertices(float radius)
{
	float t = 0.0f;
	for (int i = 0; i < numOrbitVertices; i++)
	{
		glm::vec3 pos = glm::vec3(0.0f);
		pos.x += radius * glm::sin(glm::radians(t));
		pos.z += radius * glm::cos(glm::radians(t));
		orbitLineVertices.push_back(pos);
		t += 360.0f / (numOrbitVertices - 1);
	}
}




