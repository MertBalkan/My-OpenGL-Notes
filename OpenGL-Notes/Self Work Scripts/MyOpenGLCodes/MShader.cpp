#include "MShader.h"
#include <iostream>

void MShader::createShader(GLuint shaderType, const char* shaderCode) {
	GLuint shaderId = glCreateShader(shaderType);
	glShaderSource(shaderType, 1, &shaderCode, NULL);
	glCompileShader(shaderId);
}

void MShader::attachShader(GLuint* shaderProgram, GLuint shader) {
	glAttachShader(*shaderProgram, shader);
}

void MShader::linkProgram(GLuint* shaderProgram) {
	glLinkProgram(*shaderProgram);
}

void MShader::useShader(GLuint* shaderProgram) {
	glUseProgram(*shaderProgram);
}