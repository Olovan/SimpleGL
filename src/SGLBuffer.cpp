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
//    glDeleteBuffers(1, &bufferID);
}

SGLBuffer::SGLBuffer(float data[], GLuint size, GLuint count)
{
    glGenBuffers(1, &bufferID);
    this->assignData(data, size, count);
}

SGLBuffer::SGLBuffer(Vertex data[], GLuint size)
{
    glGenBuffers(1, &bufferID);
    this->assignData(data, size);
}

void SGLBuffer::assignData(float data[], GLuint size, GLuint count)
{
    this->count = count;
    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SGLBuffer::assignData(Vertex data[], GLuint size)
{
    count = size / sizeof(Vertex);
	bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
	unbind();
}

void SGLBuffer::assignData(GLuint size)
{
	bind();
	glBufferData(GL_ARRAY_BUFFER, size, 0, GL_DYNAMIC_DRAW);
	unbind();
}

void SGLBuffer::subData(GLuint offset, GLuint size, Vertex data[])
{
	bind();
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
	unbind();
}

bool SGLBuffer::appendData(Vertex data[], GLuint size)
{
	if(size + currentOffset > totalSize)
		return false;
	subData(currentOffset, size, data);
	return true;
}

void SGLBuffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
}

void SGLBuffer::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
