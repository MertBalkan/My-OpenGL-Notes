#ifndef VBO_CLASS_H
#define VBO_CLASS_H
#include <GL/glew.h>

class VBO {
public:
	GLuint id;
	VBO(GLfloat* vertices, GLsizeiptr size);
	
	void bind();
	void unbind();
	void deleteVBO();
};

#endif // ! VBO_CLASS_H
