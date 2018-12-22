#version 410

layout(location = 0)in vec3 outVertexColor;
layout(location = 0)out vec4 outFragColor;

void main()
{
	outFragColor = vec4(outVertexColor, 1.0);
}