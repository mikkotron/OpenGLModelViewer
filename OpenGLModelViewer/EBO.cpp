#include "EBO.h"

// Constructor for the Element Buffer Object (EBO)
// takes a pointer to index data and the total size of that data in bytes
//stores indices to reuse vertices for multiple triangles
EBO::EBO(GLuint* indices, GLsizeiptr size)
{
    // generates one buffer and store its ID in ID
    glGenBuffers(1, &ID);

    // bind this buffer as the current ELEMENT_ARRAY_BUFFER
    // This tells OpenGL that this buffer will store index (element) data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);

    // upload the index data
    // GL_ELEMENT_ARRAY_BUFFER type of buffer (indices)
    // size total size of the index data in bytes
    // indices pointer to the index data on the CPU
    // GL_STATIC_DRAW data used for drawing
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

// Binds this EBO so OpenGL knows to use it for indexed drawing
void EBO::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

// unbinds the currently bound EBO
void EBO::Unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// deletes the EBO
void EBO::Delete()
{
    glDeleteBuffers(1, &ID);
}
