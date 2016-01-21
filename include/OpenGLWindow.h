#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>


class OpenGLWindow
{
    public:
        OpenGLWindow();
        OpenGLWindow(unsigned int x,unsigned int y,std::string Title);
        virtual ~OpenGLWindow();

        GLFWwindow* window;
        int width;
        int height;

        bool isOpen();
        void updateSize();

    protected:
    private:
};

#endif // OPENGLWINDOW_H
