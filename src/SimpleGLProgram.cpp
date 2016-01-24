#include <SimpleGLProgram.h>
#include <Shader.h>
#include <iostream>

SimpleGLShaderProgram::SimpleGLShaderProgram()
{
    //ctor
    programID = glCreateProgram();
}

SimpleGLShaderProgram::SimpleGLShaderProgram(std::string iVertPath, std::string iFragPath)
    : vertPath(iVertPath.c_str()), fragPath(iFragPath.c_str())
{
    programID = glCreateProgram();

    SimpleGLShader vertShader(iVertPath, GL_VERTEX_SHADER);
    SimpleGLShader fragShader(iFragPath, GL_FRAGMENT_SHADER);

    this->attachShader(vertShader.shaderID);
    this->attachShader(fragShader.shaderID);

    this->linkProgram();
    this->validateProgram();
}

SimpleGLShaderProgram::~SimpleGLShaderProgram()
{
    //dtor
    glDeleteProgram(programID);
}

void SimpleGLShaderProgram::attachShader(GLuint shaderID)
{
    glAttachShader(programID, shaderID);

    GLint shaderType;
    glGetShaderiv(shaderID, GL_SHADER_TYPE, &shaderType);

    if(shaderType == GL_VERTEX_SHADER)
        vertShaderID = shaderID;

    if(shaderType == GL_FRAGMENT_SHADER)
        fragShaderID = shaderID;
}

void SimpleGLShaderProgram::attachShader(SimpleGLShader shader)
{
    if(shader.type == GL_VERTEX_SHADER)
        vertPath = shader.path;
    else if(shader.type == GL_FRAGMENT_SHADER)
        fragPath = shader.path;
    attachShader(shader.shaderID);
}

void SimpleGLShaderProgram::linkProgram()
{
    glLinkProgram(programID);


    //Check for Link Errors
    GLint compiled;
    glGetProgramiv(programID, GL_LINK_STATUS, &compiled);
    if(compiled != GL_TRUE)
    {
        std::cout << "Program Link Failed" << std::endl;
        GLint errorLength = 0;
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &errorLength);
        GLchar errorText[errorLength];
        glGetProgramInfoLog(programID, errorLength, &errorLength, errorText);
        std::cout << errorText << std::endl;
    }
}

void SimpleGLShaderProgram::validateProgram()
{
    glValidateProgram(programID);

    GLint compiled;
    glGetProgramiv(programID, GL_VALIDATE_STATUS, &compiled);
    if(compiled != GL_TRUE)
    {
        std::cout << "Program Validation Failed" << std::endl;
        GLint errorLength = 0;
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &errorLength);
        GLchar errorText[errorLength];
        glGetProgramInfoLog(programID, errorLength, &errorLength, errorText);
        std::cout << errorText << std::endl;
    }
}

GLint SimpleGLShaderProgram::getUniformLocation(const char* name)
{
    return glGetUniformLocation(programID, name);
}

void SimpleGLShaderProgram::useProgram()
{
    glUseProgram(programID);
}


void SimpleGLShaderProgram::setUniform1f(const char* name, float value)
{
    glUniform1f(getUniformLocation(name), value);
}
void SimpleGLShaderProgram::setUniform1i(const char* name, int value)
{
    glUniform1i(getUniformLocation(name), value);
}
void SimpleGLShaderProgram::setUniform2f(const char* name, glm::vec2& value)
{
    glUniform2f(getUniformLocation(name), value[0], value[1]);
}
void SimpleGLShaderProgram::setUniform3f(const char* name, glm::vec3& value)
{
    glUniform3f(getUniformLocation(name), value[0], value[1], value[2]);
}
void SimpleGLShaderProgram::setUniform4f(const char* name, glm::vec4& value)
{
    glUniform4f(getUniformLocation(name), value[0], value[1], value[2], value[3]);
}
void SimpleGLShaderProgram::setUniformMat4f(const char* name, glm::mat4& value)
{
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &value[0][0]);
}
