/*#include <iostream>
#include <thread>
#include <chrono>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <vector>
#include "Square.hpp"

// Vertex Shader code
const char* vShader = "                                                       \n\
#version 330                                                                  \n\
																			  \n\
layout (location = 0) in vec3 pos;											  \n\
uniform vec3 uMove;															  \n\
void main()                                                                   \n\
{                                                                             \n\
	gl_Position = vec4(pos + uMove, 1.0);							          \n\
}";

// Fragment Shader
const char* fShader = "                                                       \n\
#version 330                                                                  \n\
																			  \n\
out vec4 colour;                                                              \n\
uniform vec4 uColor;																			  \n\
void main()                                                                   \n\
{                                                                             \n\
	colour = uColor;                                                          \n\
}";

float length = 0.08f;
std::vector<Square*> snakeList;
//Square sq1(0.0f, 0.0f, length);

GLuint  vertexShader, fragmentShader,
shaderProgram,
VAO, VBO, IBO,
uniformModel, colorModel;


//glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
//glm::vec4 color1 = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
//glm::vec4 color2 = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
//glm::vec4 color3 = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
//glm::vec4 color4 = glm::vec4(1.0f, 1.0f, 0.0f, 0.0f);
void drawSnake() {

	for (auto box : snakeList) {

		glUniform3f(uniformModel, box->getPosition().x, box->getPosition().y, box->getPosition().z);
		glUniform4f(colorModel, box->getColor().r, box->getColor().g, box->getColor().b, box->getColor().a);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}


}

void addToSnakeTail() {
	int elementCount = snakeList.size();

	if (elementCount == 0) {
		snakeList.push_back(new Square(0.0f, 0.0f, length));
	}
	else {
		Square* lastSquare = snakeList[elementCount - 1];
		glm::vec3 pos = lastSquare->getPosition();
		Square::DIRECTION dir = lastSquare->getDirection();

		switch (dir)
		{
		case Square::DIR_RIGHT:
			pos -= glm::vec3(length, 0.0f, 0.0f);
			break;
		case Square::DIR_LEFT:
			pos += glm::vec3(length, 0.0f, 0.0f);
			break;
		case Square::DIR_UP:
			pos -= glm::vec3(0.0f, length, 0.0f);
			break;
		case Square::DIR_DOWN:
			pos += glm::vec3(0.0f, length, 0.0f);
			break;
		}

		Square* newSquare = new Square(pos.x, pos.y, length);
		newSquare->setDirection(dir);
		snakeList.push_back(newSquare);
	}
}

void moveSnake() {
	for (auto next : snakeList) {
		next->move();
	}
	for (int i = snakeList.size() - 1; i > 0 ; i--) {
		snakeList[i]->setDirection(snakeList[i - 1]->getDirection());
	}
} 

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	if (action == GLFW_PRESS) {
		if (snakeList.size() != 0) {

			Square* first = snakeList[0];

			if (key == GLFW_KEY_RIGHT) {
				//sq1.setDirection(Square::DIRECTION::DIR_RIGHT);
				first->setDirection(Square::DIRECTION::DIR_RIGHT);
			}
			if (key == GLFW_KEY_LEFT) {
				//sq1.setDirection(Square::DIRECTION::DIR_LEFT);
				first->setDirection(Square::DIRECTION::DIR_LEFT);
			}
			if (key == GLFW_KEY_UP) {
				//sq1.setDirection(Square::DIRECTION::DIR_UP);
				first->setDirection(Square::DIRECTION::DIR_UP);
			}
			if (key == GLFW_KEY_DOWN) {
				//sq1.setDirection(Square::DIRECTION::DIR_DOWN);
				first->setDirection(Square::DIRECTION::DIR_DOWN);
			}
		}
	}
	if (key == GLFW_KEY_SPACE) 
		addToSnakeTail();

}

int main() {

	glfwInit();
	//Surum belirleme kodlari OpenGL 3.3 ve modern versiyon oldugu belirtiliyor...

	//------------------------------------------------------------------------
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//------------------------------------------------------------------------
	float vertices[] = {
		-length / 2, length / 2, 0.0f,
		-length / 2, -length / 2, 0.0f,
		length / 2, -length / 2, 0.0f,
		length / 2, length / 2, 0.0f
	};

	GLuint indices[] = {
		0, 1, 2,
		0, 2, 3
	};

	addToSnakeTail();

	GLFWwindow* window = glfwCreateWindow(800, 800, "window", NULL, NULL);

	if (window == NULL) {
		std::cout << "Fail";
		glfwTerminate();
		return -1;
	}
	glfwSetKeyCallback(window, key_callback);
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		std::cout << "Error! GLEW IS NOT OK!" << std::endl;
		glfwDestroyWindow(window);
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, 800, 800);

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShader, NULL);
	glCompileShader(vertexShader);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShader, NULL);
	glCompileShader(fragmentShader);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);

	uniformModel = glGetUniformLocation(shaderProgram, "uMove");
	colorModel = glGetUniformLocation(shaderProgram, "uColor");


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		drawSnake();
		moveSnake();
		std::this_thread::sleep_for(std::chrono::milliseconds(50));

		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);

	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}*/