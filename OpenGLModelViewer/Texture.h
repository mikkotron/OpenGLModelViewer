#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<glad/glad.h>
#include <stb/stb_image.h>

#include"shaderClass.h"

//handles loading, binding, and managing OpenGL image textures
class Texture
{
	public:
		GLuint ID; // OpenGL ID of the texture
		GLenum type;
		Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

		void texUnit(Shader& shader, const char* uniform, GLuint unit);
		void Bind();
		void Unbind();
		void Delete();
};

#endif

