#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

#define MAX_KEYS 1024

class OpenGLWindow
{
    public:
        OpenGLWindow();
        OpenGLWindow(unsigned int x,unsigned int y,std::string Title);
        virtual ~OpenGLWindow();

        GLFWwindow* window;
        int width;
        int height;
        bool keys[MAX_KEYS];

        bool isOpen();
        void updateSize();
        void update();

        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

    protected:
    private:
};

#endif // OPENGLWINDOW_H
