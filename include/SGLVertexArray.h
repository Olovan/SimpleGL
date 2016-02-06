#ifndef SGLVERTEXARRAY_H
#define SGLVERTEXARRAY_H

#include <GL/glew.h>
#include <SGLBuffer.h>
#include <vector>

using std::vector;

class SGLVertexArray
{
    public:
        SGLVertexArray();
        ~SGLVertexArray();

        void addBuffer(SGLBuffer* buffer, GLuint index);
        void deleteBuffers();
        void bind();
        void unbind();

        GLuint ID;
        vector<SGLBuffer*> buffers;

    protected:
    private:
};

#endif // SGLVERTEXARRAY_H
