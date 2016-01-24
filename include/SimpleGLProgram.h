#ifndef SIMPLEGLPROGRAM_H
#define SIMPLEGLPROGRAM_H

#include <glew/glew.h>
#include <string>
#include <glm/glm.hpp>

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


        GLint getUniformLocation(const char* name);
        void setUniform1f(const char* name, float value);
        void setUniform1i(const char* name, int value);
        void setUniform2f(const char* name, glm::vec2& value);
        void setUniform3f(const char* name, glm::vec3& value);
        void setUniform4f(const char* name, glm::vec4& value);
        void setUniformMat4f(const char* name, glm::mat4& value);
    protected:
    private:
};

#endif // SIMPLEGLPROGRAM_H
