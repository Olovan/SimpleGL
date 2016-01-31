#include <GL/glew.h>
#include <SGLBatchBuffer.h>


#define DEFAULT_BUFFER_SIZE sizeof(Vertex) * 1000

SGLBatchBuffer::SGLBatchBuffer()
{
	size = DEFAULT_BUFFER_SIZE;
	createBuffer(DEFAULT_BUFFER_SIZE);
}

SGLBatchBuffer::SGLBatchBuffer(GLuint size)
{
	size = size;
	createBuffer(size);
}

void SGLBatchBuffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
}

void SGLBatchBuffer::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SGLBatchBuffer::createBuffer()
{
	glGenBuffers(1, &bufferID);
}

void SGLBatchBuffer::createBuffer(GLuint size)
{
	createBuffer();
}

void SGLBatchBuffer::destroyBuffer()
{
	bind();
}

void SGLBatchBuffer::setBufferData(GLuint size)
{
	bind();
	glBufferData(GL_ARRAY_BUFFER, size, 0, GL_DYNAMIC_DRAW);
	unbind();
}

void SGLBatchBuffer::subBufferData(GLuint offset, GLuint sizeOfDataBytes, void* data)
{
	bind();
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeOfDataBytes, data);
	unbind();
}

bool SGLBatchBuffer::insertData(GLuint sizeOfDataBytes, void* data)
{
	if(size < currentOffset + sizeOfDataBytes)
		return false;
	subBufferData(currentOffset, sizeOfDataBytes, data);
	currentOffset += sizeOfDataBytes;
	return true;
}

void SGLBatchBuffer::draw()
{
	bind();
	//TODO Draw all elements contained within array using Element array
}



