#include "SGLElementArray.h"

SGLElementArray::SGLElementArray()
{
    //ctor
    createBuffer();
}

SGLElementArray::SGLElementArray(GLushort iArray[], GLuint size)
{
    createBuffer();
    addData(iArray, size);
}

SGLElementArray::~SGLElementArray()
{
    //dtor
    deleteBuffer();
}

void SGLElementArray::createBuffer()
{
    glGenBuffers(1, &bufferID);
}


void SGLElementArray::deleteBuffer()
{
    glDeleteBuffers(1, &bufferID);
}

void SGLElementArray::addData(GLushort iArray[], GLuint size)
{
    this->size = size;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, &iArray[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void SGLElementArray::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
}




