#include"VAO.h"

// Constructor
// Generates a new Vertex Array Object (VAO) // stores instructions how to read data
VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}
void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizei stride, void* offset)
{
	// Bind the VBO so OpenGL knows which buffer to read from
	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);// Vertex attrib is a way of communicating to the vert shader from outside
	// Enable the vertex attribute so it can be used by the vertex shader
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

void VAO::Bind()
{
	glBindVertexArray(ID);
}

void VAO::Unbind()
{
	glBindVertexArray(0);
}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}

