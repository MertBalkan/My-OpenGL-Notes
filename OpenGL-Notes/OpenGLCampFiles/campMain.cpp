/*#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

int main() {

	glfwInit();
	//Surum belirleme kodlari OpenGL 3.3 ve modern versiyon oldugu belirtiliyor...

	//------------------------------------------------------------------------
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//------------------------------------------------------------------------

	// Vertices coordinates
	GLfloat vertices[] =
	{ // COORDINATES                 COLORS           U    V         
		-0.5f, -0.5f, 0.0f,     0.1f, 0.0f,  0.0f,  0.0f, 0.0f,      // Lower left corner
		-0.5f, 0.5f, 0.0f,      0.0f, 1.0f,  0.0f,  0.0f, 1.0f,      // Lower right corner
		 0.5f,  0.5f, 0.0f,     0.0f, 0.0f,  1.0f,  1.0f, 1.0f,      // Upper corner
		 0.5f, -0.5f, 0.0f,     1.0f, 1.0f,  1.0f,  1.0f, 0.0f       // Inner left
		 
		 
	};

	GLuint indices[] = {
		0, 2, 1,
		0, 3, 2,
	};


	GLFWwindow* window = glfwCreateWindow(800, 800, "window", NULL, NULL);

	if (window == NULL) {
		std::cout << "Fail";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		std::cout << "Error! GLEW IS NOT OK!" << std::endl;
		glfwDestroyWindow(window);
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, 800, 800);

	Shader shaderProgram("default.vert", "default.frag");
	
	VAO VAO1;
	VAO1.bind();
	
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.linkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.linkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.linkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.unbind();
	VBO1.unbind();
	EBO1.unbind();

	GLuint uniId = glGetUniformLocation(shaderProgram.id, "scale");

	int widthImg, heightImg, bitDepth;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* textureData = stbi_load("Textures/brick.png", &widthImg, &heightImg, &bitDepth, 0);

	GLuint texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	//Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(textureData);
	glBindTexture(GL_TEXTURE_2D, 0);

	GLuint tex0Uniform = glGetUniformLocation(shaderProgram.id, "tex0");
	shaderProgram.activateShader();
	glUniform1i(tex0Uniform, 0);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.5, 0.7, 0.7, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		shaderProgram.activateShader();
		glUniform1f(uniId, 0.5f);
		glBindTexture(GL_TEXTURE_2D, texture);
		VAO1.bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	VAO1.deleteVAO();
	VBO1.deleteVBO();
	EBO1.deleteEBO();
	glDeleteTextures(1, &texture);
	shaderProgram.deleteShader();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}*/