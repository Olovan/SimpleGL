#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

#define MAX_KEYS 1024
#define MAX_MOUSE_BUTTONS 32

//Create declaration of create_window so that OpenGLWindow will know that it's a static function because the compiler is stupid
class OpenGLWindow;
static void create_window(OpenGLWindow* newWindow, unsigned int width, unsigned int height, std::string title);

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
        void update();

        //GETTERS AND SETTERS
        bool getKey(unsigned int keycode);
        bool getMouseButton(unsigned int buttoncode);
        void getMousePosition(double& X, double& Y);


        //CALLBACK FUNCTIONS
        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void mouse_position_callback(GLFWwindow* window, double xpos, double ypos);
        static void mouse_buttons_callback(GLFWwindow* window, int button, int action, int mods);

    protected:
    private:
        double m_mousexPos;
        double m_mouseyPos;
        bool m_keys[MAX_KEYS];
        bool m_mouseButtons[MAX_MOUSE_BUTTONS];

        friend void create_window(OpenGLWindow* newWindow, unsigned int width, unsigned int height, std::string title);
};

#endif // OPENGLWINDOW_H
