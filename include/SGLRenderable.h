#ifndef SGLRENDERABLE_H
#define SGLRENDERABLE_H

#include <SGLShaderProgram.h>

class SGLRenderable
{
    public:
        SGLRenderable();
        virtual ~SGLRenderable();

        virtual void draw(SGLShaderProgram * program);

    protected:
    private:
};

#endif // SGLRENDERABLE_H
