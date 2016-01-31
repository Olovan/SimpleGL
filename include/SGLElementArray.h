#ifndef SGLELEMENTARRAY_H
#define SGLELEMENTARRAY_H

#include <GL/glew.h>

class SGLElementArray
{
public:
	SGLElementArray();
	SGLElementArray(GLushort iArray[], GLuint size);
	virtual ~SGLElementArray();

	GLuint bufferID;
	GLuint size;
	GLuint currentSize = 0;
	GLushort currentArrayOffset; //Offset used to point Arrays to correct data in batch buffers

	void createBuffer();
	void deleteBuffer();
	void setData(GLushort iArray[], GLuint size);
	void setSubData(GLushort offset, GLuint size, GLushort data[]);
	bool appendData(GLushort data[], GLuint size);
	void assignMemory(GLuint size);
	void bind();
protected:
private:
};

#endif // SGLELEMENTARRAY_H
