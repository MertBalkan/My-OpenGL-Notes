#pragma once
#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <string>
class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();
	void attachShader(const char* fileName, unsigned int shaderType);
	void link();
	void use();
private:
	unsigned int programId;
	std::string getShaderFromFile(const char* fileName);
};

#endif