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
		vec4 color = texture(textureSampler, VertexOutputTexCoords);
		if(color.a < 0.1)
			discard;
		FragmentShaderOutputColors = color;
	}
	else
	{
		FragmentShaderOutputColors = vec4(VertexOutputColors, 1);
	}
}
