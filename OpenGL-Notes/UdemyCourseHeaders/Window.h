#pragma once
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);

	int Initialise();

	GLfloat GetBufferWidth() { return bufferWidth; }
	GLfloat GetBufferHeight() { return bufferHeight; }
	GLfloat GetXChange();
	GLfloat GetYChange();


	bool GetShouldClose() { return glfwWindowShouldClose(mainWindow); }

	bool* getKeys() { return keys; }

	void SwapBuffers() { glfwSwapBuffers(mainWindow); }

	~Window();
private:
	GLFWwindow* mainWindow;

	GLint width, height;
	GLint bufferWidth, bufferHeight;

	bool keys[1024];//size ascii
	bool mouseFirstMoved;

	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;

	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void handleMouse(GLFWwindow* window, double xPos, double yPos);
	void createCallBacks();
};