#include <iostream> //cout, endl;
#include <GL/Glew.h> //GL functions
#include <OpenGLWindow.h> //OpenGLWindow
#include <SGLShader.h> //SimpleGLShader
#include <SGLProgram.h> //SimpleGLProgram
#include <SGLBuffer.h>
#include <SGLVertexArray.h>
#include <glm/glm.hpp> //mat4
#include <glm/gtc/matrix_transform.hpp> //glm::ortho
#include <glm/gtx/rotate_vector.hpp> //glm::rotate
#include <SGLBoxRenderable2D.h>
#include <SGLCubeRenderable.h>
#include <Vertex.h>

#include <vector>
#include <random>
#include <ctime>



using std::cout;
using std::endl;
using std::vector;

float lastReportOfFramerate = 0;
unsigned int framesThisSecond = 0;

int main()
{
    std::srand(std::time(0)); //Seed Random

    OpenGLWindow window;
    glfwSwapInterval(0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    SGLShaderProgram shader("../../Shaders/VertexShader.glsl", "../../shaders/FragmentShader.glsl");
    shader.useProgram();

    //Set Orthographic Projection uniform variable
    float degreeToRad = 3.1415/180.0f;

    glm::mat4 orthoMatrix = glm::ortho((float)0.0f, (float)800.0f, (float)0.0f, (float)600.0f, (float)-100, (float)100);

    shader.setUniformMat4f("projectionMatrix", orthoMatrix);

    SGLCubeRenderable testCube(glm::vec3(400, 300, 0), glm::vec3(50, 100, 30), glm::vec3(1, 0, 0), &shader);


    SGLBoxRenderable2D testBox(glm::vec3(400, 300, 1.0), glm::vec2(50,50), glm::vec3(1, 0, 0), &shader);
    SGLBoxRenderable2D testBox2(glm::vec3(100, 300, 0.5), glm::vec2(50,50), glm::vec3(0, 0, 1), &shader);
//    SGLBoxRenderable2D testBox3(glm::vec3(300, 200, 1.0), glm::vec2(50,50), glm::vec3(1, 1, 0), &shader);
//
//
    SGLBoxRenderable2D bigBox (glm::vec3(400, 300, 0), glm::vec2(600, 600), glm::vec3(1, 1, 1), &shader);
    bigBox.vertexColors[0] = glm::vec3(1, 0, 0);
    bigBox.vertexColors[2] = glm::vec3(0, 1, 0);
    bigBox.vertexColors[3] = glm::vec3(0, 0, 1);
    bigBox.setOrigin(glm::vec3(300, 300, 0));
    bigBox.resetVertexArray(); //load updated data into vertex array


    bigBox.setTexture("../../images/Spaceman.png");
    testBox.setTexture("../../images/Spaceman.png");
    testBox2.setTexture("../../IMAGES/Spaceman.png");


    double lastFrameTime = 0;
    double deltaFrameTime = 0;

    while(window.isOpen())
    {
        //Clean the Screen and process events
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        deltaFrameTime = glfwGetTime() - lastFrameTime;
        lastFrameTime = glfwGetTime();

        //Handle Window Resizing
        window.updateSize();
        glViewport(0, 0, window.width, window.height);

//        //rotate
        bigBox.rotate(30 * deltaFrameTime);
        testCube.rotate(30 * deltaFrameTime, glm::vec3(0, 1, 0));
        testCube.rotate(30 * deltaFrameTime, glm::vec3(1, 0, 0));
//
//        //Draw stuff
        testCube.draw();
        testBox2.draw();
//        testBox3.draw();
//        bigBox.draw();
//        testBox.draw();

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


    return 0;
}
