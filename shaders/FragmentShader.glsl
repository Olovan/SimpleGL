#version 330

in vec3 VertexOutputColors;
in vec2 VertexOutputTexCoords;
out vec4 FragmentShaderOutputColors;

uniform sampler2D textureSampler;
uniform int useTexture = 0;

void main()
{
	if(useTexture != 0)
	{
		FragmentShaderOutputColors = texture(textureSampler, VertexOutputTexCoords);
	}
	else
	{
		FragmentShaderOutputColors = vec4(VertexOutputColors, 1);
	}
}
