#ifndef SGLBUFFER_H
#define SGLBUFFER_H

#include <GL/glew.h>
#include <Vertex.h>

class SGLBuffer
{
    public:
        SGLBuffer();
        SGLBuffer(float data[], GLuint size, GLuint count);
        SGLBuffer(Vertex data[], GLuint size);
        ~SGLBuffer();

        GLuint bufferID;
        GLuint count; //Number of floats per Vertex
        GLuint totalSize; //Total size of the Buffer
        GLuint currentOffset; //current location of the offset for the SubData

        void assignData(float data[], GLuint size, GLuint count);
        void assignData(Vertex data[], GLuint size);
        void assignData(GLuint size);
	void subData(GLuint offset, GLuint size, Vertex data[]);
        bool appendData(Vertex data[], GLuint sizeOfData);


	void bind();
	void unbind();
    protected:
    private:
};

#endif // SGLBUFFER_H
