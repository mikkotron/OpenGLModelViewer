#include"shaderClass.h"

// reads the entire contents of a file and returns it as a string
// used for loading shader source code from .vert / .frag files
std::string get_file_contents(const char* filename) //
{
	// Open file in binary mode

	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		// Move read position to the end to get file size
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		// Move back to the beginning and read entire file
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());

		in.close();
		return(contents);
	}
	// Throw error if file could not be opened
	throw(errno);
}

// Shader constructor
// vertexFile   : vertex shader source file
// fragmentFile : fragment shader source file
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	// load shader source code from files using the funciton above
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	// Convert std::string to C-style strings for OpenGL
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	/////////
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); // creating a value/reference to store our vertexshader in
	glShaderSource(vertexShader, 1, &vertexSource, NULL); // feeding in the source code from the top
	glCompileShader(vertexShader); //gpu cant understand source code so compiing it to machine code

	compileErrors(vertexShader, "VERTEX");

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	/////////

	// check for vertex shader compilation errors
	compileErrors(fragmentShader, "FRAGMENT");

	//now wraping those 2 shaders to shader program

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader); // attaching shaders
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID); // wrap
	compileErrors(ID, "PROGRAM");


	glDeleteShader(vertexShader); // deleteing the shaders
	glDeleteShader(fragmentShader);

}
//use shader program
void Shader::Activate()
{
	glUseProgram(ID);
}
// delete shader program
void Shader::Delete()
{
	glDeleteProgram(ID);
}
//checks for compilation errors
void Shader::compileErrors(unsigned int shader, const char* type)
{
	GLint hasCompiled;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << std::endl;
		}
	}
}