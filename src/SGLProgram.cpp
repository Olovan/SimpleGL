#include <SGLShaderProgram.h>
#include <SGLShader.h>
#include <iostream>

SGLShaderProgram::SGLShaderProgram()
{
    //ctor
    programID = glCreateProgram();
}

SGLShaderProgram::SGLShaderProgram(std::string iVertPath, std::string iFragPath)
    : vertPath(iVertPath.c_str()), fragPath(iFragPath.c_str())
{
    programID = glCreateProgram();

    SGLShader vertShader(iVertPath, GL_VERTEX_SHADER);
    SGLShader fragShader(iFragPath, GL_FRAGMENT_SHADER);

    this->attachShader(vertShader.shaderID);
    this->attachShader(fragShader.shaderID);

    this->linkProgram();
    this->validateProgram();
}

SGLShaderProgram::~SGLShaderProgram()
{
    //dtor
    glDeleteProgram(programID);
}

void SGLShaderProgram::attachShader(GLuint shaderID)
{
    glAttachShader(programID, shaderID);

    GLint shaderType;
    glGetShaderiv(shaderID, GL_SHADER_TYPE, &shaderType);

    if(shaderType == GL_VERTEX_SHADER)
        vertShaderID = shaderID;

    if(shaderType == GL_FRAGMENT_SHADER)
        fragShaderID = shaderID;
}

void SGLShaderProgram::attachShader(SGLShader shader)
{
    if(shader.type == GL_VERTEX_SHADER)
        vertPath = shader.path;
    else if(shader.type == GL_FRAGMENT_SHADER)
        fragPath = shader.path;
    attachShader(shader.shaderID);
}

void SGLShaderProgram::linkProgram()
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

void SGLShaderProgram::validateProgram()
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

GLint SGLShaderProgram::getUniformLocation(const char* name)
{
    return glGetUniformLocation(programID, name);
}

void SGLShaderProgram::useProgram()
{
    glUseProgram(programID);
}


void SGLShaderProgram::setUniform1f(const char* name, float value)
{
	useProgram();
    glUniform1f(getUniformLocation(name), value);
}
void SGLShaderProgram::setUniform1i(const char* name, int value)
{
	useProgram();
    glUniform1i(getUniformLocation(name), value);
}
void SGLShaderProgram::setUniform2f(const char* name, glm::vec2& value)
{
	useProgram();
    glUniform2f(getUniformLocation(name), value[0], value[1]);
}
void SGLShaderProgram::setUniform3f(const char* name, glm::vec3& value)
{
	useProgram();
    glUniform3f(getUniformLocation(name), value[0], value[1], value[2]);
}
void SGLShaderProgram::setUniform4f(const char* name, glm::vec4& value)
{
	useProgram();
    glUniform4f(getUniformLocation(name), value[0], value[1], value[2], value[3]);
}
void SGLShaderProgram::setUniformMat4f(const char* name, glm::mat4& value)
{
	useProgram();
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &value[0][0]);
}
