#version 450

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inColor;
layout (location = 2) in vec2 inUV;

out gl_PerVertex
{
    vec4 gl_Position;
};

layout (location = 0) out vec3 outColor;
layout (location = 1) out vec2 outUV;

void main() {
    outColor = inColor;
    outUV = inUV;
    gl_Position = vec4(inPosition, 1.0 );
}
