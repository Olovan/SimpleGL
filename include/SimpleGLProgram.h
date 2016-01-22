#ifndef SIMPLEGLPROGRAM_H
#define SIMPLEGLPROGRAM_H

#include <glew/glew.h>

class SimpleGLShader;

class SimpleGLProgram
{
    public:
        SimpleGLProgram();
        virtual ~SimpleGLProgram();

        GLuint programID;

        void attachShader(GLuint shaderID);
        void attachShader(SimpleGLShader shader);
        void linkProgram();
        void useProgram();
    protected:
    private:
};

#endif // SIMPLEGLPROGRAM_H
