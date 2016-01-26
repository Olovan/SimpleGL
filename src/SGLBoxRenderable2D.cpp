#include "SGLBoxRenderable2D.h"
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

float radsToDegrees = 180/3.1415;
float degreesToRads = 3.1415/180;



SGLBoxRenderable2D::SGLBoxRenderable2D(glm::vec3 position, glm::vec2 size, glm::vec3 color, SimpleGLShaderProgram* program)
    : position(position), size(size), program(program)
{
    //ctor
    setSize(size);

    setColor(color);

    setPosition(position);

    vertexArray.addBuffer(new SGLBuffer((float*)vertexPositions, sizeof(vertexPositions), 3), 0);
    vertexArray.addBuffer(new SGLBuffer((float*)vertexColors, sizeof(vertexColors), 3), 1);
}

SGLBoxRenderable2D::~SGLBoxRenderable2D()
{
    //dtor
}

void SGLBoxRenderable2D::draw()
{
    program->setUniformMat4f("modelMatrix", modelMatrix);
    vertexArray.bind();
    glDrawArrays(GL_QUADS, 0, 4);
}

void SGLBoxRenderable2D::setSize(glm::vec2 size)
{
    glm::vec3 origin = glm::vec3(-1 * this->origin.x, -1 * this->origin.y, -1 * this->origin.z);
     vertexPositions[0] = glm::vec3(origin.x, origin.y, origin.z);
     vertexPositions[1] = glm::vec3(origin.x + size.x, origin.y, origin.z);
     vertexPositions[2] = glm::vec3(origin.x + size.x, origin.y + size.y, origin.z);
     vertexPositions[3] = glm::vec3(origin.x, origin.y + size.y, origin.z);
}

void SGLBoxRenderable2D::setColor(glm::vec3 color)
{
    vertexColors[0] = color;
    vertexColors[1] = color;
    vertexColors[2] = color;
    vertexColors[3] = color;
}

void SGLBoxRenderable2D::setPosition(glm::vec3 position)
{
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, position);
}

void SGLBoxRenderable2D::setRotation(float degrees, const glm::vec3& axis)
{
    modelMatrix = glm::mat4(1);
    move(position);
    rotate(degrees, axis);
}

void SGLBoxRenderable2D::move(glm::vec3 movement)
{
    modelMatrix = glm::translate(modelMatrix, movement);
}

void SGLBoxRenderable2D::rotate(float degrees, const glm::vec3& axis)
{
    float rads = degrees * degreesToRads;
    modelMatrix = glm::rotate(modelMatrix, rads, axis);
}

void SGLBoxRenderable2D::rotate(float degrees)
{
    rotate(degrees, glm::vec3(0, 0, 1));
}

void SGLBoxRenderable2D::setOrigin(glm::vec3 origin)
{
    this->origin = origin;
    setSize(size);
}

void SGLBoxRenderable2D::resetVertexArray()
{
    //Reload data into the buffers when the data has changed.
    vertexArray.deleteBuffers();
    vertexArray.addBuffer(new SGLBuffer((float*)vertexPositions, sizeof(vertexPositions), 3), 0);
    vertexArray.addBuffer(new SGLBuffer((float*)vertexColors, sizeof(vertexColors), 3), 1);
}
