//My work case and notes for OpenGL...
#include <stdio.h>
#include <string.h>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Window dimensions
const GLint WIDTH = 800, HEIGHT = 600;
const float toRadians = 3.14159265f / 180.0f;

GLuint VAO, VBO, IBO, shader, uniformModel; // IBO -> Index Buffer Object

bool direction = true;
float triOffset = 0.0f;
float triMaxoffset = 0.7f;
float triIncrement = 0.0005f;

float currentAngle = 0.0f;

bool sizeDirection = true;
float currentSize = 0.4f;
float maxSize = 1.0f;
float minSize = 0.1f;

//Vertex Shader
static const char* vShader = "										\n\
#version 330														\n\
																	\n\
layout(location = 0) in vec3 pos;									\n\
out vec4 vColor;													\n\
uniform mat4 model;													\n\
																	\n\
void main()															\n\
{																	\n\
	gl_Position = model * vec4(pos, 1.0);							\n\
	vColor = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);					\n\
}";

//Fragment Shader
static const char* fShader = "										\n\
#version 330														\n\
																	\n\
in vec4 vColor;														\n\
out vec4 color;														\n\
void main()															\n\
{																	\n\
	color = vColor;													\n\
}";

void createTriangle()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[]{
		-1.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLenght[1];
	codeLenght[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLenght);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		printf("ERROR COMPILING the %d SHADER : %s\n", shaderType, eLog);
		return;
	}
	glAttachShader(theProgram, theShader);
}

void compileShaders()
{
	shader = glCreateProgram();

	if (!shader) {
		printf("Error creating shader program!\n");
		return;
	}
	addShader(shader, vShader, GL_VERTEX_SHADER);
	addShader(shader, fShader, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shader);
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("ERROR LINKING PROGRAM : %s\n", eLog);
		return;
	}

	glValidateProgram(shader);

	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("ERROR VALIDATING PROGRAM : %s\n", eLog);
		return;
	}

	uniformModel = glGetUniformLocation(shader, "model"); //this function returns id and we are picking up this id
}

int main()
{
	//Initialise glfw
	if (!glfwInit())
	{
		printf("ERROR...");
		glfwTerminate();
		return 1;
	}

	//setup glfw window properties
	//opengl version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Core profile = No backwars compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //helps us about new version
	//Allow forward compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Ilk window", NULL, NULL);

	if (!window)
	{
		printf("GLFW Window creation failed");
		glfwTerminate();
		return 1;
	}

	//Get buffer size information
	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);

	//Set context for GLEW to use
	glfwMakeContextCurrent(window);
	//Allow modern extension features
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("GLEW INIT FAILED");
		glfwDestroyWindow(window);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST); //depth buffer

	//Setup Viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	createTriangle();
	compileShaders();

	//Loop until window close
	while (!glfwWindowShouldClose(window))
	{
		// Get + handle user input events
		glfwPollEvents();

		if (direction) 
		{
			triOffset += triIncrement;
		}
		else 
		{
			triOffset -= triIncrement;
		}

		if (abs(triOffset) >= triMaxoffset) 
		{
			direction = !direction;
		}
		
		currentAngle += 0.1f;
		
		if(currentAngle >= 360)
		{
			currentAngle -= 360;
		}

		if (sizeDirection) 
		{
			currentSize += 0.0001f;
		}
		else {
			currentSize -= 0.0001f;
		}

		if (currentSize >= maxSize || currentSize <= minSize) {
			sizeDirection = !sizeDirection;
		}


		//Clear window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(shader);

		glm::mat4 model(1.0f);

	    //model = glm::translate(model, glm::vec3(triOffset, 0, 0));
		model = glm::rotate(model, currentAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

		//glUniform1f(uniformModel, triOffset);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));


		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3); //zero to three we say that there is a 3 point
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		glUseProgram(0); //unsigning shader

		glfwSwapBuffers(window); //opengl'in yapacagi cizim pencereye aktarilir.....

	}
	return 0;
}