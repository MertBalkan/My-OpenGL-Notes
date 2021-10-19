/*#include  <GL/glew.h>
#include <GLFW/glfw3.h>
#include "MShader.h"
#include <iostream>

// Vertex Shader code
static const char* vShader = "                                                \n\
#version 330                                                                  \n\
                                                                              \n\
layout (location = 0) in vec3 pos;											  \n\
                                                                              \n\
void main()                                                                   \n\
{                                                                             \n\
    gl_Position = vec4(0.4 * pos.x, 0.4 * pos.y, pos.z, 1.0);				  \n\
}";

// Fragment Shader
static const char* fShader = "                                                \n\
#version 330                                                                  \n\
                                                                              \n\
out vec4 colour;                                                               \n\
                                                                              \n\
void main()                                                                   \n\
{                                                                             \n\
    colour = vec4(1.0, 0.0, 0.0, 1.0);                                         \n\
}";

GLuint VAO, VBO, shaderProgram;

MShader mShader;

GLfloat vertices[] = {
	-1, -1, 0,
	1, -1, 0,
	0, 1, 0
};


int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow* window = glfwCreateWindow(800, 800, "MyWindow", NULL, NULL);

	if (window == NULL) {
		std::cout << "Error occured while opening window!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		std::cout << "Error occured while opening Glew!" << std::endl;
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, 800, 800);
	
	mShader.createShader(GL_VERTEX_SHADER, vShader);
	mShader.createShader(GL_FRAGMENT_SHADER, fShader);

	shaderProgram = glCreateProgram();

	mShader.attachShader(&shaderProgram, GL_VERTEX_SHADER);
	mShader.attachShader(&shaderProgram, GL_FRAGMENT_SHADER);

	mShader.linkProgram(&shaderProgram);

	glCreateVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window)) 
	{
		glfwPollEvents();
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(VAO);
		mShader.useShader(&shaderProgram);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}*/