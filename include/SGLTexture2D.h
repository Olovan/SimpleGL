#ifndef SGLTEXTURE2D_H
#define SGLTEXTURE2D_H

#include <string>
#include <GL/glew.h>

using std::string;

class SGLTexture2D
{
    public:
        SGLTexture2D();
        SGLTexture2D(string pathToFile);
        virtual ~SGLTexture2D();

        GLuint textureID;
        int width, height, bpp;

        void bind();
        bool loadFromFile(string pathToFile);
    protected:
    private:
};

#endif // SGLTEXTURE2D_H
