#include "SGLBuffer.h"

#include <iostream>

SGLBuffer::SGLBuffer()
{
    //ctor
    glGenBuffers(1, &bufferID);
}

SGLBuffer::~SGLBuffer()
{
    //dtor
    glDeleteBuffers(1, &bufferID);
}

SGLBuffer::SGLBuffer(float data[], GLuint size, GLuint count)
{
    glGenBuffers(1, &bufferID);
    this->assignData(data, size, count);
}

void SGLBuffer::assignData(float data[], GLuint size, GLuint count)
{
    this->count = count;
    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, NULL);
}
