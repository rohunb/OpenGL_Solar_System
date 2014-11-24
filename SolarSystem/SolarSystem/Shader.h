#pragma once
#include <GL/glew.h>
#include <fstream>

enum StandardUniform { ModelMatrix, ViewMatrix, ProjectionMatrix, LightsStruct1, LightsStruct2, LightsStruct3, TextureSampler2D, ColourVec3 };
enum StandardAttribute {VertexAttrib, NormalAttrib, TexCoordAttrib, ColourAttrib};

typedef unsigned int uint;

class Shader
{
private:
	GLuint shaderProgram, vertShader, fragShader;
	GLuint standardUniformLocation[sizeof(StandardUniform)];

public:
	inline GLuint Program() const { return shaderProgram; }

	Shader(const char* vertFileName, const char* fragFilename);
	Shader(const char* vertFileName, const char* fragFilename, int numAttributes, ...);
	Shader(const char* vertFileName, const char* fragFilename, const char* vertexAttributeName, const char* normalAttributeName = NULL,
		const char* textureCoordAttributeName = NULL, const char* colourAttributeName = NULL);

	~Shader();
	void Use();
	GLuint GetStandardUniformLoc(StandardUniform uniform);
	void HandleStandardUniforms(const char* modelMatrixName, const char* viewMatrixName, const char* projectionMatrixName);

private:
	char* ReadTextFile(const char* fileName);
	void ProcessShader(const char* vertFilename, const char* fragFilename);
	void Link();
};

