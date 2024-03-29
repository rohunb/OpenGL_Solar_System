#include "LineRenderer.h"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

LineRenderer::LineRenderer()
	:numVertices(0),
	shader(nullptr)
{
	Init();
}

LineRenderer::LineRenderer(Shader* _shader, int _numVertices)
	:shader(_shader)
{
	NumVertices(_numVertices);
	Init();
}

LineRenderer::LineRenderer(Shader* _shader, const std::vector<glm::vec3>& _vertices)
	: numVertices(_vertices.size()),
	shader(_shader),
	vertices(_vertices)
{
	Init();
}
LineRenderer::LineRenderer(const std::vector<glm::vec3>& _vertices)
	:numVertices(_vertices.size()),
	shader(nullptr),
	vertices(_vertices)
{
	Init();
}
LineRenderer::~LineRenderer()
{
	if (shader)
	{
		delete shader;
		shader = nullptr;
	}
}
void LineRenderer::ReGenArrays()
{
	if (NumVertices() < 1)
	{
		return;
	}
	glGenVertexArrays(1, &VBO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, NumVertices()*3*sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}
void LineRenderer::Init()
{
	printf("line init\n");
	SetColour(glm::vec3(1.0f, 1.0f, 1.0f));

	if (!shader)
	{
		std::cerr << "Shader not loaded";
	}

	colourLoc = glGetUniformLocation(shader->Program(), "uColour");
	viewLoc = shader->GetStandardUniformLoc(ViewMatrix);
	projLoc = shader->GetStandardUniformLoc(ProjectionMatrix);

	if (NumVertices() < 1)
	{
		return;
	}
	glGenVertexArrays(1, &VBO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, NumVertices()*sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void LineRenderer::Render(const Camera* camera)
{
	if (NumVertices() < 1)
	{
		return;
	}
	if (!shader)
	{
		std::cerr << "Shader not loaded";
	}
	shader->Use();
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera->View()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera->Projection()));
	glUniform3fv(colourLoc, 1, colour);

	glBindVertexArray(VAO);
	glDrawArrays(GL_LINES, 0, numVertices);
	glBindVertexArray(0);

	glUseProgram(0);
}

