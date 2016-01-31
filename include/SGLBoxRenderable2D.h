#ifndef SGLBOXRENDERABLE2D_H
#define SGLBOXRENDERABLE2D_H

#include <SGLRenderable.h>
#include <glm/glm.hpp>
#include <SGLVertexArray.h>
#include <SGLElementArray.h>
#include <SimpleGLProgram.h>


class SGLBoxRenderable2D : public SGLRenderable
{
    public:
        SGLBoxRenderable2D(glm::vec3 position, glm::vec2 size, glm::vec3 color, SimpleGLShaderProgram* program);
        virtual ~SGLBoxRenderable2D();

        glm::vec3 position;
        glm::vec2 size;
        SimpleGLShaderProgram* program;
        glm::mat4 modelMatrix;
        glm::vec3 origin; //Used to determine rotation and position
        GLuint texID = 0;

        glm::vec3 vertexPositions[4];
        glm::vec3 vertexColors[4];
        glm::vec2 texCoords[4];
        GLushort elementArray[6] = { 0, 2, 1,   2, 0, 3};

        SGLVertexArray vertexArray;
        SGLElementArray elementArrayBuffer;

        void draw() override;
        void setSize(glm::vec2 size);
        void setColor(glm::vec3 color);
        void setPosition(glm::vec3 position);
        void setRotation(float degrees, const glm::vec3& axis);
        void setOrigin(glm::vec3 origin);
        void setTexture(std::string pathToTexture);
        void setTexCoords();
        void move(glm::vec3 movement);
        void rotate(float degrees, const glm::vec3& axis);
        void rotate(float degrees);
        void resetVertexArray();
    protected:
    private:
};

#endif // SGLBOXRENDERABLE2D_H
