#version 450

layout(set = 0, binding = 0) uniform sampler2D albedo;

layout(location = 0) in vec3 inColor;
layout(location = 1) in vec2 inUV;

layout(location = 0) out vec4 outColor;

void main() {
    outColor = vec4(texture(albedo, inUV).xyz, 1.0);
    // outColor = vec4(inColor, 1.0 );
}
