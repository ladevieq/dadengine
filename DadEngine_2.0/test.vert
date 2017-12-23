#version 410

//layout(location = 0) uniform mat4 MVP;

layout(location = 0)in vec3 inPosition;
layout(location = 1)in vec3 inVertexColor;


layout(location = 0)out vec3 outVertexColor;

void main ()
{
	gl_Position = vec4(inPosition, 1.0);
	outVertexColor = inVertexColor;
}