#include "SGLCamera.h"
#include <SGLUtility.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>





SGLCamera::SGLCamera()
{
    //ctor
}





SGLCamera::~SGLCamera()
{
    //dtor
}

vec3 SGLCamera::getPosition()
{
    return position;
}

vec2 SGLCamera::getRotation()
{
    return rotation;
}

mat4 SGLCamera::getViewMatrix()
{
    return viewMatrix;
}





void SGLCamera::setPosition(vec3 position)
{
    setBoth(position, this->rotation);
}

void SGLCamera::move(vec3 position)
{
    setBoth(this->position + position, this->rotation);
}

void SGLCamera::move(float x, float y, float z)
{
    vec3 movement(x, y, z);
    setBoth(this->position + movement, this->rotation);
}

void SGLCamera::setRotation(vec2 rotation)
{
    setBoth(this->position, rotation);
}

void SGLCamera::rotate(vec2 rotation)
{
    setBoth(this->position, this->rotation + rotation);
}

void SGLCamera::rotate(float x, float y)
{
    vec2 rotation(x, y);
    setBoth(this->position, this->rotation + rotation);
}

void SGLCamera::setBoth(vec3 position, vec2 rotation)
{
    this->position = position;
    this->rotation = rotation;

    rotation = vec2(rotation.x * degreesToRads, rotation.y * degreesToRads);

    targetVector = vec3(0, 0, 1);
    targetVector = glm::rotateX(targetVector, rotation.x);
    targetVector = glm::rotateY(targetVector, rotation.y);

    vec3 up = vec3(0, 1, 0);
    up = glm::rotateX(up, rotation.x);
    up = glm::rotateY(up, rotation.y);

    lookAt(position, position + targetVector, up);
}





void SGLCamera::lookAt(vec3 target, vec3 up)
{
    lookAt(position, target, up);
}

void SGLCamera::lookAt(vec3 position, vec3 target, vec3 up)
{
    viewMatrix = glm::lookAt(position, target, up);
}







void SGLCamera::rotateX(float degrees)
{

}

void SGLCamera::rotateY(float degrees)
{

}

void SGLCamera::rotateZ(float degrees)
{

}
