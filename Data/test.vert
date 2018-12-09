#version 410

layout(location = 0)in vec3 inPosition;
layout(location = 1)in vec3 inVertexColor;

uniform mat4 MVP;

layout(location = 0)out vec3 outVertexColor;

void main ()
{
	gl_Position = MVP * vec4(inPosition, 1.0);
	outVertexColor = inVertexColor;
}