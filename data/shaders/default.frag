#version 410 core
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec3 inTangent;
layout (location = 3) in vec2 inUV0;
layout (location = 4) in vec2 inUV1;

out vec4 outColor;

uniform sampler2D baseColorTexture;
uniform sampler2D metallicRoughnessTexture;
uniform sampler2D normalTexture;
uniform sampler2D occlusionTexture;
uniform sampler2D emissiveTexture;

uniform vec4 baseColorFactor;
uniform float metallicFactor;
uniform float roughnessFactor;
uniform float normalScale;
uniform float occlusionStrength;
uniform vec3 emissiveFactor;

uniform vec3 cameraPosition;

const float PI = 3.14159265359;

vec4 toLinear(vec4 color) {
    return vec4(pow(color.rgb, vec3(2.2)), color.w);
}

float getRangeAttenuation(float range, float distance) {
    return max(min(1.0 - pow(distance / range, 4.0), 1.0), 0.0) / pow(distance, 2.0);
}

vec3 normalTextureNormal = normalize(texture(normalTexture, inUV0).xyz * 2.0 - 1.0);
vec3 T = normalize(inTangent);
vec3 B = -normalize(cross(inNormal, T));
mat3 TBN = mat3(T, B, inNormal);
vec3 normal = normalize(TBN * normalTextureNormal) * normalScale;

#define POINT_LIGHT
float lightIntensity = 10.0;
#if defined(POINT_LIGHT)
vec3 lightPosition = vec3(0.0, 1.0, 0.0);
#else
vec3 lightVector = vec3(-1.0, -1.0, 1.0);
#endif
vec3 lightDiffuseColor = vec3(1.0);
vec3 lightSpecularColor = vec3(1.0);

vec4 baseColor = toLinear(texture(baseColorTexture, inUV0)) * baseColorFactor;

vec4 metallicRoughnesSample = texture(metallicRoughnessTexture, inUV0);
vec2 metallicRoughness = vec2(metallicRoughnesSample.b, metallicRoughnesSample.g) * vec2(metallicFactor, roughnessFactor);

#if defined(POINT_LIGHT)
vec3 toLight = normalize(lightPosition - inPosition);
#else
vec3 toLight = normalize(-lightVector);
#endif
vec3 reflectedToLight = normalize(reflect(toLight, normal));
vec3 toViewer = normalize(cameraPosition - inPosition);
vec3 halfway = normalize(toLight + toViewer);
float lightDistance = length(toLight);

#if defined(POINT_LIGHT)
vec3 radiance = lightIntensity * lightDiffuseColor * getRangeAttenuation(100.0, lightDistance);
#else
vec3 radiance = lightIntensity * lightDiffuseColor;
#endif

// vec4 diffuse = lightIntensity * vec4(baseColor.rgb * max(dot(normal, toLight), 0), baseColor.w);
// vec3 specular = lightSpecularColor * lightIntensity * pow(max(dot(halfway, normal), 0), 10) * float(dot(normal, toLight) > 0);

void main()
{
    float dotHV = max(dot(halfway, toViewer), 0.0);
    float dotNL = max(dot(normal, toLight), 0.0);
    float dotNV = max(dot(normal, toViewer), 0.0);
    float dotNH = max(dot(normal, halfway), 0.0);
    vec3 dielectricSpecular = vec3(0.04);
    vec3 F0 = mix(dielectricSpecular, baseColor.rgb, metallicRoughness.r);
    vec3 F = F0 + (1.0 - F0) * pow(1.0 - dotHV, 5.0);
    float alphaRoughness = metallicRoughness.g * metallicRoughness.g;
    float sqAlphaRoughness = alphaRoughness * alphaRoughness;
    float Vis = 0.5 / (dotNL * sqrt(dotNV * dotNV * (1 - sqAlphaRoughness) + sqAlphaRoughness) + (dotNV * sqrt(dotNL * dotNL * (1 - sqAlphaRoughness) + sqAlphaRoughness)));
    float D = sqAlphaRoughness / (PI * pow(dotNH * dotNH * (sqAlphaRoughness - 1) + 1, 2));

    vec3 diffuse = (1.0 - F) * (mix(baseColor.rgb * (1.0 - dielectricSpecular.r), vec3(0.0), metallicRoughness.r) / PI);
    vec3 specular = F * Vis * D;

    // float ao = texture(occlusionTexture, inUV0).r;
    // vec3 emissive = toLinear(texture(emissiveTexture, inUV0)).rgb * emissiveFactor;

    vec3 color = vec3(radiance * dotNL * (diffuse + specular));
    // color = mix(color, color * ao, occlusionStrength);
    // outColor += vec4(emissive, 0.0);
    outColor = vec4(color, baseColor.a);
}
