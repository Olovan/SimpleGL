#include <OpenGLWindow.h>
#include <iostream>
#include <stdlib.h>



static void error_callback(int error, const char* description)
{
    std::cout << description << std::endl;
}

#pragma region Constructors and Destructor

static void create_window(OpenGLWindow* newWindow, unsigned int width, unsigned int height, std::string title)
{
    //Set Up GLFW
    glfwSetErrorCallback(error_callback);
    if(!glfwInit())
        exit(EXIT_FAILURE);

    //Set Width/Height
    newWindow->width = width;
    newWindow->height = height;

    //Initialize Key Array and Button Array
    for(int i = 0; i < MAX_KEYS; i++)
        newWindow->m_keys[i] = false;
    for (int i = 0; i < MAX_MOUSE_BUTTONS; i++)
        newWindow->m_mouseButtons[i] = false;

    //Make the Window
    newWindow->window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    //Set GLFWwindow User Pointer so the GLFW window knows who owns it
    glfwSetWindowUserPointer(newWindow->window, newWindow);

    //Set Callback Functions
    glfwSetKeyCallback(newWindow->window, OpenGLWindow::key_callback);
    glfwSetCursorPosCallback(newWindow->window, OpenGLWindow::mouse_position_callback);
    glfwSetMouseButtonCallback(newWindow->window, OpenGLWindow::mouse_buttons_callback);


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

    //Enable Depth Buffer
    glEnable(GL_DEPTH_TEST);
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

#pragma endregion

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

//GETTERS AND SETTERS

#pragma region Getters and Setters

bool OpenGLWindow::getKey(unsigned int keycode)
{
    if(keycode >= MAX_KEYS) //Make sure it's a valid keycode
        return false;

    return m_keys[keycode];
}

bool OpenGLWindow::getMouseButton(unsigned int buttoncode)
{
    if(buttoncode >= MAX_MOUSE_BUTTONS)
        return false;

    return m_mouseButtons[buttoncode];
}

void OpenGLWindow::getMousePosition(double& X, double& Y)
{
    X = m_mousexPos;
    Y = m_mouseyPos;
}

#pragma endregion


#pragma region Callback Functions

//CALLBACK FUNCTIONS
void OpenGLWindow::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(key > MAX_KEYS) //Make sure you aren't given an invalid key
        return;

	if(action != GLFW_RELEASE) //Set to true if action is GLFW_PRESS or GLFW_REPEAT
	{
		((OpenGLWindow*)glfwGetWindowUserPointer(window))->m_keys[key] = true;
	}
	else //Set to false if action is GLFW_RELEASE
	{
		((OpenGLWindow*)glfwGetWindowUserPointer(window))->m_keys[key] = false;
	}
}

void OpenGLWindow::mouse_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    ((OpenGLWindow*)glfwGetWindowUserPointer(window))->m_mousexPos = xpos;
    ((OpenGLWindow*)glfwGetWindowUserPointer(window))->m_mouseyPos = ypos;
}

void OpenGLWindow::mouse_buttons_callback(GLFWwindow* window, int button, int action, int mods)
{
    if(button > MAX_MOUSE_BUTTONS)
        return;

    if(action != GLFW_RELEASE)
        ((OpenGLWindow*)glfwGetWindowUserPointer(window))->m_mouseButtons[button] = true;
    else
        ((OpenGLWindow*)glfwGetWindowUserPointer(window))->m_mouseButtons[button] = false;
}

#pragma endregion
