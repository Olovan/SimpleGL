#ifndef SGLCAMERA_H
#define SGLCAMERA_H

#include <glm/glm.hpp>

using glm::mat4;
using glm::vec3;
using glm::vec2;

class SGLCamera
{
    public:
        SGLCamera();
        virtual ~SGLCamera();

        vec3 getPosition();
        vec2 getRotation();
        mat4 getViewMatrix();

        void setPosition(vec3 position);
        void move(vec3 position);
        void move(float x, float y, float z);
        void setRotation(vec2 rotation); //Only supports X and Y at this time
        void rotate(vec2 rotation);
        void rotate(float x, float y);
        void setBoth(vec3 position, vec2 rotation);

        void lookAt(vec3 target, vec3 up);
        void lookAt(vec3 position, vec3 target, vec3 up);

        mat4 viewMatrix = mat4(1);
    protected:
    private:

        vec3 position = vec3(0, 0, 0);
        vec2 rotation = vec2(0, 0);

        vec3 targetVector = vec3(0, 0, 1);

        void rotateX(float degrees);
        void rotateY(float degrees);
        void rotateZ(float degrees);
};

#endif // SGLCAMERA_H
