#version 450

layout(location = 0)in vec3 inVertexColor;
layout(location = 0)out vec4 outFragColor;

void main()
{
	outFragColor = vec4(inVertexColor, 1.0);
}