#ifndef VAO_CLASS_H
#define VAO_CLASS_H
#include "VBO.h"
#include "GL/glew.h"

class VAO {
public:
	GLuint id;
	VAO();

	void linkAttrib(VBO& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	void bind();
	void unbind();
	void deleteVAO();
};
#endif // !VAO_CLASS_H
