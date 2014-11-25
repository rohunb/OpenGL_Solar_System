//#include "LineRenderer.h"
//#include "glm\gtc\matrix_transform.hpp"
//#include "glm\gtc\type_ptr.hpp"
//
//LineRenderer::LineRenderer()
//	:numVertices(0),
//	shader(nullptr)
//{
//	
//	Init();
//}
//
//LineRenderer::LineRenderer(Shader* _shader)
//	:numVertices(0),
//	shader(_shader)
//{
//
//}
//LineRenderer::LineRenderer(const std::vector<glm::vec3>& vertices)
//{
//
//}
//LineRenderer::LineRenderer(const Shader* shader, const std::vector<glm::vec3>& vertices)
//{
//
//}
//LineRenderer::LineRenderer(const std::vector<glm::vec3>& vertices)
//{
//	NumVertices(vertices.size());
//	this->vertices = vertices;
//	SetColour(glm::vec3(.8f, 0.3f, 0.5f));
//}
//LineRenderer::~LineRenderer()
//{
//	if (shader)
//	{
//		delete shader;
//		shader = nullptr;
//	}
//}
//void LineRenderer::ReGenArrays()
//{
//	if (NumVertices() < 1)
//	{
//		return;
//	}
//	glGenVertexArrays(1, &VBO);
//	glGenBuffers(1, &VBO);
//
//	glBindVertexArray(VAO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, NumVertices()*3.0f*sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0.0f, (GLvoid*)0);
//	glEnableVertexAttribArray(0);
//
//	glBindVertexArray(0);
//}
//void LineRenderer::Init()
//{
//	SetColour(glm::vec3(.8f, 0.3f, 0.5f));
//	ShaderInfo shaders[] =
//	{
//		{ GL_VERTEX_SHADER, "line_renderer_shader.vert" },
//		{ GL_FRAGMENT_SHADER, "line_renderer_shader.frag" },
//		{ GL_NONE, NULL }
//	};
//	shaderProgram = LoadShaders(shaders);
//	if (shaderProgram == 0)
//	{
//		std::cerr << "Shader not loaded";
//	}
//	colourLoc = glGetUniformLocation(shaderProgram, "colour");
//	viewLoc = glGetUniformLocation(shaderProgram, "view");
//	projLoc = glGetUniformLocation(shaderProgram, "projection");
//
//	if (NumVertices() < 1)
//	{
//		return;
//	}
//	glGenVertexArrays(1, &VBO);
//	glGenBuffers(1, &VBO);
//
//	glBindVertexArray(VAO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, NumVertices()*3.0f*sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
//	
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0.0f, (GLvoid*)0);
//	glEnableVertexAttribArray(0);
//
//	glBindVertexArray(0);
//}
//
//void LineRenderer::Render(const glm::mat4& view, const glm::mat4& projection)
//{
//	if (NumVertices() < 1)
//	{
//		return;
//	}
//	if (shaderProgram == 0)
//	{
//		std::cerr << "Shader not loaded";
//	}
//	glUseProgram(shaderProgram);
//	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
//	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
//	glUniform3fv(colourLoc, 1, colour);
//
//	glBindVertexArray(VAO);
//	glDrawArrays(GL_LINE_STRIP, 0, numVertices);
//	glBindVertexArray(0);
//}
//
