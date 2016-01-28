#include <iostream> //cout, endl;
#include <GL/Glew.h> //GL functions
#include <OpenGLWindow.h> //OpenGLWindow
#include <Shader.h> //SimpleGLShader
#include <SimpleGLProgram.h> //SimpleGLProgram
#include <SGLBuffer.h>
#include <SGLVertexArray.h>
#include <glm/glm.hpp> //mat4
#include <glm/gtc/matrix_transform.hpp> //glm::ortho
#include <glm/gtx/rotate_vector.hpp> //glm::rotate
#include <SGLBoxRenderable2D.h>

#include <vector>
#include <random>
#include <ctime>


#define NUMBER_OF_BOXES 10000
#define BOX_SIZE 1

#define BATCHBUFFER


using std::cout;
using std::endl;
using std::vector;

float lastReportOfFramerate = 0;
unsigned int framesThisSecond = 0;

struct Vertex
{
    glm::vec3 position;
    glm::vec3 color;
};

int main()
{
    std::srand(std::time(0)); //Seed Random

    OpenGLWindow window;
    glfwSwapInterval(0);

    SimpleGLShaderProgram program("../../Shaders/VertexShader.glsl", "../../shaders/FragmentShader.glsl");
    program.useProgram();

    //Set Orthographic Projection uniform variable
    float degreeToRad = 3.1415/180.0f;

    glm::mat4 orthoMatrix = glm::ortho((float)0.0f, (float)800.0f, (float)0.0f, (float)600.0f);

    program.setUniformMat4f("projectionMatrix", orthoMatrix);

#ifndef BATCHBUFFER
    vector<SGLBoxRenderable2D*> boxes;
    for(int i = 0; i < NUMBER_OF_BOXES; i++)
    {
        boxes.push_back(new SGLBoxRenderable2D(glm::vec3(rand() % 800, rand() % 600, 0.2), glm::vec2(BOX_SIZE, BOX_SIZE), glm::vec3(1, 1, 1), &program));
    }
#endif // BATCHBUFFER

#ifdef BATCHBUFFER
    Vertex vertices[4 * NUMBER_OF_BOXES];
    for(int i = 0; i < NUMBER_OF_BOXES; i++)
    {
        GLint xPos = rand() % 800;
        GLint yPos = rand() % 600;
        vertices[4*i] = (Vertex({.position = glm::vec3(xPos, yPos, 0.2), .color = glm::vec3(1, 1, 1)}));
        vertices[4*i + 1] = (Vertex({.position = glm::vec3(xPos + BOX_SIZE, yPos, 0.2), .color = glm::vec3(1, 1, 1)}));
        vertices[4*i + 2] = (Vertex({.position = glm::vec3(xPos + BOX_SIZE, yPos + BOX_SIZE, 0.2), .color = glm::vec3(1, 1, 1)}));
        vertices[4*i + 3] = (Vertex({.position = glm::vec3(xPos, yPos + BOX_SIZE, 0.2), .color = glm::vec3(1, 1, 1)}));
    }
    cout << vertices[20].position.x << endl;


    GLuint bigBuffer;
    glGenBuffers(1, &bigBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, bigBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 3));
#endif // BATCHBUFFER


    SGLBoxRenderable2D testBox(glm::vec3(400, 300, 1.0), glm::vec2(50,50), glm::vec3(1, 0, 0), &program);
    SGLBoxRenderable2D testBox2(glm::vec3(100, 300, 0.5), glm::vec2(50,50), glm::vec3(0, 0, 1), &program);
    SGLBoxRenderable2D testBox3(glm::vec3(300, 200, 1.0), glm::vec2(50,50), glm::vec3(1, 1, 0), &program);


    SGLBoxRenderable2D bigBox (glm::vec3(400, 300, 0), glm::vec2(600, 600), glm::vec3(1, 1, 1), &program);
    bigBox.vertexColors[0] = glm::vec3(1, 0, 0);
    bigBox.vertexColors[2] = glm::vec3(0, 1, 0);
    bigBox.vertexColors[3] = glm::vec3(0, 0, 1);
    bigBox.setOrigin(glm::vec3(300, 300, 0));
    bigBox.resetVertexArray(); //load updated data into vertex array

    while(window.isOpen())
    {
        //Clean the Screen and process events
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Handle Window Resizing
        window.updateSize();
        glViewport(0, 0, window.width, window.height);

        //rotate
        bigBox.rotate(1);

        //Draw stuff
        testBox.draw();
        testBox2.draw();
        testBox3.draw();
        bigBox.draw();

#ifdef BATCHBUFFER
        glBindVertexArray(0);
        glm::mat4 modelMat = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(program.programID, "modelMatrix"), 1, GL_FALSE, &modelMat[0][0]);
        glBindBuffer(GL_ARRAY_BUFFER, bigBuffer);
        glDrawArrays(GL_QUADS, 0, 4 * NUMBER_OF_BOXES);
#endif // BATCHBUFFER
#ifndef BATCHBUFFER
        for(auto box : boxes)
        {
            box->draw();
        }
#endif // BATCHBUFFER

        //Display what we have drawn
        window.update();

        //Check for OpenGL Error Codes
        GLenum error;
        error = glGetError();
        if(error != GL_NO_ERROR)
            cout << "GL Error: " << error << endl;


        //Report FrameRate
        framesThisSecond++;
        if(glfwGetTime() - lastReportOfFramerate > 1)
        {
            cout << framesThisSecond / (glfwGetTime() - lastReportOfFramerate) << " Frames Per Second" << endl;
            framesThisSecond = 0;
            lastReportOfFramerate = (float)glfwGetTime();
        }
    }

#ifndef BATCHBUFFER
    for(int i = 0; i < NUMBER_OF_BOXES; i++)
    {
        delete boxes[i];
    }
#endif // BATCHBUFFER

//    delete vertArray;

    return 0;
}
