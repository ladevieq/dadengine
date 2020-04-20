#pragma once

#include <cstdint>
#include <cstdio>
#include <vector>

#include "math/vector/vector2.hpp"
#include "math/vector/vector3.hpp"
#include "math/vector/vector4.hpp"

#if defined(OPENGL)
#include "renderer/opengl-loader.hpp"
#elif defined(VULKAN)
#include "renderer/vulkan-loader.hpp"
#endif

namespace DadEngine
{
    struct Vertex
    {
        Vector3 position;
#if defined(VULKAN)
        Vector3 color;
#endif
        Vector3 normal;
        Vector4 tangent;
        Vector2 uv0;
    };

    struct VertexBuffer
    {
        VertexBuffer(std::vector<Vertex> &&_vertices);

#if defined(OPENGL)
        GLuint vertexArrayID;
        GLuint vertexBufferID;
#elif defined(VULKAN)
#endif
        std::vector<Vertex> vertices;
    };

    struct IndexBuffer
    {
        IndexBuffer(std::vector<uint32_t> &&_indices);

#if defined(OPENGL)
        GLuint elementBufferID;
#elif defined(VULKAN)
#endif
        std::vector<uint32_t> indices;
    };

    struct Sampler
    {
#if defined(OPENGL)
        GLint magFilter;
        GLint minFilter;
        GLint wrapS;
        GLint wrapT;
#elif defined(VULKAN)
#endif
    };

    struct Texture
    {
        Texture() = default;
        Texture(uint8_t *_data, int32_t _width, int32_t _height, int32_t _channels, Sampler _sampler, bool _hasAlpha);

#if defined(OPENGL)
        GLuint textureID;
#elif defined(VULKAN)
#endif
        Sampler sampler;

        uint8_t *data = nullptr;
        int32_t width;
        int32_t height;
        int32_t channels;
        bool hasAlpha;
    };

    // PBR metallic roughness
    struct PBRMaterial
    {
        Vector4 baseColorFactor = { 1.f, 1.f, 1.f, 1.f };
        Texture baseColorTexture;

        float metallicFactor  = 1.f;
        float roughnessFactor = 1.f;
        Texture metallicRoughnessTexture;

        float normalScale = 1.f;
        Texture normalTexture;

        float occlusionStrength = 1.f;
        Texture occlusionTexture;

        Vector3 emissiveFactor = { 1.f, 1.f, 1.f };
        Texture emissiveTexture;

        bool hasTransparency;
    };

    struct Primitive
    {
        Primitive(VertexBuffer &&_vertexBuffer, uint32_t _drawMode, PBRMaterial _material)
            : vertices(_vertexBuffer), indices({}), drawMode(_drawMode), material(_material)
        {}

        Primitive(VertexBuffer &&_vertexBuffer, IndexBuffer &&_indexBuffer, uint32_t _drawMode, PBRMaterial _material)
            : vertices(_vertexBuffer),
              indices(_indexBuffer),
              drawMode(_drawMode),
              material(_material)
        {}

        void Render();

        VertexBuffer vertices;
        IndexBuffer indices;
#if defined(OPENGL)
        uint32_t drawMode = GL_TRIANGLES;
#elif defined(VULKAN)
        uint32_t drawMode = 0;
#endif
        PBRMaterial material;
    };

    class Mesh
    {
        public:
        void Render();

        std::vector<Primitive> m_primitives;
    };

} // namespace DadEngine
