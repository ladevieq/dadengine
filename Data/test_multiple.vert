#version 410

layout(location = 0)in vec3 inPosition;
layout(location = 1)in vec3 inVertexColor;

uniform mat4 MVP;

layout(location = 0)out vec3 outVertexColor;

void main ()
{
	vec3 right = (gl_InstanceID % 2000) * vec3(1.0, 0.0, 0.0);
	vec3 up = (gl_InstanceID / 2000) * vec3(0.0, 1.0, 0.0);
	gl_Position = MVP * vec4(inPosition + right + up, 1.0);
	outVertexColor = inVertexColor;
}