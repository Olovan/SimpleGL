#include "SGLBoxRenderable2D.h"
#include <glm/gtc/matrix_transform.hpp>
#include <SGLUtility.h>

#include <iostream>
#include <cstring>
#include <stb_image.h>

using std::cout;
using std::endl;

using glm::vec2;
using glm::vec3;


void SGLBoxRenderable2D::setTexCoords()
{
    texCoords[0] = vec2(0, 0);
    texCoords[1] = vec2(1, 0);
    texCoords[2] = vec2(1, 1);
    texCoords[3] = vec2(0, 1);
}


SGLBoxRenderable2D::SGLBoxRenderable2D(glm::vec3 position, glm::vec2 size, glm::vec3 color, SGLShaderProgram* program)
    : position(position), size(size), program(program)
{
    //ctor
    setSize(size);
    setColor(color);

    setPosition(position);
    elementArrayBuffer.setData( elementArray, sizeof(elementArray));

    vertexArray.addBuffer(new SGLBuffer((float*)vertexPositions, sizeof(vertexPositions), 3), 0);
    vertexArray.addBuffer(new SGLBuffer((float*)vertexColors, sizeof(vertexColors), 3), 1);
    vertexArray.addBuffer(new SGLBuffer((float*)texCoords, sizeof(texCoords), 2), 2);
}

SGLBoxRenderable2D::~SGLBoxRenderable2D()
{
    //dtor
}

void SGLBoxRenderable2D::draw()
{
    program->setUniformMat4f("modelMatrix", modelMatrix);
    vertexArray.bind();
    elementArrayBuffer.bind();
    texture.bind();
    program->setUniform1i("useTexture", useTexture);
    glDrawElements(GL_TRIANGLES, elementArrayBuffer.currentSize, GL_UNSIGNED_SHORT, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
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

void SGLBoxRenderable2D::setTexture(std::string pathToTexture)
{
    if(texture.loadFromFile(pathToTexture))
        useTexture = 1;
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
    vertexArray.addBuffer(new SGLBuffer((float*)texCoords, sizeof(texCoords), 2), 2);
}
