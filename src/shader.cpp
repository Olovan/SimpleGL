#include "Shader.h"

#include <iostream>


SimpleGLShader::SimpleGLShader(std::string fileName, GLuint shaderType)
{
    compileFromFile(fileName, shaderType);
}

SimpleGLShader::~SimpleGLShader()
{
    glDeleteShader(shaderID);
}

bool SimpleGLShader::compileFromFile(std::string fileName, GLuint shaderType)
{
	std::ifstream f(fileName);
	shaderText = std::string((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
	compileFromText(shaderText, shaderType);
}

bool SimpleGLShader::compileFromText(std::string text, GLuint shaderType)
{
    //Create Shader Object
    shaderID = glCreateShader(shaderType);

    //Load Shader Text into Object
    const char* temp[1];
    temp[0] = shaderText.c_str();
    glShaderSource(shaderID, 1, temp, 0);

    glCompileShader(shaderID);

    GLint compiled;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compiled);
    if(!compiled)
    {
        std::cout << "Shader Compile Failed" << std::endl;
        GLint errorLength = 0;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &errorLength);
        GLchar errorText[errorLength];
        glGetShaderInfoLog(shaderID, errorLength, &errorLength, errorText);
        std::cout << errorText << std::endl;
    }
}
