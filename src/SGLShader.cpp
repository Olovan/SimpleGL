#include "SGLShader.h"

#include <iostream> //cout endl;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::istreambuf_iterator;


SGLShader::SGLShader(std::string fileName, GLuint shaderType)
{
    type = shaderType;
    path = fileName.c_str();
    compileFromFile(fileName, shaderType);
}

SGLShader::~SGLShader()
{
    glDeleteShader(shaderID);
}

bool SGLShader::compileFromFile(string fileName, GLuint shaderType)
{
    //Put text from file into String
	ifstream file(fileName);
	if (file) //Make Sure file exists
    {
        shaderText = string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        compileFromText(shaderText, shaderType);
    }
    else //If file doesn't exist then return error
    {
        cout << "File " + fileName + " was not found" << endl;
    }
}

bool SGLShader::compileFromText(string text, GLuint shaderType)
{
    //Create Shader Object
    shaderID = glCreateShader(shaderType);

    //Load Shader Text into Object
    const char* temp[1];
    temp[0] = shaderText.c_str();
    glShaderSource(shaderID, 1, temp, 0);

    glCompileShader(shaderID);

    //Check for compile errors
    GLint compiled;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compiled);
    if(!compiled)
    {
        cout << "Shader Compile Failed" << endl;
        GLint errorLength = 0;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &errorLength);
        GLchar errorText[errorLength];
        glGetShaderInfoLog(shaderID, errorLength, &errorLength, errorText);
        cout << errorText << endl;
    }
}
