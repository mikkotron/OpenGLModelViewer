#include"VBO.h"

//Constructor for vertex buffer object // stores data
VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
	glGenBuffers(1, &ID); // creating a buffer object giving it value one becauase we create only 1 3D object
	//Binding = making certain object the current object when ever functions happen it modifies the current object the binding object
	glBindBuffer(GL_ARRAY_BUFFER, ID); // binding it with GL array buffer because its the type for vertex buffer
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW); //storing the vertices ref for type of buffer, total size of data in bytes, the data itself, specifying the usage of data STATIC vertices will be modified once and used many many times DRAW means we modify the vertices and wil be used to draw image on the screen
}

void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}