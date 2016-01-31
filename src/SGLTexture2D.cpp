#include "SGLTexture2D.h"

#include <stb_image.h>
#include <iostream>

using std::cout;
using std::endl;

SGLTexture2D::SGLTexture2D()
{
    //ctor
    glGenTextures(1, &textureID);
}

SGLTexture2D::SGLTexture2D(string pathToFile)
{
    loadFromFile(pathToFile);
}

SGLTexture2D::~SGLTexture2D()
{
    //dtor
    glDeleteTextures(1, &textureID);
}

void SGLTexture2D::bind()
{
    glBindTexture(GL_TEXTURE_2D, textureID);
}

bool SGLTexture2D::loadFromFile(string pathToFile)
{
    //Load Image data
    unsigned char * imageData = stbi_load(pathToFile.c_str(), &width, &height, &bpp, 4); // 4 = RGBA   bpp = bytes per pixel
    if(imageData == nullptr) //Make sure image could be loaded before continuing
    {
        cout << "Texture data could not be loaded by stb_load" << endl;
        return false;
    }
    //Create and Bind Texture
    bind();
    //Set Texture settings
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //Load Image data into Texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    return true;
}




