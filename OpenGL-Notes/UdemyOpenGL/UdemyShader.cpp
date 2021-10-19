#include "UdemyShader.h"

UdemyShader::UdemyShader() {
	shaderID = 0;
	uniformModel = 0;
	uniformProjection = 0;
	uniformView = 0;
}

void UdemyShader::CreateFromString(const char* vertexCode, const char* fragmentCode) {
	CompileShader(vertexCode, fragmentCode);
}

void UdemyShader::CreateFromFiles(const char* vertexLocation, const char* fragmentLocation) {
	std::string vertexString = ReadFile(vertexLocation);
	std::string fragmentString = ReadFile(fragmentLocation);

	const char* vertexCode = vertexString.c_str();
	const char* fragmentCode = fragmentString.c_str();

	CompileShader(vertexCode, fragmentCode);
}

std::string UdemyShader::ReadFile(const char* fileLocation) {
	std::string content;
	std::ifstream fileStream(fileLocation, std::ios::in);

	if (!fileStream.is_open()) {
		printf("FAILED TO READ %s! File doesnt exist!", fileLocation);
		return "";
	}

	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}
	fileStream.close();
	return content;
}

void UdemyShader::CompileShader(const char* vertexCode, const char* fragmentCode) {
	shaderID = glCreateProgram();

	if (!shaderID) {
		printf("Error creating shader program!\n");
		return;
	}
	AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
	AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };


	//LINKING CONTROL
	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("ERROR LINKING PROGRAM : %s\n", eLog);
		return;
	}

	glValidateProgram(shaderID);

	//VALIDATING CONTROL
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("ERROR VALIDATING PROGRAM : %s\n", eLog);
		return;
	}

	uniformProjection = glGetUniformLocation(shaderID, "projection");
	uniformModel = glGetUniformLocation(shaderID, "model"); //this function returns id and we are picking up this id
	uniformView = glGetUniformLocation(shaderID, "view");
}

void UdemyShader::AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) {

	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLenght[1];
	codeLenght[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLenght);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	//COMPLING CONTROL
	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		printf("ERROR COMPILING the %d SHADER : %s\n", shaderType, eLog);
		return;
	}
	glAttachShader(theProgram, theShader);
}
 
GLuint UdemyShader::GetProjectionLocation() {
	return uniformProjection; 
}

GLuint UdemyShader::GetModelLocation() {
	return uniformModel;
}

GLuint UdemyShader::GetViewLocation() {
	return uniformView;
}

void UdemyShader::UseShader() {
	glUseProgram(shaderID);
}

void UdemyShader::ClearShader() {
	if (shaderID != 0) {
		glDeleteProgram(shaderID);
		shaderID = 0;
	}
	uniformModel = 0;
	uniformProjection = 0;
	uniformView = 0;

}

UdemyShader::~UdemyShader() {
	ClearShader();
}