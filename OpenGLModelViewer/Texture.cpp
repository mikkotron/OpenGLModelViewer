#include "Texture.h"



// Texture constructor 
Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{   
    // Store the texture type for later use
	type = texType;
    // Variables to store image data
    int widthImg, heightImg, numColCh;
    // Flip image vertically to match OpenGL texture coordinate system
    stbi_set_flip_vertically_on_load(true);
    // Load image from file
    unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

    // Generate a texture object
    glGenTextures(1, &ID);

    // activate the texture slot and bind the texture
    glActiveTexture(slot);
    glBindTexture(texType, ID);

    // configures the type of algorithm that is used to make the image smaller or bigger
    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Configures the way the texture repeats
    glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);


    // upload texture data
    // GL_RGBA the internal format used by OpenGL
    glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
    glGenerateMipmap(texType);


    stbi_image_free(bytes);
    glBindTexture(texType, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{   // Get location of the uniform in the shader
    GLuint texUni = glGetUniformLocation(shader.ID, uniform);
    // activate the shader program
    shader.Activate();
    // Tell the shader which texture unit to use
    glUniform1i(texUni, unit);
}
// Bind the texture for use in rendering
void Texture::Bind()
{
    glBindTexture(type, ID);
}
// Unbind the texture
void Texture::Unbind()
{
    glBindTexture(type, 0);
}
// Delete the texture
void Texture::Delete()
{
    glDeleteTextures(1, &ID);
}