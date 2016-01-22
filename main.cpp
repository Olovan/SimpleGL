#include <iostream> //cout, endl;
#include <GL/Glew.h> //GL functions
#include <OpenGLWindow.h> //OpenGLWindow
#include <Shader.h> //SimpleGLShader
#include <SimpleGLProgram.h> //SimpleGLProgram

//using namespace std;

using std::cout;
using std::endl;


int main()
{
    OpenGLWindow window;

    GLfloat verts[] =
    {
        0  ,   300, //Position
        0  , 0.5, 1.0, //Color
        -400 ,-300, //Position
        0  , 1.0, 1.0, //Color
         400 ,-300, //Position
        0  , 1.0, 0.5, //Color
    };

    //create Orthographic coord system
    glLoadIdentity();
    glOrtho(0, window.width, 0, window.height, -1, 1);

    //Create Buffer and bind data to it
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0); //Set Position Attribute (WHICH ATTRIBUTE, SIZE OF ATTRIBUTE, DATA TYPE OF ATTRIBUTE, SHOULD I NORMALIZE IT?, WHERE'S THE FIRST ELEMENT)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (char *)(sizeof(float) * 2));

    //Create and Compile Shaders
    SimpleGLShader fragShader("../../shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
    SimpleGLShader vertShader("../../shaders/VertexShader.glsl", GL_VERTEX_SHADER);

    //Link Shaders to Program
    SimpleGLProgram program;
    program.attachShader(fragShader);
    program.attachShader(vertShader);
    program.linkProgram();
    program.useProgram();

    float orthoMatrix[] = { 2.0f / (window.width), 2.0f / window.height, 0, 1};
    GLint orthoMatLocation = glGetUniformLocation(program.programID, "orthoMatrix");
    glUniform4fv(orthoMatLocation, 1, orthoMatrix);


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


    return 0;
}
