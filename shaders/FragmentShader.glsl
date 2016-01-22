#version 330

in vec3 VertexOutputColors;
out vec4 FragmentShaderOutputColors;

void main()
{
	FragmentShaderOutputColors = vec4(VertexOutputColors, 1);
}
