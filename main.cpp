#include <iostream> //cout, endl;
#include <GL/Glew.h> //GL functions
#include <OpenGLWindow.h> //OpenGLWindow
#include <Shader.h> //SimpleGLShader
#include <SimpleGLProgram.h> //SimpleGLProgram
#include <glm/glm.hpp> //mat4
#include <glm/gtc/matrix_transform.hpp> //glm::ortho

//using namespace std;

using std::cout;
using std::endl;

int main()
{
    OpenGLWindow window;

    GLfloat verts[] =
    {
        400, 600, //Position
        0  , 0.5, 1.0, //Color
        0  ,   0, //Position
        0  , 1.0, 1.0, //Color
        800,   0, //Position
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

    //Set Orthographic Projection uniform variable
    glm::mat4 orthoMatrix = {
                                2/800.0f, 0.0f, 0.0f, -1.0f,
                                0.0f, 2/600.0f, 0.0f, -1.0f,
                                0.0f, 0.0f, 2.0f, 0.0f,
                                0.0f, 0.0f, 0.0f, 1.0f
                            };

    GLint orthoMatLocation = glGetUniformLocation(program.programID, "orthoMatrix");
    glUniformMatrix4fv(orthoMatLocation, 1, GL_FALSE, &orthoMatrix[0][0]);

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

        //Display what we have drawn
        window.update();
    }

    glDeleteBuffers(1, &buffer);


    return 0;
}
