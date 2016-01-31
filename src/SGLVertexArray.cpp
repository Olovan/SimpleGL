#include "SGLVertexArray.h"

SGLVertexArray::SGLVertexArray()
{
    //ctor
    glGenVertexArrays(1, &ID);
}

SGLVertexArray::~SGLVertexArray()
{
    //clean up buffers
    deleteBuffers();
    glDeleteVertexArrays(1, &ID);
}

void SGLVertexArray::deleteBuffers()
{
    for (SGLBuffer* buffer : buffers)
        delete buffer;
    buffers.clear();
}

void SGLVertexArray::addBuffer(SGLBuffer* buffer, GLuint index)
{
    buffers.push_back(buffer);
    glBindVertexArray(ID);
    glBindBuffer(GL_ARRAY_BUFFER, buffer->bufferID);
    glVertexAttribPointer(index, buffer->count, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(index);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void SGLVertexArray::bind()
{
    glBindVertexArray(ID);
}
