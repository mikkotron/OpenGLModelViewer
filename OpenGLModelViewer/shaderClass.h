#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>//for reading the shader files
#include <sstream> 
#include <iostream> // for logging erors
#include <cerrno> // for error handling

std::string get_file_contents(const char* filename);

//handles loading, compiling, linking, and using OpenGL shaders
class Shader
{
	public:
		GLuint ID;
		Shader(const char* vertexFile, const char* fragmentFile);

		void Activate();
		void Delete();
	private:
		void compileErrors(unsigned int shader, const char* type);

};

#endif
