/*#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shaderprogram.hpp"

GLfloat vertices[] =
{
	-0.6f, -0.6f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	-0.0f,  0.5f, 0.0f,
};

GLuint programId, VAO, VBO;

int main()
{
	if (!glfwInit()) 
	{
		std::cout << "GLFW isn't initialized..." << std::endl;
		glfwTerminate();
		return -1;
	}
	GLFWwindow* window = glfwCreateWindow(800, 600, "My Window", NULL, NULL);
	
	if (window == NULL) 
	{
		std::cout << "Window isn't created..." << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	
	glewExperimental = GL_TRUE;

	if(glewInit() != GLEW_OK)
	{
		std::cout << "GLEW init failed" << std::endl;
		glfwDestroyWindow(window);
		glfwTerminate();
		return -1;
	}

	ShaderProgram program;
	program.attachShader("shaders/simplevs.glsl", GL_VERTEX_SHADER);
	program.attachShader("shaders/simplefs.glsl", GL_FRAGMENT_SHADER);
	program.link();


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO); //VAO aktif ediliyor...
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //VBO aktif ediliyor...
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
	glEnableVertexAttribArray(0);

	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(0, 0, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		
		program.use();
		glBindVertexArray(VAO);
		glEnableVertexAttribArray(0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glUseProgram(0);

		glfwSwapBuffers(window);
	}
	return 0;
}*/