#include <SGLCubeRenderable.h>
#include <glm/gtc/matrix_transform.hpp>
#include <SGLUtility.h>

#include <iostream>

SGLCubeRenderable::SGLCubeRenderable()
{
    elementArray.setData(elementArrayData, sizeof(elementArrayData));
}

SGLCubeRenderable::SGLCubeRenderable(vec3 position, vec3 size, vec3 color, SGLShaderProgram* program)
{
    elementArray.setData(elementArrayData, sizeof(elementArrayData));
    setProgram(program);
	createCube(position, size, color);
}

SGLCubeRenderable::SGLCubeRenderable(vec3 position, GLuint size, vec3 color, SGLShaderProgram* program)
{
    elementArray.setData(elementArrayData, sizeof(elementArrayData));
    setProgram(program);
	createCube(position, vec3(size, size, size), color);
}

SGLCubeRenderable::~SGLCubeRenderable()  //Destructor
{
}

void SGLCubeRenderable::createCube(vec3 position, vec3 size, vec3 color)
{
	setOrigin(0, 0, 0);
	genVertexPositions(size);
	setColor(color);
	setPosition(position);
    vertexArray.addBuffer(new SGLBuffer((float*)vertexPositions, sizeof(vertexPositions), 3), 0);
	vertexArray.addBuffer(new SGLBuffer((float*)vertexColors, sizeof(vertexColors), 3), 1);
//	vertexArray.addBuffer(new SGLBuffer(textureCoordinates, sizeof(textureCoordinates), 2), 2); COMMENT OUT UNTIL TEXTURES ARE FIGURED OUT
}

void SGLCubeRenderable::genVertexPositions(vec3 size)
{
    vertexPositions[0] = vec3(origin.x         , origin.y         , origin.z         );
    vertexPositions[1] = vec3(origin.x + size.x, origin.y         , origin.z         );
    vertexPositions[2] = vec3(origin.x + size.x, origin.y + size.y, origin.z         );
    vertexPositions[3] = vec3(origin.x         , origin.y + size.y, origin.z         );
    vertexPositions[4] = vec3(origin.x         , origin.y         , origin.z + size.z);
    vertexPositions[5] = vec3(origin.x + size.x, origin.y         , origin.z + size.z);
    vertexPositions[6] = vec3(origin.x + size.x, origin.y + size.y, origin.z + size.z);
    vertexPositions[7] = vec3(origin.x         , origin.y + size.y, origin.z + size.z);
}

void SGLCubeRenderable::setColor(vec3 color)
{
    vertexColors[0] = color;
    vertexColors[1] = color;
    vertexColors[2] = color;
    vertexColors[3] = color;
    vertexColors[4] = color;
    vertexColors[5] = color;
    vertexColors[6] = color;
    vertexColors[7] = color;
}

void SGLCubeRenderable::setOrigin(float x, float y, float z)
{
    origin = vec3(x, y, z);
}

void SGLCubeRenderable::setOrigin(vec3 origin)
{
    this->origin = origin;
}

void SGLCubeRenderable::setPosition(vec3 position)
{
    modelMatrix = mat4(1);
    move(position);
}

void SGLCubeRenderable::setRotation(vec3 rotation)
{
    modelMatrix = mat4(1);
    rotate(rotation.x, vec3(1, 0, 0));
    rotate(rotation.y, vec3(0, 1, 0));
    rotate(rotation.z, vec3(0, 0, 1));
}

void SGLCubeRenderable::setProgram(SGLShaderProgram* program)
{
    this->program = program;
}

void SGLCubeRenderable::move(vec3 movement)
{
    modelMatrix = glm::translate(modelMatrix, movement);
}

void SGLCubeRenderable::rotate(float rotation, vec3 axis)
{
    float radsRotation = rotation * degreesToRads;
    modelMatrix = glm::rotate(modelMatrix, radsRotation, axis);
}

void SGLCubeRenderable::draw()
{
    //Set Uniforms
    program->setUniform1i("useTexture", useTexture);
    program->setUniformMat4f("modelMatrix", modelMatrix);
    //Draw Triangles
    vertexArray.bind();
    elementArray.bind();
    glDrawElements(GL_TRIANGLES, elementArray.currentSize, GL_UNSIGNED_SHORT, 0);
    elementArray.unbind();
    vertexArray.unbind();
}
