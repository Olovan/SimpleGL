#ifndef SGLBUFFER_H
#define SGLBUFFER_H

#include <GL/glew.h>

class SGLBuffer
{
    public:
        SGLBuffer();
        SGLBuffer(float data[], GLuint size, GLuint count);
        ~SGLBuffer();

        GLuint count;
        GLuint bufferID;

        void assignData(float data[], GLuint size, GLuint count);
    protected:
    private:
};

#endif // SGLBUFFER_H
