#ifndef SIMPLEGLPROGRAM_H
#define SIMPLEGLPROGRAM_H

#include <glew/glew.h>
#include <string>

class SimpleGLShader;

class SimpleGLShaderProgram
{
    public:
        SimpleGLShaderProgram();
        SimpleGLShaderProgram(std::string iVertPath, std::string iFragPath);
        virtual ~SimpleGLShaderProgram();

        GLuint programID;

        const char* vertPath;
        const char* fragPath;

        GLuint vertShaderID = 0;
        GLuint fragShaderID = 0;

        void attachShader(GLuint shaderID);
        void attachShader(SimpleGLShader shader);
        void linkProgram();
        void validateProgram();
        void useProgram();
    protected:
    private:
};

#endif // SIMPLEGLPROGRAM_H
