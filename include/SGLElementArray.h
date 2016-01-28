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

        void createBuffer();
        void deleteBuffer();
        void addData(GLushort iArray[], GLuint size);
        void bind();
    protected:
    private:
};

#endif // SGLELEMENTARRAY_H
