#include <iostream> //cout, endl;
#include <GL/Glew.h> //GL functions
#include <OpenGLWindow.h> //OpenGLWindow
#include <Shader.h> //SimpleGLShader
#include <SimpleGLProgram.h> //SimpleGLProgram
#include <glm/glm.hpp> //mat4
#include <glm/gtc/matrix_transform.hpp> //glm::ortho
#include <glm/gtx/rotate_vector.hpp> //glm::rotate

//using namespace std;

using std::cout;
using std::endl;

int main()
{
    OpenGLWindow window;

    GLfloat verts[] =
    {
       -300, 300, //Position
        1.0  , 0.0, 0.0, //Color
       -300,-300, //Position
        0  , 1.0, 0.0, //Color
        300,-300, //Position
        0  , 0.0, 1.0, //Color
        300, 300, //Position
        1  ,   1,   1,
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

    SimpleGLShaderProgram program("../../Shaders/VertexShader.glsl", "../../shaders/FragmentShader.glsl");
    program.useProgram();

    //Set Orthographic Projection uniform variable
    float degreeToRad = 3.1415/180.0f;

    glm::mat4 orthoMatrix = glm::ortho((float)0.0f, (float)800.0f, (float)0.0f, (float)600.0f, (float)-1.0f, (float)1.0f);
    glm::mat4 viewMatrix = glm::mat4(1.0f);
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(400, 300, 0));
    modelMatrix = glm::rotate(modelMatrix, 20 * degreeToRad, glm::vec3(0, 0, 1));


    program.setUniformMat4f("projectionMatrix", orthoMatrix);
    program.setUniformMat4f("viewMatrix", viewMatrix);
    program.setUniformMat4f("modelMatrix", modelMatrix);

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
        glDrawArrays(GL_QUADS, 0, 4);

        //Display what we have drawn
        window.update();

        modelMatrix = glm::rotate(modelMatrix, 1 * degreeToRad, glm::vec3(0, 0, 1));
        program.setUniformMat4f("modelMatrix", modelMatrix);
    }

    glDeleteBuffers(1, &buffer);


    return 0;
}
