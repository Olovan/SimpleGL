#version 330

in layout(location = 0) vec2 position;
in layout(location = 1) vec3 inputColors;
out vec3 VertexOutputColors;

void main()
{
	VertexOutputColors = inputColors;
	gl_Position = vec4(position, 0, 1);
}
