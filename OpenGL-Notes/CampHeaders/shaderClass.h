#ifndef  SHADER_CLASS_H
#define  SHADER_CLASS_H

#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char* fileName);

class Shader {
public:
	GLuint id;
	Shader(const char* vertexFile, const char* fragmentFile);

	void activateShader();
	void deleteShader();
	void compileErrors(unsigned int shader, const char* type);
};

class ShaderClass
{
};

#endif // ! SHADER_CLASS_H