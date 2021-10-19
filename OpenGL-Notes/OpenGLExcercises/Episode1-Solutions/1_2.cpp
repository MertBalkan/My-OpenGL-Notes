/*#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


int main() {
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(400, 225, "1_2", NULL, NULL);

	if (window == NULL) {
		std::cout << "Error occured" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glViewport(0, 0, 400, 225);

	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}*/