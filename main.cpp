#include <iostream>
#include <GL/Glew.h>
#include <OpenGLWindow.h>
#include <stdio.h>
#include <Shader.h>

using namespace std;


int main()
{
    OpenGLWindow window;

    GLfloat verts[] =
    {
        0  ,   1, //Position
        0  , 0.5, 1.0, //Color
        -1 ,  -1, //Position
        0  , 1.0, 1.0, //Color
         1 ,  -1, //Position
        0  , 1.0, 0.5, //Color
    };

    glLoadIdentity();
    glOrtho(0, window.width, 0, window.height, -1, 1);
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0); //Set Position Attribute (WHICH ATTRIBUTE, SIZE OF ATTRIBUTE, DATA TYPE OF ATTRIBUTE, SHOULD I NORMALIZE IT?, WHERE'S THE FIRST ELEMENT)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (char *)(sizeof(float) * 2));

    SimpleGLShader fragShader("../../shaders/FragmentShader.frag", GL_FRAGMENT_SHADER);
    SimpleGLShader vertShader("../../shaders/VertexShader.vert", GL_VERTEX_SHADER);

    GLuint shaderProgramID = glCreateProgram();
    glAttachShader(shaderProgramID, vertShader.shaderID);
    glAttachShader(shaderProgramID, fragShader.shaderID);
    glLinkProgram(shaderProgramID);
    glUseProgram(shaderProgramID);

    while(window.isOpen())
    {
        //Clean the Screen and process events
        glClear(GL_COLOR_BUFFER_BIT);

        //Handle Window Resizing
        window.updateSize();
        glViewport(0, 0, window.width, window.height);
        glLoadIdentity();
        glOrtho(0, window.width, 0, window.height, -1, 1);

        //Draw stuff
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //Swap Buffers
        glfwSwapBuffers(window.window);
        glfwPollEvents();
    }

    glDeleteBuffers(1, &buffer);

    glDeleteProgram(shaderProgramID);


    return 0;
}
