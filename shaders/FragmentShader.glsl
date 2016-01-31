#version 330

in vec3 VertexOutputColors;
in vec2 VertexOutputTexCoords;
out vec4 FragmentShaderOutputColors;

uniform sampler2D textureSampler;

void main()
{
	
	FragmentShaderOutputColors = texture(textureSampler, VertexOutputTexCoords).rgba;
	
}
