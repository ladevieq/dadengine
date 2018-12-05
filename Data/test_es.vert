#version 320 es

layout(location = 0)in lowp vec3 inPosition;
layout(location = 1)in lowp vec3 inVertexColor;

/*layout (std140, location = 2) uniform Matrices
{
	mat4 MVP;
} matrices;*/

uniform lowp mat4 MVP;

layout(location = 0)out lowp vec3 outVertexColor;

void main ()
{
	gl_Position = MVP * vec4(inPosition, 1.0);
	outVertexColor = inVertexColor;
}