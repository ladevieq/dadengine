#version 410 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec3 inTangent;
layout (location = 3) in vec2 inUV0;
layout (location = 4) in vec2 inUV1;

layout (location = 0) out vec3 outPosition;
layout (location = 1) out vec3 outNormal;
layout (location = 2) out vec3 outTangent;
layout (location = 3) out vec2 outUV0;
layout (location = 4) out vec2 outUV1;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

mat3 normalMatrix = mat3(transpose(inverse(model)));

void main()
{
    vec4 transformedPosition = model * vec4(inPos, 1.0);
    outPosition = transformedPosition.xyz / transformedPosition.w;
    outNormal = normalize(normalMatrix * inNormal);
    outTangent = inTangent;
    outUV0 = inUV0;
    outUV1 = inUV1;

    gl_Position = projection * view * vec4(outPosition, 1.0);
}
