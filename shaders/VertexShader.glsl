#version 330

in layout(location = 0) vec2 position;
in layout(location = 1) vec3 inputColors;
out vec3 VertexOutputColors;

uniform mat4 orthoMatrix;

void main()
{
	VertexOutputColors = inputColors;
	vec4 positionVec4 = vec4(position, 0, 1);
	gl_Position = positionVec4 * orthoMatrix;

}
