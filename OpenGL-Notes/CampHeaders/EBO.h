#ifndef EBO_CLASS_H
#define EBO_CLASS_H
#include <GL/glew.h>

class EBO {
public:
	GLuint id;
	EBO(GLuint* indices, GLsizeiptr size);

	void bind();
	void unbind();
	void deleteEBO();
};

#endif // ! EBO_CLASS_H
