#include <OpenGLWindow.h>
#include <iostream>
#include <stdlib.h>



static void error_callback(int error, const char* description)
{
    std::cout << description << std::endl;
}

static void create_window(OpenGLWindow* newWindow, unsigned int width, unsigned int height, std::string title)
{
    //Set Up GLFW
    glfwSetErrorCallback(error_callback);
    if(!glfwInit())
        exit(EXIT_FAILURE);

    //Set Width/Height
    newWindow->width = width;
    newWindow->height = height;

    //Make the Window
    newWindow->window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    //Set GLFWwindow User Pointer so the GLFW window knows who owns it
    glfwSetWindowUserPointer(newWindow->window, newWindow);

    //Set key callback function for the window
    glfwSetKeyCallback(newWindow->window, OpenGLWindow::key_callback);

    //Set Window as the Current OpenGL context
    glfwMakeContextCurrent(newWindow->window);

    //Init GLEW and catch errors
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
    {
        std::cout << "GLEW FAILED TO INIT!" << std::endl;
        exit(EXIT_FAILURE);
    }

    //Set up double buffering
    glfwSwapInterval(1);
    glViewport(0, 0, width, height);
}

//Default makes 800x600 blank window with not title
OpenGLWindow::OpenGLWindow()
{
    create_window(this, 800, 600, "");
}


OpenGLWindow::OpenGLWindow(unsigned int x, unsigned int y, std::string title)
{
    create_window(this, x, y, title);
}

OpenGLWindow::~OpenGLWindow()
{
    //dtor
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool OpenGLWindow::isOpen()
{
    return !glfwWindowShouldClose(window);
}

void OpenGLWindow::updateSize()
{
    glfwGetFramebufferSize(window, &width, &height);
}

void OpenGLWindow::update()
{
    glfwPollEvents();
    glfwSwapBuffers(window);
}

void OpenGLWindow::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(key > MAX_KEYS)
        return;

	if(action != GLFW_RELEASE)
	{
		((OpenGLWindow*)glfwGetWindowUserPointer(window))->keys[key] = true;
	}
	else
	{
		((OpenGLWindow*)glfwGetWindowUserPointer(window))->keys[key] = false;
	}
}
