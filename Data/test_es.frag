#version 320 es

layout(location = 0)in lowp vec3 outVertexColor;
layout(location = 0)out lowp vec4 outFragColor;

void main()
{
	outFragColor = vec4(outVertexColor, 1.0);
}