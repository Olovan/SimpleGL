#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 inputColors;
out vec3 VertexOutputColors;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 modelMatrix = mat4(1.0);

void main()
{
	VertexOutputColors = inputColors;
	vec4 positionVec4 = vec4(position, 1);
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * positionVec4;

}
