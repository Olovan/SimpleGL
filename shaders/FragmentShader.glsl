#version 330

in vec3 VertexOutputColors;
out vec4 FragmentShaderOutputColors;

uniform mat4 orthoMatrix;

void main()
{
	FragmentShaderOutputColors = vec4(VertexOutputColors, 1);
}
