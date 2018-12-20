#version 450

layout(location = 0)in vec3 inPosition;
layout(location = 1)in vec3 inVertexColor;

layout (binding = 0) uniform Matrices {
	mat4 MVP;
} matrices;


layout(location = 0)out vec3 outVertexColor;

out gl_PerVertex {
    vec4 gl_Position;
};

void main ()
{
	gl_Position = matrices.MVP * vec4(inPosition, 1.0);
	outVertexColor = inVertexColor;
}