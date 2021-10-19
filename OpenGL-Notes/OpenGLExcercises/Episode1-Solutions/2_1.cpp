/*#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main() {
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(640, 480, "2_1", NULL, NULL);

	if (window == NULL) {
		std::cout << "Error occured!" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glViewport(0, 0, 640, 480);


	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glClearColor(1, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glClearColor(0, 1, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}*/