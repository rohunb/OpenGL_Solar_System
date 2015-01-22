#include "Renderer.h"
#include "GL/glut.h"

Renderer::Renderer(int width, int height, int posX, int posY, char* windowName, uint displayMode)
{
	glutInitDisplayMode(displayMode);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(posX, posY);
	glutCreateWindow(windowName);
	
	glewExperimental = GL_TRUE;
	glewInit();

	glEnable(GL_DEPTH_TEST);

}


Renderer::~Renderer()
{

}

void Renderer::PreRender() const
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Renderer::RenderModel(const Model* model) const
{
	model->Render();
}
