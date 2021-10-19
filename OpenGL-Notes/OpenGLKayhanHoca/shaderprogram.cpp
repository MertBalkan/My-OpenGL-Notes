#include "shaderprogram.hpp"
#include <GL/glew.h>
#include <iostream>
#include <fstream>

ShaderProgram::ShaderProgram() 
{
	programId = glCreateProgram();
}
ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(programId);
}
void ShaderProgram::link()
{
	glLinkProgram(programId);

	int isLinked;
	char log[512];

	glGetShaderiv(programId, GL_LINK_STATUS, &isLinked);

	if (!isLinked) 
	{
		glGetProgramInfoLog(programId, 512, 0, log);
		std::cout << "Program Link Error: " << std::endl << log << std::endl;
	}

}
void ShaderProgram::use() 
{
	glUseProgram(programId);
}
void ShaderProgram::attachShader(const char* fileName, unsigned int shaderType)
{
	unsigned int shaderId = glCreateShader(shaderType);
	std::string sourceCode = getShaderFromFile(fileName);

	const char* chSourceCode = &sourceCode[0];

	glShaderSource(shaderId, 1, &chSourceCode, NULL);
	
	glCompileShader(shaderId);

	int isCompiled;
	char log[512];

	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);

	if (!isCompiled)
	{
		glGetShaderInfoLog(shaderId, 512, 0, log);
		std::cout << "Shader Type: " << shaderType << std::endl << log << std::endl;


	}

	glAttachShader(programId, shaderId);

	glDeleteShader(shaderId);
}
std::string ShaderProgram::getShaderFromFile(const char* fileName)
{
	std::ifstream file(fileName);
	std::string data;

	if(file.is_open())
	{
		char readChar;
		
		while(readChar = file.get() != EOF)
		{
			data+=readChar;
		}
		file.close();
	}

	return data;
}