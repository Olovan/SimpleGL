#ifndef SIMPLEGL_SHADER
#define SIMPLEGL_SHADER

#include <string>
#include <fstream>
#include <streambuf>
#include <glew/glew.h>
#include <glfw/glfw3.h>

class SimpleGLShader
{
	public:
	    SimpleGLShader();
	    SimpleGLShader(std::string fileName, GLuint shaderType);
	    ~SimpleGLShader();
        bool compileFromFile(std::string fileName, GLuint shaderType);
        bool compileFromText(std::string text, GLuint shaderType);

        GLuint shaderID;
        GLint type;
        const char* path;

	private:
        std::string shaderText;
	protected:

};

#endif
