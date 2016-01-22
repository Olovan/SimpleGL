#include <SimpleGLProgram.h>
#include <Shader.h>
#include <iostream>

SimpleGLProgram::SimpleGLProgram()
{
    //ctor
    programID = glCreateProgram();
}

SimpleGLProgram::~SimpleGLProgram()
{
    //dtor
    glDeleteProgram(programID);
}

void SimpleGLProgram::attachShader(GLuint shaderID)
{
    glAttachShader(programID, shaderID);
}

void SimpleGLProgram::attachShader(SimpleGLShader shader)
{
    glAttachShader(programID, shader.shaderID);
}

void SimpleGLProgram::linkProgram()
{
    glLinkProgram(programID);


    //Check for Link Errors
    GLint compiled;
    glGetProgramiv(programID, GL_COMPILE_STATUS, &compiled);
    if(!compiled)
    {
        std::cout << "Program Link Failed" << std::endl;
        GLint errorLength = 0;
        glGetShaderiv(programID, GL_INFO_LOG_LENGTH, &errorLength);
        GLchar errorText[errorLength];
        glGetShaderInfoLog(programID, errorLength, &errorLength, errorText);
        std::cout << errorText << std::endl;
    }
}

void SimpleGLProgram::useProgram()
{
    glUseProgram(programID);
}
