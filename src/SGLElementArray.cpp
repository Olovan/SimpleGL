#include "SGLElementArray.h"

SGLElementArray::SGLElementArray()
{
    //ctor
    createBuffer();
}

SGLElementArray::SGLElementArray(GLushort iArray[], GLuint size)
{
    createBuffer();
    setData(iArray, size);
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

void SGLElementArray::setData(GLushort iArray[], GLuint size)
{
    this->size = size;
    currentSize = size;
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, &iArray[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void SGLElementArray::setSubData(GLushort offset, GLuint size, GLushort iArray[])
{
	bind();
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, iArray);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

bool SGLElementArray::appendData(GLushort data[], GLuint size)
{
	if(currentSize + size > this->size)
		return false;
	bind();
	setSubData(currentSize, size, data);
	currentSize += size;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	return true;
}

void SGLElementArray::assignMemory(GLuint size)
{
	this->size = size;
	currentSize = 0;
	currentArrayOffset = 0;
	bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, 0, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void SGLElementArray::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
}

void SGLElementArray::unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}




