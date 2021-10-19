/*#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main() {
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(640, 480, "1_1", NULL, NULL);


	if (window == NULL) {
		std::cout << "Error occured while opening a window..." << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glViewport(0, 0, 640, 480);

	glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	while(!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}*/