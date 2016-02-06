#include <Vertex.h>
#include <SGLRenderable.h>
#include <SGLVertexArray.h>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <SGLTexture2D.h>
#include <SGLProgram.h>
#include <SGLElementArray.h>

using glm::vec3;
using glm::vec2;
using glm::mat4;


class SGLCubeRenderable : public SGLRenderable
{
public:
	SGLCubeRenderable();
	SGLCubeRenderable(vec3 position, vec3 size, vec3 color, SGLShaderProgram* program);
	SGLCubeRenderable(vec3 position, GLuint size, vec3 color, SGLShaderProgram* program);
	~SGLCubeRenderable();

	void draw() override;
	void setPosition(vec3 position);
	void move(vec3 movement);
	void setRotation(vec3 rotation);
	void rotate(float rotation, vec3 axis);
	void setColor(vec3 color);
	void setOrigin(vec3 origin);
	void setOrigin(float x, float y, float z);
	void setProgram(SGLShaderProgram* program);
private:
	mat4 modelMatrix;
	vec3 position;
	vec3 rotation;
	vec3 origin = vec3(0, 0, 0);
	SGLVertexArray vertexArray;
	SGLTexture2D texture; //TODO figure out what to do with Texture
	int useTexture = 0;
	vec2 textureCoordinates[8]; //TODO figure out what to do with Texture coords
	vec3 vertexPositions[8];
	vec3 vertexColors[8];
    SGLElementArray elementArray;
	GLushort elementArrayData[36] =
	{
	4, 6, 7,
	4, 7, 5,
	0, 1, 2,
	0, 2, 3,
	4, 0, 3,
	4, 3, 7,
	5, 1, 2,
	5, 2, 6,
	3, 7, 6,
	3, 6, 2,
	4, 5, 1,
	4, 1, 0,
	};

	void createCube(vec3 position, vec3 size, vec3 color);
	void resetVertexArray();
	void genVertexPositions(vec3 size);
	SGLShaderProgram* program;
};
