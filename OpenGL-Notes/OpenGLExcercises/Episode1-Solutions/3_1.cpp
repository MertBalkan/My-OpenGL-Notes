/*#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


int main() {
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(640, 480, "3_1", NULL, NULL);

	if (window == NULL) {
		std::cout << "Error!";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glViewport(0, 0, 640, 480);

	float prevTime = float(glfwGetTime());
	float angle = 0.0f;

	while (!glfwWindowShouldClose(window))
	{
		float time = float(glfwGetTime());
		
		if (time - prevTime >= 0.1f) {
			angle += 0.1f;
			prevTime = time;
		}

		glfwPollEvents();

		glClearColor(float(sin(angle)), float(cos(angle)), float(tan(angle)), 1);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);


	}

	glfwTerminate();
	return 0;
}*/