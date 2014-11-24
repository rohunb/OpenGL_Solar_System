#include "Shader.h"
#include <stdarg.h>
#include <vector>



Shader::Shader(const char* vertFileName, const char* fragFilename)
{
	ProcessShader(vertFileName, fragFilename);
	Link();
}
Shader::Shader(const char* vertFileName, const char* fragFilename,
	const char* vertexAttributeName, const char* normalAttributeName, const char* textureCoordAttributeName, const char* colourAttributeName)
{
	ProcessShader(vertFileName, fragFilename);
	if (vertexAttributeName)
	{
		glBindAttribLocation(shaderProgram, VertexAttrib, vertexAttributeName);
		printf("Binding attribute <%s> loc: %d\n", vertexAttributeName, VertexAttrib);
	}
	if (normalAttributeName){
		glBindAttribLocation(shaderProgram, NormalAttrib, normalAttributeName);
		printf("Binding attribute <%s> loc: %d\n", normalAttributeName, NormalAttrib);
	}
	if (textureCoordAttributeName){
		glBindAttribLocation(shaderProgram, TexCoordAttrib, textureCoordAttributeName);
		printf("Binding attribute <%s> loc: %d\n", textureCoordAttributeName, TexCoordAttrib);
	}
	if (colourAttributeName){
		glBindAttribLocation(shaderProgram, ColourAttrib, colourAttributeName);
		printf("Binding attribute <%s> loc: %d\n", colourAttributeName, ColourAttrib);
	}
	Link();
}
Shader::Shader(const char* vertFileName, const char* fragFilename, int numAttributes, ...)
{
	char* name;
	StandardAttribute index;
	ProcessShader(vertFileName, fragFilename);
	va_list args;
	va_start(args, numAttributes);
	for (int i = 0; i < numAttributes; i++)
	{
		index = (StandardAttribute)va_arg(args, int);
		name = va_arg(args, char*);
		printf("Binding attribute <%s> loc: %d\n", name, index);
		glBindAttribLocation(shaderProgram, index, name);
	}
	va_end(args);
	Link();
}

GLuint Shader::GetStandardUniformLoc(StandardUniform uniform)
{
	return standardUniformLocation[uniform];
}

void Shader::HandleStandardUniforms(const char* modelMatrixName, const char* viewMatrixName, const char* projectionMatrixName)
{
	//const char* standardUniformNames[sizeof(StandardUniform)] = { projectionMatrixName, viewMatrixName, modelMatrixName, lightsStruct1Name, lightsStruct2Name, lightsStruct3Name, textureSampler2DName, colourVec4Name };
	std::vector<const char*> standUniformNames = { modelMatrixName, viewMatrixName, projectionMatrixName };

	int count;
	glGetProgramiv(shaderProgram, GL_ACTIVE_UNIFORMS, &count);
	printf("\nThere are %d active Uniforms\n", count);

	for (uint i = 0; i < standUniformNames.size(); i++)
	{
		if (standUniformNames[i] == NULL)
		{
			continue;
		}

		standardUniformLocation[i] = glGetUniformLocation(shaderProgram, standUniformNames[i]);

		if (standardUniformLocation[i] != -1)
		{
			printf("%s loc:%d\n", standUniformNames[i], standardUniformLocation[i]);
		}
		else
		{
			printf("%s loc: unused\n", standUniformNames[i]);
		}
	}
}


void Shader::ProcessShader(const char* vertFilename, const char* fragFilename)
{
	GLint status;
	shaderProgram = vertShader = fragShader = 0;
	try
	{
		const char* vertText = ReadTextFile(vertFilename);
		const char* fragText = ReadTextFile(fragFilename);

		if (vertText == NULL || fragText == NULL)
		{
			return;
		}

		vertShader = glCreateShader(GL_VERTEX_SHADER);
		fragShader = glCreateShader(GL_FRAGMENT_SHADER);

		if (vertShader == 0 || fragShader == 0)
		{
			std::string errorMesg("Error creating shader");
			throw errorMesg;
		}

		glShaderSource(vertShader, 1, &vertText, 0);
		glShaderSource(fragShader, 1, &fragText, 0);

		glCompileShader(vertShader);
		glGetShaderiv(shaderProgram, GL_COMPILE_STATUS, &status);
		if (status == 0)
		{
			GLsizei errorLogSize = 0;
			std::string errorLog;
			glGetShaderiv(shaderProgram, GL_INFO_LOG_LENGTH, &errorLogSize);
			errorLog.resize(errorLogSize);
			glGetShaderInfoLog(shaderProgram, errorLogSize, &errorLogSize, &errorLog[0]);
			throw errorLog;
		}
		glCompileShader(fragShader);
		glGetShaderiv(shaderProgram, GL_COMPILE_STATUS, &status);
		if (status == 0) {
			GLsizei errorLogSize = 0;
			std::string errorLog;
			glGetShaderiv(shaderProgram, GL_INFO_LOG_LENGTH, &errorLogSize);
			errorLog.resize(errorLogSize);
			glGetShaderInfoLog(shaderProgram, errorLogSize, &errorLogSize, &errorLog[0]);
			throw errorLog;
		}

		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, fragShader);
		glAttachShader(shaderProgram, vertShader);

		if (vertText) delete[] vertText;
		if (fragText) delete[] fragText;
	}
	catch (std::string error)
	{
		printf("Shader Processing Error:%s\n", &error[0]);
	}
}

void Shader::Link()
{
	GLint status;
	try
	{
		glLinkProgram(shaderProgram);
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
		if (status == 0)
		{
			GLsizei errorLogSize = 0;
			std::string errorLog;
			glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &errorLogSize);
			errorLog.resize(errorLogSize);
			glGetShaderInfoLog(shaderProgram, errorLogSize, &errorLogSize, &errorLog[0]);
			throw errorLog;
		}
	}
	catch (std::string error)
	{
		printf("Shader Linking Error:%s\n", &error[0]);
	}
}

void Shader::Use()
{
	glUseProgram(shaderProgram);
}

char* Shader::ReadTextFile(const char* fileName)
{
	char* buffer = NULL;
	std::ifstream file(fileName, std::ios::binary);
	if (file.is_open())
	{
		file.seekg(0, std::ios::end);
		int bufferSize = (int)file.tellg();
		if (bufferSize == 0)
		{
			std::string errorMsg("Can't read shader file: ");
			errorMsg += std::string(fileName); 
			throw errorMsg;
		}
		buffer = new char[(int)(bufferSize + 1)];
		file.seekg(0, std::ios::beg);
		file.read(buffer, bufferSize);
		buffer[bufferSize] = '\0';
		file.close();
	}
	else
	{
		std::string errorMsg("Can't open shader file: ");
		printf("ERROR:%s:%s\n", fileName, &errorMsg[0]);
	}
	return buffer;
}
Shader::~Shader()
{
	glDetachShader(shaderProgram, fragShader);
	glDetachShader(shaderProgram, vertShader);
	glDeleteShader(fragShader);
	glDeleteShader(vertShader);
	glDeleteProgram(shaderProgram);
}
