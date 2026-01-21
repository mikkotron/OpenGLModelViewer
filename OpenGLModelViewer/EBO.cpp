#include "EBO.h"

// Constructor for the Element Buffer Object (EBO)
// Takes a pointer to index data and the total size of that data in bytes
EBO::EBO(GLuint* indices, GLsizeiptr size)
{
    // Generate one buffer and store its ID in 'ID'
    glGenBuffers(1, &ID);

    // Bind this buffer as the current ELEMENT_ARRAY_BUFFER
    // This tells OpenGL that this buffer will store index (element) data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);

    // Upload the index data to the GPU
    // GL_ELEMENT_ARRAY_BUFFER type of buffer (indices)
    // size total size of the index data in bytes
    // indices pointer to the index data on the CPU
    // GL_STATIC_DRAW data will not change often and will be used for drawing
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

// Binds this EBO so OpenGL knows to use it for indexed drawing
// Must be called while the correct VAO is bound
void EBO::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

// Unbinds the currently bound EBO
// After this call, no element buffer is bound to GL_ELEMENT_ARRAY_BUFFER
void EBO::Unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Deletes the EBO from GPU memory
// Should be called when the buffer is no longer needed
void EBO::Delete()
{
    glDeleteBuffers(1, &ID);
}
