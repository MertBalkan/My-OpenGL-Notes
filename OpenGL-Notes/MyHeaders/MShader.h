#pragma once
#ifndef MSHADER_HPP
#define MSHADER_HPP
#include <GL/glew.h>

class MShader {
private:
public:
	void attachShader(GLuint* shaderProgram, GLuint shader);
	void createShader(GLuint shaderType, const char* shaderCode);
	void linkProgram(GLuint* shaderProgram);
	void useShader(GLuint* shaderProgram);
};
#endif